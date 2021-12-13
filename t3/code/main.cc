//My libraries
#include <global.h>
#include <validateArgs.h>
#include <Timing.hpp>
#include <checkEdges.h>


//Global variables
using namespace std;


//Functions
bool ** createMatrix(uint32_t nfil, uint32_t ncol){
	//Creacion
	bool **matrix = new bool*[nfil]; //filas 
       	for(size_t i=0 ; i<nfil ; i++){
		matrix[i] = new bool[ncol]; //columnas 
	}
	return matrix;	
}


void forFill(bool ** matrix, size_t i, uint32_t nfil, uint32_t ncol, float plive, uint32_t *living_cells, mt19937 gen){ //Funcion for j=0 para llenar
	uniform_real_distribution<> unif(0,1); 
	for(size_t j=0 ; j<ncol ; j++){
		float valor = unif(gen); //genero valor	aleatoreo
		if(valor <= plive){ 
			matrix[i][j] = true; //si el valor es menor a plive, vive
			*living_cells +=1;
		}else{
			matrix[i][j]=false;
		}	
	}
}


void parallelFillMatrix(bool** matrix, uint32_t nfil, uint32_t ncol, float plive, uint32_t *living_cells){
	uint32_t local_nt = omp_get_max_threads(); //paralelizare con el maximo de threads posibles
	//Generador de numeros aleatoreos float
	random_device dev;
	mt19937 gen(dev());

	*living_cells = 0; //contare el numero de celulas vivas para la matrix inicial
	uint32_t local_living_cells = 0;

	//Llenado paralelo
	#pragma omp parallel for num_threads(local_nt) reduction(+:local_living_cells)
	for(size_t i=0 ; i<nfil ; i++){
		forFill(matrix, i, nfil, ncol, plive, &local_living_cells, gen); //esta funcion es el siguiente for j=0
	}
	*living_cells = local_living_cells;
}


void fillMatrix(bool** matrix, uint32_t nfil, uint32_t ncol, float plive, uint32_t *living_cells){ //PREGUNTAR- 
	//Generador de numeros aleatoreos float
	random_device dev;
	mt19937 gen(dev());

	*living_cells = 0; //contare el numero de celulas vivas para la matrix inicial

	//Llenado
	for(size_t i=0 ; i<nfil ; i++){
		forFill(matrix, i, nfil, ncol, plive, living_cells, gen); //esta funcion es el siguiente for j=0
	}
}

bool ** duplicateMatrix(bool **matrix, uint32_t nfil, uint32_t ncol){
	bool ** new_matrix = createMatrix(nfil, ncol);
	uint32_t local_nt = omp_get_max_threads(); //paralelizare con el maximo de threads posibles
	#pragma omp parallel for num_threads(local_nt)
	for(size_t i=0 ; i<nfil ; i++){
		for(size_t j=0 ; j<ncol ; j++){
			new_matrix[i][j] = matrix[i][j];
		}
	}
	return new_matrix;
}


void printMatrixUniverse(bool ** matrix, uint32_t nfil, uint32_t ncol, size_t i){
	if(i == 0) cout << "------ MATRIZ INICIAL ------" << endl;
	else cout << endl << "----------- "<< i <<" ------------" <<endl;
	for(size_t i =0 ; i<nfil ; i++){
		cout << "| ";
		for(size_t j=0 ; j<ncol ; j++){
			if(matrix[i][j]==true){
				cout << "\uFF61 ";	
			}else{
				cout << "  ";
			}
			//cout << matrix[i][j] << " ";
		}
		cout << "|" << endl;
	}	
}

void checkStateByColumn(bool **matrix, bool **new_matrix, size_t i, uint32_t nfil, uint32_t ncol, uint32_t *living_cells){
	uint32_t neighbours = 0; //vecindad
	uint32_t state = 0; //estado de la celula: viva o muerta

	for(size_t j=0 ; j<ncol ; j++){
		state = matrix[i][j];
		neighbours = checkEdge(matrix, i, j, nfil, ncol);  //Problemas en el borde (0,j) (i,0) (n,j) (i,m) - n= filas, m= columnas 
		if(neighbours == -1){ //Significa que no era un borde
			neighbours = 0;
			neighbours += matrix[i-1][j-1];	
			neighbours += matrix[i][j-1];
			neighbours += matrix[i+1][j-1];
			neighbours += matrix[i+1][j];
			neighbours += matrix[i+1][j+1];
			neighbours += matrix[i][j+1];
			neighbours += matrix[i-1][j+1];
			neighbours += matrix[i-1][j];
		}
		//cout<<"i: "<<i<<", j: "<<j<<", ne: "<<neighbours<<endl;
		//Aplicar reglas
		if( (state==0) && (neighbours==3) ){
			new_matrix[i][j] = 1; //nace
			*living_cells += 1;
		}else{
			if( (state==1) && ( (neighbours==2) || (neighbours==3) ) ){
				new_matrix[i][j] = 1; //sigue viva
				*living_cells += 1;
			}else{
				new_matrix[i][j] = 0; //muere
			}
		}
	}
}


bool ** sequentialGeneration(bool **matrix, uint32_t nfil, uint32_t ncol, uint32_t *living_cells){
	*living_cells = 0; //contare el numero de celulas vivas para esta generacion
	bool **new_matrix = createMatrix(nfil, ncol);	
	
	for(size_t i =0 ; i<nfil ; i++){ 
		checkStateByColumn(matrix, new_matrix, i, nfil, ncol, living_cells);  
	}

	return new_matrix;
}


bool ** parallelGeneration(bool **matrix, uint32_t nfil, uint32_t ncol, uint32_t nt, uint32_t *living_cells){
	*living_cells = 0; //contare el numero de celulas vivas para esta generacion
	uint32_t local_living_cells = 0; //esta aqui porque pragma parallel, no permite paso por referencia de living 	
	bool **new_matrix = createMatrix(nfil, ncol);	

	//si no le asigno schedule, a un thread se le pasan cierta cantidad de iteraciones nfil/nt

	#pragma omp parallel for num_threads(nt) reduction(+:local_living_cells) 
	for(size_t i =0 ; i<nfil ; i++){ //despues lo tiramos a i+=2
		//la variable living_cells es local y se reduce despues de que terminan los threads 
		checkStateByColumn(matrix, new_matrix, i, nfil, ncol, &local_living_cells); 
		//el problema que tenia antes era que living cells era accedido por todos los threads para contar, por lo que habia un cuello de botella
	}

	*living_cells = local_living_cells;
	return new_matrix;
}


int main(int argc, char * argv[]){  //------------- MAIN ---------------
	
	uint32_t nfil, ncol, nt, seq=0, show=0, gen=0;
	float plive;
	uint32_t living_cells_parallel = 0;
	uint32_t living_cells_seq = 0;
	uint32_t sum_seq_time = 0, sum_parallel_time=0;


	//Verificando argumentos	
	if( (argc >= 10) && (argc <= 13) ){ //cantidad de argumentos
		validateArgs(argc, argv, &nfil, &ncol, &nt, &seq, &show, &plive, &gen);
	}else{
		usage(argv);
	}

	
	//ALGOTIHM GAME OF LIFE!!
	Timing timer0, timer_seq, timer_parallel;
	bool **matrixSeq = createMatrix(nfil, ncol);
	bool **matrixParallel;
	//INICIALIZACION
	//timer0.start();
	//fillMatrix(matrixSeq, nfil, ncol, plive, &living_cells_seq); //llenado secuencial, preferi hacerlo paralelo con el de abajo
	parallelFillMatrix(matrixSeq, nfil, ncol, plive, &living_cells_seq); //lo paralelizo solo para que se ejecute mas rapido el llenado inicial, pero este no se toma encuenta en los calculos, ni como generacion
	//timer0.stop();
	
	if( (seq==1) && (show==1) ) printMatrixUniverse(matrixSeq, nfil, ncol, 0); //MOSTRAR
	//cout << "Generacion: 0, "<< living_cells_seq << ", Tc=" << timer0.elapsed() << "ms" << endl;

	if(seq==0){ //Asigno solo si se hara la parte parallela
		matrixParallel = duplicateMatrix(matrixSeq, nfil, ncol);
	}
	
	//GENERACIONES - recien aqui se tomara en cuenta la generacion 1, no en la inicializacion
	for(size_t i=0 ; i<gen ; i++){
		
		timer_seq.start();
		matrixSeq = sequentialGeneration(matrixSeq, nfil, ncol, &living_cells_seq); //SECUENCIAL
		timer_seq.stop();
		sum_seq_time += timer_seq.elapsed(); //sumo secuencial para promediar
		if( (seq==1) && (show==1) ) printMatrixUniverse(matrixSeq, nfil, ncol, (i+1)); //MOSTRAR

		if(seq==1){
			cout << "Generacion: " << i+1 << ", "<< living_cells_seq << ", Tc=" << timer_seq.elapsed() << "ms" << endl;
		}else{
			timer_parallel.start();
			matrixParallel = parallelGeneration(matrixParallel, nfil, ncol, nt, &living_cells_parallel); //PARALELO
			timer_parallel.stop();			
			sum_parallel_time += timer_parallel.elapsed(); //sumo paralelo para promediar
			cout << "Generacion: " << i+1 << ", Par="<< living_cells_parallel << ", Tc=" << timer_parallel.elapsed() << "; Seq=" << living_cells_seq << ", Tc=" << timer_seq.elapsed() << endl;
		}
	}	

	//ESTADISTICAS - SOLO SI ES PARALELO
	if(seq==0){
		float avg_seq = (float(sum_seq_time)/float(gen));
		float avg_parallel = (float(sum_parallel_time)/float(gen));
		cout <<	"Thread: " << nt << endl;
		cout << "Tamano del tablero: " << nfil << " x " << ncol << endl;
		cout << "Tiempo Promedio de Computo de cada generacion:" << endl;
		cout << "\tSec:" << avg_seq << endl;
		cout << "\tPar:" << avg_parallel << endl;
		cout << endl;
		float speedUp = (avg_seq/avg_parallel);
		cout << "SpeedUP" << endl;
		cout << "\tPar:" << speedUp << endl;
		float efficient = (speedUp/float(nt));
		cout << "Eficiencia" << endl;
		cout << "\tPar:" << efficient << endl;
	
	}

	return (EXIT_SUCCESS);
}



