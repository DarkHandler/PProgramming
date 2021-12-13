#!/bin/bash

#### SCRIPT EXPERIMENTAL - SPEEDUP - SORT V/S INTRINSICS Y SORT ####
###---------- PARTE EXPERIMENTAL -----------###
## Creacion de archivo para guardar el resultado de los tests para cada caso
input="result.out"
if [[ -f $input ]]; then #eliminalo si existe
	rm $input
fi
touch $input
###############################################################################
#Obtencion de los archivos de array dinamicos
arrayFileNameTest=$(ls ../array* | sed s/'..\/'//) #sed eliminara "../" y solo quedan los nombres de los archivos

#---- INICIO TEST ----
for fileName in $arrayFileNameTest; do
	for i in {1..10}; do  #10 veces para obtener un tiempo un poco más preciso
		#echo $fileName	
		./tarea02 --fname /projects/smedinag/tarea02/$fileName >> result.out 
	done
	echo "---------------------------------------------------------" >> result.out
	#con este archivo podré hacer un promedio de los valores de cada caso
done


###------------- PARTE ESTADISTICA -----------###

#Arrays en el cual se almacenaran los promedios para los casos 10e3, 10e4, 10e5, 10e6, 10e7
charge_time=(0 0 0 0 0)
total_avg_time_sort=(0 0 0 0 0)
total_avg_time_simdsort=(0 0 0 0 0)

count=0 	#contador de 2 lineas
arraycount=0 	#contador para el indice

while IFS= read -r line; do
		
	if [[ $line != \-* ]]; then #si no son las lineas con guion	
		count=$((count+1))
		if [[ $count -eq 1 ]];then
			charge_time[$arraycount]=$( echo "${charge_time[$arraycount]}+${line}" | bc -l)
		elif [[ $count -eq 2  ]];then
			total_avg_time_sort[$arraycount]=$( echo "${total_avg_time_sort[$arraycount]}+${line}" | bc -l)
			#echo ${t_total_avg[$arraycount]}
		else #count es 3
			total_avg_time_simdsort[$arraycount]=$( echo "${total_avg_time_simdsort[$arraycount]}+${line}" | bc -l)
			count=0
		fi
	else #son guiones
		charge_time[$arraycount]=$(echo "${charge_time[$arraycount]}/10" | bc -l) #los divido en 10 para sacar promedio del elemento
		total_avg_time_sort[$arraycount]=$(echo "${total_avg_time_sort[$arraycount]}/10" | bc -l) 
		total_avg_time_simdsort[$arraycount]=$(echo "${total_avg_time_simdsort[$arraycount]}/10" | bc -l)
		arraycount=$((arraycount+1))
	fi

done < $input


#ARRAYS CON EL RESULTADO PROMEDIO DE CADA CASO 
echo "El array completo charge_time es: ${charge_time[@]}"
echo "El array completo total_avg_time_sort es: ${total_avg_time_sort[@]}"
echo "El array completo total_avg_time_simdsort es: ${total_avg_time_simdsort[@]}"

