///////////////////////// INSTRUCCIONES DE COMPILACIÓN Y EJECUCIÓN ////////////////////

Para compilar bison y flex:
	- flex --header-file="lex.yy.h" analizador_lexico.l
	- bison -d -Wconflicts-sr analizador_sintactico.y
Una vez compilados, deben insertarse las cabeceras de las funciones e includes en los ficheros .h generados

Para compilar el programa usar el siguiente comando dentro del directorio con los códigos fuente:
	- gcc *.c -Wall -lm -o calculadora

Se recomienda utilizar el MakeFile proporcionado para realizar la compilación de forma más directa y sencilla, y usar la opción -h del intérprete para ver la ayuda.
	
_____________________________________________________

Para ejecutar el programa, se pueden usar las siguientes opciones:
	- -h: Se imprime la ayuda antes de ejecutar el intérprete
	- -f: Se carga un fichero con operaciones, por lo que a continuación debe insertarse el nombre del fichero con su extensión
