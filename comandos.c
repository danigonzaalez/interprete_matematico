#include <stdio.h>
#include <stdlib.h>
#include "tabla_simbolos.h"

int imprimir = 0;

//para imprimir workspace
void cmd_workspace() {
    imprimir_variables_tabla();
}

//para imprimir tabla de simbolos
void cmd_table() {
    imprimir_tabla();
}

//para limpiar el workspace
void cmd_clear() {
    limpiar_workspace();
}

//para activar impresion
void cmd_echo_on() {
    imprimir = 1;
}

//para desactivar impresion
void cmd_echo_off() {
    imprimir = 0;
}

//para imprimir ayuda
void cmd_help() {
    printf("\n\n------------- INTÉRPRETE MATEMÁTICO ------------\n"
    "Este es un intérprete matemático que soporta operaciones y funciones básicas\n"
    "------------- PALABRAS CLAVE ------------\n"
    "\t\"table()\": imprimir la tabla de símbolos\n"
    "\t\"workspace()\": imprimir las variables declaradas\n"
    "\t\"clear()\": elimina el workspace de forma que se pierden las variables declaradas\n"
    "\t\"load()\": cargar un archivo \"load nombre.extensión\"\n"
    "\t\"echoon()\": activar impresión\n"
    "\t\"echooff()\": desactivar impresión\n"
    "\t\"exit()\": salir\n"
    "\t\"help()\": imprimir la ayuda\n"
    "------------- DECLARAR VARIABLES ------------\n"
    "Para declarar una variable se debe hacer uso del operador \"=\"\n"
    "Las variables deben ser cadenas alfanuméricas y deben empezar por un caracter o guión bajo\n"
    "------------- CONSTANTES ------------\n"
    "\t\"pi\": almacena el valor 3.141592\n"
    "\t\"e\": almacena el valor 2.718282\n"
    "------------- FUNCIONES DE UN PARÁMETRO------------\n"
    "\t\"sqrt()\": función raíz cuadrada\n"
    "\t\"sin()\": función seno\n"
    "\t\"cos()\": función coseno\n"
    "\t\"tan()\": función tangente\n"
    "\t\"asin()\": función arcsen\n"
    "\t\"acos()\": función arccos\n"
    "\t\"atan()\": función arctan\n"
    "\t\"ln()\": función logaritmo neperiano\n"
    "\t\"log10()\": función logaritmo en base 10\n"
    "\t\"exp()\": función exponencial\n"
    "\t\"fabs()\": función valor absoluto\n"
    "------------- FUNCIONES DE DOS PARÁMETROS------------\n"
    "\t\"mod(,)\": calcula el un número en determinado módulo\n"
    "\t\"^\": eleva una base a un exponente\n"
    );
}