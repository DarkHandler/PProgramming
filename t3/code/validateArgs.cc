#include <global.h>
#include <validateArgs.h>

using namespace std;

void usage(char *argv[]){
        cout << "Uso: " << argv[0] << " [Opciones]..." << endl;
        cout << "Opciones:" << endl;
        cout << "" << endl;
        cout << "   --ncol  \t especifica el numero de columnas del tablero" << endl;
        cout << "   --nfil  \t especifica el numero de filas del tablero" << endl;
        cout << "   --nt    \t especifica la cantidad de threads (nt>=1)" << endl;
        cout << "   --plive \t probabilidad que una celula este viva en la primera generacion" << endl;
        cout << "   --seq   \t ejecuta la version secuencial. Si esta opcion no esta, se ejecuta la version paralela/secuencial" << endl;
        cout << "   --show  \t permite visualizar el tablero para comprobar el funcionamiento de su implementacion en la version secuencial (--seq)" << endl;
        cout << "   --gen  \t especifica el numero de generaciones" << endl;
        cout << "" <<endl;
        exit(EXIT_FAILURE);
}


void validateArgs(int argc, char *argv[], uint32_t *nfil, uint32_t *ncol, uint32_t *nt, uint32_t *seq, uint32_t *show, float *plive, uint32_t *gen){
	uint8_t essential_param_count = 0; //Debe quedar en 4 --> nfil, ncol, plive y gen
	uint8_t nt_exist=0; //verifica si esta nt
	
	for(size_t i=1; i<argc; i++){
		string arg = argv[i]; //argumento

		if(arg == "--seq"){
			*seq=1; //significa que se encontro
		}else{
			if(arg == "--show"){ //solo funciona debe estar si existe --seq
				*show=1;	
			}else{	
				if(arg == "--ncol"){
					*ncol=atoi(argv[i+1]);
					i++;
					essential_param_count++;
				}else{
					if(arg == "--nfil"){
						*nfil=atoi(argv[i+1]);
						i++;
						essential_param_count++;
					}else{
						if(arg == "--nt"){ //solo para paralelo
							*nt=atoi(argv[i+1]);
							i++;
							nt_exist=1; //se agrego
						}else{
							if(arg == "--plive"){
								*plive=atof(argv[i+1]);
								i++;
								essential_param_count++;
							}else{
								if(arg == "--gen"){
									*gen=atoi(argv[i+1]);
									i++;
									essential_param_count++;
								}
							}	
						}
					}
				}	
			}
		}	
	}

	if(*seq==1){ //si es secuencial
		if( (essential_param_count != 4) ){
			usage(argv);
		}else{
	       		if(nt_exist==1){ 
				usage(argv);
			}
		}
	}else{ //es paralelo
		if((*show==1) || (nt_exist==0) || (*nt<=1) || (essential_param_count!=4)){
			usage(argv);
		}
	}
}

