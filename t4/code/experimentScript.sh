#!/bin/bash

#### SCRIPT EXPERIMENTAL - MPI ####
###---------- PARTE EXPERIMENTAL -----------###
## Creacion de archivo para guardar el resultado de los tests para cada caso
output="result.out"
if [[ -f $output ]]; then #eliminalo si existe
	rm $output
fi
touch $output
###############################################################################

N=50000000
#---- INICIO TEST ----
for i in {1..16}; do # Casos de procesos a probar {1..16}
	for j in {1..10}; do  #10 veces para obtener un tiempo un poco más preciso
		./run.sh $i $N >> $output 
	done
	echo "---------------------------------------------------------" >> result.out
	#con este archivo podré hacer un promedio de los valores de cada caso
done


###------------- PARTE ESTADISTICA -----------###

secuential_time=(0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0) #length 16
parallel_time=(0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0)

count=0 	#contador de 2 lineas
arraycount=0 	#contador para el indice

while IFS= read -r line; do
		
	if [[ $line != \-* ]]; then #si no son las lineas con guion	
		count=$((count+1))
		if [[ $count -eq 1 ]];then
			secuential_time[$arraycount]=$( echo "${secuential_time[$arraycount]}+${line}" | bc -l)
		else #count es 2
			parallel_time[$arraycount]=$( echo "${parallel_time[$arraycount]}+${line}" | bc -l)
			count=0
		fi
	else #son guiones
		secuential_time[$arraycount]=$(echo "${secuential_time[$arraycount]}/10" | bc -l) 
		parallel_time[$arraycount]=$(echo "${parallel_time[$arraycount]}/10" | bc -l)
		arraycount=$((arraycount+1))
	fi

done < $output


#ARRAYS CON EL RESULTADO PROMEDIO DE CADA CASO 
echo "El array completo secuencial_time es: ${secuential_time[@]}"
echo "El array completo parallel_time es: ${parallel_time[@]}"

