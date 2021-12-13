# Medición del tiempo de ejecución (timing) de un algoritmo

## Descripción de los directorios y algunos archivos relevantes que se utilizaron para el experimento:

Directorio code/ :
- Dentro de este se encuentran los códigos utilizados para hacer el laboratorio de experimentos, los resultados y el ejecutable del código principal.
Directorio code/src/ :
- En este directorio encontraremos el código principal hecho en C junto a sus librerias y código objeto.
Archivo code/src/main.c :
- El archivo main.c es el principal para realizar la experimentación realizando operaciones y obteniendo la caraterización temporal de fragmentos de código.
Archivo code/experimScript.sh :
- Este archivo es un script ejecutable de bash, que permite ejecutar el experimento con todas las variables definidas para nt y nx (que se encuentran dentro de este), y de estos experimentos obtener un archivo con los resultados de estos.
Archivo code/result.out :
- Este archivo contiene los resultados de los experimentos realizados 10 veces con cada par nt y nx.
Archivo code/data-parse.sh :
- Este archivo permite procesar el archivo result.out y sacar el promedio de las 10 veces el par nt y nx para dar con un resultado más estadísitico y luego poder ser gráficado con otra herramienta. Este archivo solo devuelve un output del contenido de los array como resultado.

## Orden de ejecucion para la realizacion del experimento
- Requisito: tener testexec encontrado dentro del directorio code/ luego de haber hecho make
1.- Ejecutar experimScript.sh
2.- Ejecutar data-parse.sh


*** IMPORTANTE ***
- Antes de ejecutar el experimento, lo que se debe es modificar el archivo main.cc y comentando las lineas de codigo que dicen en su comentario "//Comentar para hacer el experimento" y se debe descomentar las que dicen "//Descomentar para hacer el experimento", en caso de no realizarse, el archivo data-parse.sh no se podra ejecutar y resultado de los experimento sera fallido.


La estructura del trabajo es la siguente:
```
/projects/smedinag/
        + tarea01/
                + code/
                        - Makefile
                        + src/
                - README.txt
```
