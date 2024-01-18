
#ifndef COMPILADORES_PRACTICA1_TABLA_SIMBOLOS_H
#define COMPILADORES_PRACTICA1_TABLA_SIMBOLOS_H

//funcion que crea la tabla de simbolos y va insertando todas las palabras reservadas en el
void inicializar_tabla();

//funcion para insertar un identificador en la tabla
void insertar_identificador_tabla(char *lexema, double val);

//funcion que comprueba en la tabla si existe un elemento con el tipo y lexema insertados
int existe_elemento_tabla(char *lexema, int tipo);

//funcion que devuelve el valor del lexema insertado
double obtener_valor_tabla(char *lexema);

//funcion que ejecuta una funcion con un unico input y devuelve el resultado
double ejecutar_funcion_un_input(char *lexema, double input);

//funcion que ejecuta una funcion con dos inputs y devuelve el resultado
double ejecutar_funcion_dos_input(char *lexema, double input1, double input2);

//funcion que ejecuta un comando
void ejecutar_comando(char *lexema);

//funcion que limpia el worspace
void limpiar_workspace();

//funcion que imprime la tabla de simbolos
void imprimir_tabla();

//funcion que imprime las variables de la tabla de simbolos
void imprimir_variables_tabla();

//funcion que destruye la tabla de simbolos
void destruir_tabla();

#endif //COMPILADORES_PRACTICA1_TABLA_SIMBOLOS_H
