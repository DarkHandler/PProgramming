# Ordenamiento de arreglo de enteros con SIMD

## Descripción de los directorios y algunos archivos relevantes que se utilizaron para el experimento:

Directorio code/ :
- Dentro de este se encuentran los códigos utilizados para hacer el laboratorio de experimentos, los resultados y el ejecutable del código principal.

Directorio code/src/ :
- En este directorio encontraremos el código principal hecho en C++ junto a sus librerias y código objeto.

Archivo code/src/main.c : 
- El archivo main.cc es el principal, este permite realizar las operaciones necesarias de ejecución de la función sort y SIMD y el resultado de la medición del tiempo de ejecición de estos para sus posteriores experimentaciones de acuerdo al desempeño temporal que se verá en este trabajo.

Archivos code/tarea02:
- Ejecutable del código principal que se encuentra en el directorio src/main.cc, generado luego de haber ejecutado el comando make.

Archivo code/experimentScript.sh :
- Este archivo es un script ejecutable de bash, que permite ejecutar los experimentos pasando por dos partes, la fase de obtención de métricas temporales almacenadas en un archivo llamado result.out y la parte estadística que permite obtener el promedio de las 10 veces qe se ejecutan los valores temporales que nos arrojan los experimentos guarados en el archivo mencionado.

Archivo code/result.out :
- Este archivo contiene los resultados de los experimentos realizados 10 veces para cada uno de los archivos definidos como array, los cuales están estructurados para obtener arreglos de tamaño {10³,10⁴,10⁵,10⁶,10⁷} respectivamente.

Archivo code/arrayGenerator.cc:
- Es un código escrito para generar archivos en representación a arreglos del tamaño que se le pase como parámetro, estructurados de tal forma que puedan ser leídos por el código principal (src/main.cc).

Archivo code/generator:
- Este es el ejecutable que se genero posteriormente al haber realizado la compilación del código arrayGenerator.cc, osea que se ejecuto g++ -o generator arrayGenerator.cc.

Archivos arrayData-{valores}.txt:
- Archivos generados tras haber ejecutado el ejecutable generator, donde {valores} son los tamaños de los arreglos que se necesitaban para realizar los experimentos.

*** IMPORTANTE ANTES DE LEER EL ORDEN DE EJECUCIÓN ***
- Antes de ejecutar los experimentos, lo que se debe hacer es modificar el archivo main.cc, para luego comentar y descomentar las lineas de codigo, es decir comentar las que poseen el comentario "//Comentar para hacer el experimento {1 o 2}" y se debe descomentar las que dicen "//Descomentar para hacer el experimento {1 o 2}", cada una para el respectivo caso del experimento que se desea ejecutar, en caso de no realizarse, el archivo experimentScript.sh no se podra ejecutar y resultado de los experimento sera fallido.


## Orden de ejecucion para realizar cualquiera de los dos experimentos {1 o 2}
1.-  Modificar el archivo main.cc para comentar o descomentar las lineas que pertenezcan al experimento respectivo (detallado en el código)
2.-  Ejecutar el comando make en el directorio code/ 
3.-  Ejecutar el script experimentScript.sh

Cabe destacar que hay unas líneas que se pueden descomentar dentro del archivo main.cc cuando no se ejecuta el experimento, que sirven para mostrar información detallada de lo que hace main.cc (o en sí el ejecutable code/tarea02 generado luego del make).


La estructura de este directorio es la siguiente:

```
/projects/smedinag/
	+ tarea02/
		+ code/
			- Makefile
			+ src/
		- README.txt	
```

Una vez compilado sin errores, se ejecutará con la secuencia:

```
$ cd /projects/smedinag/tarea02/code
$ make
$ ./tarea02 --fname /projects/smedinag/tarea02/arrayData-{valores}.txt	
Salida de los experimentos realizados...
```
Donde {valores} son {10³,10⁴,10⁵,10⁶,10⁷}.

