#include <global.h>
#include <checkEdges.h>

uint32_t checkEdge(bool** matrix, uint32_t i, uint32_t j, uint32_t nfil, uint32_t ncol){
        uint32_t neighbour_edge=0;
        if( (nfil>1) && (ncol>1) ){ //compruebo todos los casos bordes en un arreglo de mas de 1 dimension
                if( (i==0) && (j==0) ){
                        neighbour_edge+=matrix[0][1];
                        neighbour_edge+=matrix[1][0];
                        neighbour_edge+=matrix[1][1];
                }else{
                        if( (i==0) && (j==ncol-1) ){
                                neighbour_edge+=matrix[0][ncol-2];
                                neighbour_edge+=matrix[1][ncol-2];
                                neighbour_edge+=matrix[1][ncol-1];
                        }else{
                                if( (i==nfil-1) && (j==0) ){
                                        neighbour_edge+=matrix[nfil-2][0];
                                        neighbour_edge+=matrix[nfil-2][1];
                                        neighbour_edge+=matrix[nfil-1][1];
                                }else{
                                        if( (i==nfil-1) && (j==ncol-1) ){
                                                neighbour_edge+=matrix[nfil-1][ncol-2];
                                                neighbour_edge+=matrix[nfil-2][ncol-2];
                                                neighbour_edge+=matrix[nfil-2][ncol-1];
                                        }else{ //asignacion de 5 vecinos y se vienen 4 ifelse
                                                if( (i==0) && (0<j<ncol-1) ){
                                                        neighbour_edge+=matrix[i][j-1];
                                                        neighbour_edge+=matrix[i+1][j-1];
                                                        neighbour_edge+=matrix[i+1][j];
                                                        neighbour_edge+=matrix[i+1][j+1];
                                                        neighbour_edge+=matrix[i][j+1];
                                                }else{
                                                        if( (i==nfil-1) && (0<j<ncol-1) ){
                                                                neighbour_edge+=matrix[i][j-1];
                                                                neighbour_edge+=matrix[i-1][j-1];
                                                                neighbour_edge+=matrix[i-1][j];
                                                                neighbour_edge+=matrix[i-1][j+1];
                                                                neighbour_edge+=matrix[i][j+1];
                                                        }else{
                                                                if( (0<i<nfil-1) && (j==0) ){
                                                                        neighbour_edge+=matrix[i-1][j];
                                                                        neighbour_edge+=matrix[i-1][j+1];
                                                                        neighbour_edge+=matrix[i][j+1];
                                                                        neighbour_edge+=matrix[i+1][j+1];
                                                                        neighbour_edge+=matrix[i+1][j];
								}else{
                                                                        if( (0<i<nfil-1) && (j==ncol-1) ){
                                                                                neighbour_edge+=matrix[i-1][j];
                                                                                neighbour_edge+=matrix[i-1][j-1];
                                                                                neighbour_edge+=matrix[i][j-1];
                                                                                neighbour_edge+=matrix[i+1][j-1];
                                                                                neighbour_edge+=matrix[i+1][j];
                                                                        }else{
                                                                                return -1; //no cae en ninguna caso, no es borde y se hace recorrido normal -- esto es el valor maximo
                                                                        }

                                                                }
                                                        }
                                                }
                                        }
                                }

                        }
                }
        }else{ //caso especial arreglo 1 dimension
                if( (nfil==1) && (ncol>1) ){ //tambien veo los bordes de estos
                        if(j==0){
                                neighbour_edge+=matrix[0][1];
                        }else{
                                if(j==ncol-1){
                                        neighbour_edge+=matrix[0][ncol-2];
                                }else{//ya que es 1 dimension tiene a la izquierda y derecha
                                        neighbour_edge+=matrix[0][j-1] + matrix[0][j+1];
                                }
                        }
                }else{
                        if( (nfil>1) && (ncol==1) ){
                                if(i==0){
                                        neighbour_edge+=matrix[1][0];
                                }else{
                                        if(i==nfil-1){
                                                neighbour_edge+=matrix[nfil-2][0];
                                        }else{//ya que es 1 dimension tiene a la izquierda y derecha
                                                neighbour_edge+=matrix[i-1][0] + matrix[i+1][0];
                                        }
                                }
                        }
                }
        }
 	return neighbour_edge; //si retorna -1, no cae en ningun caso
}

