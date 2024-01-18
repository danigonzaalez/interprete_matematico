#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tabla_simbolos.h"
#include "analizador_sintactico.tab.h"
#include "lex.yy.h"

//funcion que cierra el fichero si esta abierto
extern void abrir_fichero(char *fichero);

//funcion que imprime la ayuda por pantalla
extern void imprimir_ayuda();

//funcion main del programa
int main(int argc, char *argv[]) {

    //inicializamos la tabla de simbolos con las operaciones y constantes
    inicializar_tabla();

    //mensaje de bienvenida
    printf("--------------- BIENVENIDO --------------"
    "\nPara que se impriman los resultados debes finalizar las sentencias con \";\""
    "\nDe lo contrario, las sentencias se ejecutarán igual pero no se imprimirán los resultados"
    "\nPara obtener toda la información inserta el comando de ayuda \"help()\"\n\n");
    
    if (argc == 3 && strcmp(argv[1], "-f") == 0) { //si se ejecutó con la opción -f cargamos el fichero
        abrir_fichero(argv[2]);
    } else if (argc == 2 || argc > 3) { //si se inserta un numero incorrecto de argumentos
        printf("Argumentos incorrectos...\n");
        destruir_tabla(); //destruimos la tabla de simbolos
        return 1; //salimos con codigo de error 1
    }

    //ejecutamos el analizador
    yyparse();

    //destruimos la tabla de simbolos
    destruir_tabla();
    
    //salimos
    return 0;
}
