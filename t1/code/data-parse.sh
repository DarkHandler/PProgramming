#!/bin/bash

input="./result.out" #archivo a procesar para calcular los promedios

### *** IMPORTANTE *** --> Para que funcione este script debe leer la seccion IMPORTANTE del archivo README.txt
### Explicación
## Estos 3 array definidos debajo almacenan en su indice el promedio de las veces (10 en el caso de mi experimento) que un valor nt y nx
## fueron ejecutados como parámetros en el código principal (main.cc). 
## Ejemplos de esto sería que en el indice 0 de los 3 arreglos, almacenan el promedio del primer caso que es nt=15000 y nx=10000, el indice 2
## es para el caso nt=15000 y nx=20000, indice 3 nt=15000 y nx=30000 y asi sucesivamente.
#Donde despues el indice 6 es nt=30000 y nx=10000.


t_total_avg=(0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0) 	#tiempo ejecucion promedio del algoritmo
t_ite_avg=(0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0)  		#tiempo de ejecucion promedio de una iteracion del algoritmo
t_elem_avg=(0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0)		#tiempo de ejecucion promedio del computo de un elemento del algoritmo

count=0 ##contador de 3 lineas
arraycount=0 #contador de resultado nt y nx
guioncount=0 #contador de lineas guion
while IFS= read -r line; do
	if [[ $line != \-* ]]; then #si no son las lineas con guion
		line=$(sed -E 's/([+-]?[0-9.]+)[eE]\+?(-?)([0-9]+)/(\1*10^\2\3)/g' <<<"$line") #expresion regular para convertir de notacion cientifica e+10 o e-10 a 10^
		#echo $line
		guioncount=0
		count=$((count+1))
		if [[ $count -eq 1 ]]; then
			t_total_avg[$arraycount]=$( echo "${t_total_avg[$arraycount]}+${line}" | bc -l)
			#echo ${t_total_avg[$arraycount]}
		elif [[ $count -eq 2 ]]; then 
			t_ite_avg[$arraycount]=$(echo "${t_ite_avg[$arraycount]}+${line}" | bc -l)
			#echo ${t_ite_avg[$arraycount]}
		elif [[ $count -eq 3 ]]; then
			t_elem_avg[$arraycount]=$(echo "${t_elem_avg[$arraycount]}+${line}" | bc -l) #sumatoria de veces que se hizo que son 10
			#echo ${t_elem_avg[$arraycount]}
			count=0
		fi
	else 
		if [[ $guioncount -eq 0 ]];then
			t_total_avg[$arraycount]=$(echo "${t_total_avg[$arraycount]}/10" | bc -l) #los divido en 10 para sacar promedio del elemento
			t_ite_avg[$arraycount]=$(echo "${t_ite_avg[$arraycount]}/10" | bc -l)
			t_elem_avg[$arraycount]=$(echo "${t_elem_avg[$arraycount]}/10" | bc -l)
			arraycount=$((arraycount+1))
		fi
		guioncount=$guioncount+1
	fi
done < $input


#ARRAYS CON EL RESULTADO PROMEDIO DE CADA PAR nt Y nx 
echo "El array completo t_total_avg es: ${t_total_avg[@]}"
echo "El array completo t_ite_avg es: ${t_ite_avg[@]}"
echo "El array completo t_elem_avg es: ${t_elem_avg[@]}"
