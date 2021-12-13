# Implementacion paralela de Game Of Life 

## Descripción de los directorios y algunos archivos relevantes que se utilizaron para el experimento:

Directorio code/ :
- Dentro de este se encuentran el ejecutable tarea03, el archivo Makefile y los archivos fuente src/.

Directorio code/src/ :
- En este directorio encontraremos el código principal y otros códigos que se acoplan a este principal. Estos estan hechos en C++ junto a algunas librerias definidas por mi y código objeto obj/.

Archivo code/src/main.cc : 
- El archivo main.cc es el principal, este permite realizar la ejecucion secuencial del algoritmo y la version secuencial más paralela. Este código posee varias opciones de parámetro que permitiran mostrar más al detalle el funcionamiento del algoritmo y además mostrar las estadísticas de comparación de SpeedUp por el tamaño del problema, número de thread y número de generaciones.

Archivo code/src/validateArgs.cc : 
- Este archivo contiene la función encargada de validar el paso los argumentos (aún no es aprueba de todos los errores humanos)

Archivo code/src/checkEdges.cc : 
- Este archivo también contiene una función la verfica si la celula actual esta en un borde. Si esto es así, lo que se hace es calcular de distinta forma la cantidad de vecinos vivos que posee, dependiendo de en que borde se encuentre, las cuales pueden ser esquinas, arriba, abajo, derecha e izquierda. En caso de no ser borde se retorna -1 que vendría a ser el mayor valor de un uint32, haciendole saber al código principal que se debe calcular de forma normal, con sus 8 vecinos.

Archivos code/tarea03:
- Ejecutable del código principal que se encuentra en el directorio src/main.cc, generado luego de haber ejecutado el comando make y que sera usado para hacer experimentos de rendimiento.

**IMPORTANTE**
Se debe leer bien el uso de las opciones del código.

La estructura de este directorio es la siguiente:

```
/projects/smedinag/
	+ tarea03/
		+ code/
			- Makefile
			+ src/
		- README.txt	
```

Una vez compilado sin errores, se ejecutará con la secuencia:

```
$ cd /projects/smedinag/tarea03/code
$ make
$ ./tarea03 --ncol ... --nfil ... --nt ... --plive ... --seq --show
Salida de los experimentos realizados...
```

