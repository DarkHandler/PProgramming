#include <global.hh>
#include <algorithm>

#include <RandomUnifStream.hpp>
#include <Timing.hpp>
#include <MatrixToMem.hpp>

#include <emmintrin.h>
#include <smmintrin.h>
#include <immintrin.h>

/////////////////////////////////////////////////////////////////////////////////
//   Usage:
//           ./program_name  .......
//
//   Description:
//                ...................
//
/////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////
//  Sorting Network
//      **********************************************************
//      ***Importante: el paso de parámetros es por referencia.***
//      **********************************************************
//
//  Input:
//      __m128i*  dataRegisters  : Arreglo de 4 vectores __m128i, cada uno
//                                con una secuencia desordenada de 4 enteros
//
//  Output:
//    La secuencia de 4 enteros ordenada de cada vector se almacena
//    en las columnas del arreglo 'dataRegisters'.
//
void sortNet(__m128i* dataRegisters) {
 	__m128i r_min0, r_max0, r_min1, r_max1, r_min2, r_max2, r_min3, r_max3, r_min4, r_max4;

	//Paso 1 - Entradas 9 5 19 50, 18 30 25 21
	r_min0 = _mm_min_epi32(dataRegisters[0], dataRegisters[2]); //9 5 19 21 
	r_max0 = _mm_max_epi32(dataRegisters[0], dataRegisters[2]); //18 30 25 50

	//Paso 2 - Entradas 7 20 3 67, 2 25 6 17
	r_min1 = _mm_min_epi32(dataRegisters[1], dataRegisters[3]); //2 20 3 17
	r_max1 = _mm_max_epi32(dataRegisters[1], dataRegisters[3]); //7 25 6 67
	
	//Paso 3 - Entradas 18 30 25 50, 7 25 6 67
	r_min2 = _mm_min_epi32(r_max0, r_max1); //7 25 6 50
	r_max2 = _mm_max_epi32(r_max0, r_max1);	//18 30 25 67

	//Paso 4 - Entradas 9 5 19 21, 2 20 3 17
	r_min3 = _mm_min_epi32(r_min0, r_min1); //2 5 3 17
	r_max3 = _mm_max_epi32(r_min0, r_min1);	//9 20 19 21

	//Paso 5 - Entradas 9 20 19 21, 7 25 6 50
	r_min4 = _mm_min_epi32(r_max3, r_min2); //7 20 6 21
	r_max4 = _mm_max_epi32(r_max3, r_min2);	//9 25 19 50


	//Salida:
	dataRegisters[0] = r_min3; //2 5 3 17
	dataRegisters[1] = r_min4; //7 20 6 21
	dataRegisters[2] = r_max4; //9 25 19 50
	dataRegisters[3] = r_max2; //18 30 25 67
}

//////////////////////////////////////////////////////////////////////
// transpose a matrix vector
//      **********************************************************
//      ***Importante: el paso de parámetros es por referencia.***
//      **********************************************************
//   Input:
//       __m128i*  dataReg  : Arreglo de 4 vectores __m128i
//   Output:
//       __m128i*  dataReg  : Arreglo de 4 vectores que es 
//                            la matriz transpuesta de la original
//
void transpose(__m128i*  dataReg){
	__m128i S[4];
	
	//2 5 3 17, 7 20 6 21
	S[0] = _mm_unpacklo_epi32(dataReg[0], dataReg[1]); //2 7 5 20
	
	//9 25 19 50, 18 30 25 67
	S[1] = _mm_unpacklo_epi32(dataReg[2], dataReg[3]); //9 18 25 30
	
	//2 5 3 17, 7 20 6 21
	S[2] = _mm_unpackhi_epi32(dataReg[0], dataReg[1]); //3 6 17 21
	
	//9 25 19 50, 18 30 25 67
	S[3] = _mm_unpackhi_epi32(dataReg[2], dataReg[3]); //19 25 50 67

	dataReg[0] = _mm_unpacklo_epi64(S[0], S[1]); //2 7 9 18
	dataReg[1] = _mm_unpackhi_epi64(S[0], S[1]); //5 20 25 30
	dataReg[2] = _mm_unpacklo_epi64(S[2], S[3]); //3 6 19 25
	dataReg[3] = _mm_unpackhi_epi64(S[2], S[3]); //17 21 50 67
	
}

//////////////////////////////////////////////////////////////////////
//  Bitonic sorter
//      **********************************************************
//      ***Importante: el paso de parámetros es por referencia.***
//      **********************************************************
//  Input:
//      __m128i*  dataReg1  : secuencia ordenada de 4 enteros ascedente
//      __m128i*  dataReg2  : secuencia ordenada de 4 enteros ascedente
//
//  Output:
//    La secuencia de 8 enteros totalmente ordenada se almacena en:
//      __m128i*  dataReg1   
//      __m128i*  dataReg2 
//
void bitonicSorter(__m128i*  dataReg1, __m128i*  dataReg2)
{

	//Reordenar dataReg2 para que la entrada sea una secuencia bitónica
	*dataReg2 = _mm_shuffle_epi32(*dataReg2, _MM_SHUFFLE(0, 1, 2, 3));
	

	//Código asociados a cada nivel del Bitonic Sorter
	//Paso 1
	//a3 a2 a1 a0, A3 A2 A1 A0
	__m128i temp1 = _mm_shuffle_epi32(*dataReg1, _MM_SHUFFLE(3,1,2,0)); //a3 a1 a2 a0 
	__m128i temp2 = _mm_shuffle_epi32(*dataReg2, _MM_SHUFFLE(3,1,2,0)); //A3 A1 A2 A0
	
	__m128i tr_min1 = _mm_min_epi32(temp1, temp2); //m3 m2 m1 m0
	__m128i tr_max1 = _mm_max_epi32(temp1, temp2); //M3 M2 M1 M0

	//Paso 2
	__m128i temp3 = _mm_unpacklo_epi32(tr_max1, tr_min1); // M3 m3 M2 m2
	__m128i temp4 = _mm_unpackhi_epi32(tr_max1, tr_min1); // M1 m1 M0 m0  

	__m128i temp5 = _mm_unpackhi_epi64(temp3, temp4); // M2 m2 M0 m0  
	__m128i temp6 = _mm_unpacklo_epi64(temp3, temp4); // M3 m3 M1 m1  

	tr_min1 = _mm_min_epi32(temp5, temp6); //m_3 m_2 m_1 m_0
	tr_max1 = _mm_max_epi32(temp5, temp6); //M_3 M_2 M_1 M_0

	//Paso 3
	__m128i temp7 = _mm_unpackhi_epi32(tr_max1, tr_min1); //M_1 m_1 M_0 m_0 
	__m128i temp8 = _mm_unpacklo_epi32(tr_max1, tr_min1); //M_3 m_3 M_2 m_2 
	
	tr_min1 = _mm_min_epi32(temp7, temp8); //mm3 mm2 mm1 mm0
	tr_max1 = _mm_max_epi32(temp7, temp8); //MM3 MM2 MM1 MM0

	//ORDENAR SALIDA
	__m128i temp9 = _mm_unpackhi_epi32(tr_max1, tr_min1); //MM1 mm1 MM0 mm0
	__m128i temp10 = _mm_unpacklo_epi32(tr_max1, tr_min1); //MM3 mm3 MM2 mm2

	temp9 = _mm_shuffle_epi32(temp9, _MM_SHUFFLE(0,1,2,3)); // mm0 MM0 mm1 MM1
	temp10 = _mm_shuffle_epi32(temp10, _MM_SHUFFLE(0,1,2,3)); //mm2 MM2 mm3 MM3
	
	//Nivel de salida
	*dataReg1 = temp9; //Quedan los minimos mm0 MM0 mm1 MM1
	*dataReg2 = temp10; //Quedan los maximos mm2 MM2 mm3 MM3

}

//////////////////////////////////////////////////////////////////////
//  Bitonic Merge Network
//      **********************************************************
//      ***Importante: el paso de parámetros es por referencia.***
//      **********************************************************
//  Input:
//       __m128i*  dataReg  : Arreglo de 4 vectores ordenados
//                            individualmente
//
//  Output:
//      __m128i*  dataReg  : Arreglo de 4 vectores ordenados 
//                           globalmente
//
void BNM(__m128i*  dataReg){
	//Debe llamar a bitonicSorter() según el esquema

	//BS 1
	bitonicSorter(&dataReg[0], &dataReg[1]);
	//BS 2
	bitonicSorter(&dataReg[2], &dataReg[3]);
	//BS 3
	bitonicSorter(&dataReg[1], &dataReg[2]);
	//BS 4
	bitonicSorter(&dataReg[0], &dataReg[1]);
	//BS 5
	bitonicSorter(&dataReg[2], &dataReg[3]);

}

void intrinsicSort(uint32_t * matrix, uint32_t nfil){
	
	__m128i dataReg[4];
	//Si nfil == 1000, significa que el for llegaria a 1008, por lo que debo parar antes osea en 992
	uint32_t to_int = (nfil/16); //obtengo entero divisible
	uint32_t N = to_int * 16; //saco el valor de hasta donde debe llegar realmente
	for(size_t i=0; i< N ; i+=16){ 
		dataReg[0] = _mm_setr_epi32(matrix[i] , matrix[i+1] , matrix[i+2] , matrix[i+3] );
		dataReg[1] = _mm_setr_epi32(matrix[i+4] , matrix[i+5] , matrix[i+6] , matrix[i+7] );
		dataReg[2] = _mm_setr_epi32(matrix[i+8] , matrix[i+9] , matrix[i+10], matrix[i+11]);
		dataReg[3] = _mm_setr_epi32(matrix[i+12], matrix[i+13], matrix[i+14], matrix[i+15]);

		//Ordenar los 4 datos de cada registro a través del Sorting Network
		sortNet(dataReg);
		transpose(dataReg);
	
		//Ordenar 8 datos en total de dos registros a través del Bitonic Sorter
		//bitonicSorter(&dataReg[0], &dataReg[1]);
		//bitonicSorter(&dataReg[2], &dataReg[3]);
	
		//Ordenar 16 datos a través de la Bitonic Merge Network
		BNM(dataReg);

		//Pasarlo a memoria principal en la matriz
		matrix[i]  = _mm_extract_epi32(dataReg[0], 0);
		matrix[i+1]  = _mm_extract_epi32(dataReg[0], 1);
		matrix[i+2]  = _mm_extract_epi32(dataReg[0], 2);
		matrix[i+3]  = _mm_extract_epi32(dataReg[0], 3);
	
		matrix[i+4]  = _mm_extract_epi32(dataReg[1], 0);
		matrix[i+5]  = _mm_extract_epi32(dataReg[1], 1);
		matrix[i+6]  = _mm_extract_epi32(dataReg[1], 2);
		matrix[i+7]  = _mm_extract_epi32(dataReg[1], 3);
		
		matrix[i+8]  = _mm_extract_epi32(dataReg[2], 0);
		matrix[i+9]  = _mm_extract_epi32(dataReg[2], 1);
		matrix[i+10] = _mm_extract_epi32(dataReg[2], 2);
		matrix[i+11] = _mm_extract_epi32(dataReg[2], 3);
	
		matrix[i+12] = _mm_extract_epi32(dataReg[3], 0);
		matrix[i+13] = _mm_extract_epi32(dataReg[3], 1);
		matrix[i+14] = _mm_extract_epi32(dataReg[3], 2);
		matrix[i+15] = _mm_extract_epi32(dataReg[3], 3);

	}
}

void showData(std::string message, MatrixToMem& m, uint32_t N){ //N es el numero de elementos a mostrar
	// Mostrar los N primeros elementos de la matriz
	std::cout << "-----------" << message << "---------" << std::endl;
	for(size_t i=0; i < N; i++){	
		std::cout << std::setw(8);	
		std::cout <<  m[i] << std::endl;	
	}
}


void uso(std::string pname)
{
	std::cerr << "Uso: " << pname << " --fname MATRIX_FILE" << std::endl;
	exit(EXIT_FAILURE);
}

int main(int argc, char** argv)
{

	std::string fileName;
	
	//////////////////////////////////////////
	//  Read command-line parameters easy way
	if(argc != 3){
		uso(argv[0]);
	}
	std::string mystr;
	for (size_t i=0; i < argc; i++) {
		mystr=argv[i];
		if (mystr == "--fname") {
			fileName = argv[i+1];
		}
	}

	
	Timing timer0, timer1, timer2;
	////////////////////////////////////////////////////////////////
	// Transferir la matriz del archivo fileName a memoria principal
	timer0.start();
	MatrixToMem m1(fileName);
	timer0.stop();
	MatrixToMem m2(fileName);
	
	std::cout << "Time to transfer to main memory: " << timer0.elapsed() << std::endl; //Comentar al hacer cualquier experimento
	//std::cout << timer0.elapsed() << std::endl; //Descomentar al hacer cualquier experimento
	

	///////////////////////////////////////////////////////////////
	//showData("Datos a ordenar sort",m1, 16);	
	//Ordenamiento de menor a mayor de arreglo dinamico en memoria principal con SORT
	//uint32_t to_int = (m1._nfil/16);  //Descomentar para experimento 2 y comentar al hacer el 1
	//uint32_t N = to_int * 16; //Descomentar para experimento 2 y comentar al hacer el 1
	timer1.start(); 
	//for(size_t i=0; i<N; i+=16){  //Descomentar para experimento 2 y comentar al hacer el 1
	//	std::sort(m1._matrixInMemory + i, m1._matrixInMemory +(i+16)); //Descomentar para experimento 2 y comentar al hacer el 1
		std::sort(m1._matrixInMemory, m1._matrixInMemory + m1._nfil); //Comentar para experimento 2 y descomentar al hacer el 1
	//} //Descomentar para experimento 2 y comentar al hacer el 1
	timer1.stop();
	
	//showData("Datos procesados sort",m1, 16); //Proposito informativo fuera de los experimentos
	
	std::cout << "Time to sort in main memory: " << timer1.elapsed() << std::endl; //Comentar al hacer cualquier experimento
	//std::cout << timer1.elapsed() << std::endl; //Descomentar al hacer cualquier experimento

	
	////////////////////////////////////////////////////////////////
	// Mostrar los N primeros elementos de la matriz desordenada.
	//showData("Datos a ordenar", m2, 16);

	//Ordenamiento cada 16 elementos del arreglo dinamico con instrinsics	
	timer2.start();
	intrinsicSort(m2._matrixInMemory, m2._nfil);
	//Ordenamiento en memoria principal del resto de los elementos
	std::sort(m2._matrixInMemory, m2._matrixInMemory + m2._nfil); //Comentar para experimento 2 y descomentar al hacer el 1
	timer2.stop();

	std::cout << "Time2 to sort with intrinsics and main memory: " << timer2.elapsed() << std::endl; //Comentar al hacer cualquier experimento
	//std::cout << timer2.elapsed() << std::endl; //Descomentar al hacer cualquier experimento

	////////////////////////////////////////////////////////////////
	// Mostrar los N primeros elementos de la matriz ordenada.
	//showData("Datos procesados",m2, 16); //Proposito informativo fuera de los experimentos
	

	return(EXIT_SUCCESS);
}

