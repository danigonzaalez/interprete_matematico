///////////////////////// INSTRUCCIONES DE COMPILACIÓN Y EJECUCIÓN ////////////////////

Para compilar bison y flex:
	- flex --header-file="lex.yy.h" analizador_lexico.l
	- bison -d -Wconflicts-sr analizador_sintactico.y
Una vez compilados, deben insertarse las cabeceras de las funciones e includes en los ficheros .h generados

Para compilar el programa usar el siguiente comando dentro del directorio con los códigos fuente:
	- gcc *.c -Wall -lm -o calculadora
	
_____________________________________________________

Para ejecutar el programa, se pueden usar las siguientes opciones:
	- -h: Se imprime la ayuda antes de ejecutar el intérprete
	- -f: Se carga un fichero con operaciones, por lo que a continuación debe insertarse el nombre del fichero con su extensión


////CORREGIR
- Añadir palabras reservadas a la tabla de simbolos para no tener que agregarlas al .l y recompilar (comandos.h). Esto es simplemente insertar unas nuevas
funciones que realicen lo que estaba en el .l pero que esten en una nueva libreria (lo mismo que con math.h)
- En el sintactico tambien quitar las reglas de los comandos y de forma similar a una funcion, recogerlas de la tabla de simbolos y ejecutarlas (comandos.h)
- Tener la funcion de imprimir ayuda en comandos.h
