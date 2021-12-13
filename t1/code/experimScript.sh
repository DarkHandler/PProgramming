#!/bin/bash

#### SCRIPT EXPERIMENTAL PARA LA CARACTERIZACION DEL TIEMPO DE EJECUCION ####
## Creacion de archivo para guardar el resultado de los tests para cada caso
if [[ -f "result.out" ]]; then #eliminalo si existe
	rm result.out
fi
touch result.out
###############################################################################
#Definicion de array de casos
arrayTestNt=(15000 30000 45000 60000 75000)
arrayTestNx=(10000 20000 30000 40000 50000)

#---- INICIO TEST ----

for elemNt in "${arrayTestNt[@]}"; do 
	for elemNx in "${arrayTestNx[@]}"; do 
		for i in {1..10}; do  #10 veces para obtener un tiempo un poco más preciso
			./testexec -nt $elemNt -nx $elemNx  >> result.out 
		done
		echo "---------------------------------------------------------" >> result.out
		#con este archivo podré hacer un promedio de los valores de cada caso
	done
done

