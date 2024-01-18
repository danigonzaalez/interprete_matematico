#ifndef ABIN_H
#define ABIN_H
//Interfaz del TAD abin

//definición del tipo opaco
typedef void *abin;

/////////////////////////////// FUNCIONES

//crea el arbol vacio
void crear(abin *A);

//comprueba si el arbol esta vacio
unsigned esVacio(abin A);

//destruye el arbol recursivamente
void destruir(abin *A);

//funcion que inserta un identificador con su valor. Si ya existe ese lexema, lo actualiza
void insertar_identificador(abin *A, char *lexema, double val);

//funcion que inserta una funcion. Si ya existe ese lexema, lo actualiza
void insertar_funcion(abin *A, char *lexema, double (*func)());

//funcion que inserta un comando. Si ya existe ese lexema, lo actualiza
void insertar_comando(abin *A, char *lexema, void (*cmd)());

//funcion que inserta una constante. Si ya existe ese lexema, lo actualiza
void insertar_constante(abin *A, char *lexema, double val);

//funcion que devuelve el valor almacenado en el nodo
double recuperar(abin A, char *lexema);

//funcion que comprueba si en el arbol existe el lexema con el tipo especificado. Si existe, guarda en el puntero control un 1, sino 0
void existe(abin A, char *lexema, int tipo, int *control);

//funcion que imprime el arbol
void imprimir_arbol(abin A);

//funcion que imprime las variables del arbol
void imprimir_variables(abin A);

//funcion que busca la funcion con determinado lexema y la ejecuta para las entradas input1 e input2, guardando el resultado en el puntero valor
void funcion_dos_inputs(abin A, char *lexema, double input1, double input2, double *valor);

//funcion que busca la funcion con determinado lexema y la ejecuta para la entrada input, guardando el resultado en el puntero valor
void funcion_un_input(abin A, char *lexema, double input, double *valor);

//funcion que busca el comando con determinado lexema y lo ejecuta. No guarda ninguna salida
void funcion_sin_inputs(abin A, char *lexema);

//funcion que elimina los nodos del arbol que almacenan una variable, liberando su memoria
void destruir_variables(abin *A, int *puntero);

#endif	// ABIN_H
