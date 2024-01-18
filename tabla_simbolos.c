
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tabla_simbolos.h"
#include "definiciones.h"
#include "abin.h"
#include "comandos.h"

abin tabla; //tabla de simbolos global

//funcion que crea la tabla e introduce las palabras reservadas
void inicializar_tabla() {
    //creo la tabla
    crear(&tabla);
    //inserto constantes
    insertar_constante(&tabla, "pi", 3.141592);
    insertar_constante(&tabla, "e", 2.718282);
    //inserto las funciones
    insertar_funcion(&tabla, "^", pow);
    insertar_funcion(&tabla, "mod", fmod);
    insertar_funcion(&tabla, "sin", sin);
    insertar_funcion(&tabla, "asin", asin);
    insertar_funcion(&tabla, "cos", cos);
    insertar_funcion(&tabla, "acos", acos);
    insertar_funcion(&tabla, "tan", tan);
    insertar_funcion(&tabla, "atan", atan);
    insertar_funcion(&tabla, "ln", log);
    insertar_funcion(&tabla, "log10", log10);
    insertar_funcion(&tabla, "exp", exp);
    insertar_funcion(&tabla, "sqrt", sqrt);
    insertar_funcion(&tabla, "fabs", fabs);
    //inserto los comandos
    insertar_comando(&tabla, "workspace", cmd_workspace);
    insertar_comando(&tabla, "table", cmd_table);
    insertar_comando(&tabla, "clear", cmd_clear);
    insertar_comando(&tabla, "echoon", cmd_echo_on);
    insertar_comando(&tabla, "echooff", cmd_echo_off);
    insertar_comando(&tabla, "help", cmd_help);
}

//funcion para insertar un identificador en la tabla
void insertar_identificador_tabla(char *lexema, double val) {
    insertar_identificador(&tabla, lexema, val);
}

//funcion que comprueba en la tabla si existe un elemento con el tipo y lexema insertados
int existe_elemento_tabla(char *lexema, int tipo) {
    int esta = 0;
    existe(tabla, lexema, tipo, &esta);
    return esta;
}

//funcion que devuelve el valor del lexema insertado
double obtener_valor_tabla(char *lexema) {
    return recuperar(tabla, lexema);
}

//funcion que ejecuta una funcion con un unico input y devuelve el resultado
double ejecutar_funcion_un_input(char *lexema, double input) {
    double resultado = 0.0;
    funcion_un_input(tabla, lexema, input, &resultado);
    return resultado;
}

//funcion que ejecuta una funcion con dos inputs y devuelve el resultado
double ejecutar_funcion_dos_input(char *lexema, double input1, double input2) {
    double resultado = 0.0;
    funcion_dos_inputs(tabla, lexema, input1, input2, &resultado);
    return resultado;
}

//funcion que ejecuta un comando
void ejecutar_comando(char *lexema) {
    funcion_sin_inputs(tabla, lexema);
}

//funcion que limpia el worspace
void limpiar_workspace() {
    int control = 0;
    destruir_variables(&tabla, &control);
}

//funcion que imprime la tabla de simbolos
void imprimir_tabla() {
    imprimir_arbol(tabla);
}

//funcion que imprime las variables de la tabla de simbolos
void imprimir_variables_tabla() {
    imprimir_variables(tabla);
}

//funcion que destruye la tabla de simbolos
void destruir_tabla() {
    destruir(&tabla);
}
