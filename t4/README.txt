# Implementacion paralela de sumatoria trigonométrica 

## Descripción de los directorios y algunos archivos relevantes que se utilizaron para el experimento:

Directorio code/ :
- Dentro de este se encuentran el ejecutable tarea03, el archivo Makefile y los archivos fuente src/.

Directorio code/src/ :
- En este directorio encontraremos el código principal.

Archivo code/src/main.cc : 
- El archivo main.cc es el principal, este permite realizar la ejecución secuencial más la paralela del algoritmo distribuido en procesos.

Archivo code/src/sumaParalela : 
- Ejecutable del código principal que se encuentra en el directorio src/main.cc, generado luego de haber ejecutado el comando make y que sera usado para hacer experimentos de rendimiento.

Archivo code/experimentScript.sh :
- Este archivo permite realizar los experimentos, guardarlos en un archivo result.out y luego tomar este y realizar estadística de los tiempos promedios para cada caso secuencial y paralelo. 

Archivo code/run.sh : 
- Este archivo es un ejecutable bash que permite el uso de MPI de acuerdo al código principal.

**IMPORTANTE**
Antes de ejecutar el script experimentScript.sh, se debe comentar y descomentar las lineas de código que lo requieran del archivo main.cc (aparecen especificadas).

La estructura de este directorio es la siguiente:

```
/projects/smedinag/
	+ tarea04/
		+ code/
			- Makefile
			- run.sh
			+ src/
		- README.txt	
```

```
$ cd /projects/$USER/tarea04/code
$ make
$ ./run <P> <N> 
Salida de los experimentos realizados...
```

, donde ```<P>```: cantidad de procesos a utilizar, ```<N>```: cantidad de de número aleatorios a sumar.
El script ```run.sh``` es un cargador que tiene las llamadas correctar a MPI para ejecutar su programa.


