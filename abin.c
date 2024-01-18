#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definiciones.h"

/////////////////////REPETIMOS LA DEFINICIÓN DE LOS TIPOS DE DATOS
//abin es un puntero a struct celda
typedef struct celda *abin;
//contenido de cada nodo del árbol

//union que nos permite uno de sus dos campos (numero decimal o una funcion) en la misma variable. Almacena el valor guardado
union Guardado {
    double valor;
    double (*funcion)();
    void (*comando)();
};

typedef union Guardado guardado;

//estructura de lo que se almecanara en cada uno de los nodos del arbol
typedef struct {
    guardado dato;
    char *lexema;
} tipoelem;

//estructura del nodo
struct celda {
	tipoelem info;
    int tipo;
	struct celda *izq, *der;
};

///////////////////////FUNCIONES

//Crea el árbol vacío
void crear(abin *A){
	*A=NULL;
}

//Comprueba si el árbol está vacío
unsigned esVacio(abin A){
	return (A==NULL);
}

//Destruye el árbol recursivamente
void destruir(abin *A){

	if(!esVacio(*A)){

	  destruir(&(*A)->izq); //funcion recursiva para subarbol izquierdo
      destruir(&(*A)->der); //funcion recursiva para subarbol derecho

      if ((*A)->info.lexema != NULL) { //libero el lexema y pongo a null
        free((*A)->info.lexema);
        (*A)->info.lexema = NULL;
      }

	  free(*A); //libero estructura del nodo
	  *A = NULL; //asigno null
	}	
}

//funcion que inserta un identificador con su valor. Si ya existe ese lexema, lo actualiza
void insertar_identificador(abin *A, char *lexema, double val) {
    //creamos el nodo
    if (esVacio(*A)) {
        *A = (abin)malloc(sizeof(struct celda));
        (*A)->info.lexema = (char*) malloc(strlen(lexema) + 1 * sizeof(char));
        strcpy((*A)->info.lexema, lexema);
        (*A)->info.lexema[strlen(lexema)] = '\0';
        (*A)->info.dato.valor = val;
        (*A)->tipo = ID;
        (*A)->izq = NULL;
        (*A)->der = NULL;
    //guiamos busqueda por la izquierda
    } else if (strcmp(lexema, (*A)->info.lexema) < 0) {
        insertar_identificador(&(*A)->izq, lexema, val);
    //guiamos busqueda por la derecha
    } else if (strcmp(lexema, (*A)->info.lexema) > 0) {
        insertar_identificador(&(*A)->der, lexema, val);
    //actualizamos el valor
    } else {
        (*A)->info.dato.valor = val;
    }
}

//funcion que inserta una funcion. Si ya existe ese lexema, lo actualiza
void insertar_funcion(abin *A, char *lexema, double (*func)()) {
    //creamos el nodo
    if (esVacio(*A)) {
        *A = (abin)malloc(sizeof(struct celda));
        (*A)->info.lexema = (char*) malloc(strlen(lexema) + 1 * sizeof(char));
        strcpy((*A)->info.lexema, lexema);
        (*A)->info.lexema[strlen(lexema)] = '\0';
        (*A)->info.dato.funcion = func;
        (*A)->tipo = FUNCION;
        (*A)->izq = NULL;
        (*A)->der = NULL;
    //guiamos busqueda por la izquierda
    } else if (strcmp(lexema, (*A)->info.lexema) < 0) {
        insertar_funcion(&(*A)->izq, lexema, func);
    //guiamos busqueda por la derecha
    } else if (strcmp(lexema, (*A)->info.lexema) > 0) {
        insertar_funcion(&(*A)->der, lexema, func);
    //actualizamos el valor
    } else {
        (*A)->info.dato.funcion = func;
    }
}

//funcion que inserta un comando. Si ya existe ese lexema, lo actualiza
void insertar_comando(abin *A, char *lexema, void (*cmd)()) {
    //creamos el nodo
    if (esVacio(*A)) {
        *A = (abin)malloc(sizeof(struct celda));
        (*A)->info.lexema = (char*) malloc(strlen(lexema) + 1 * sizeof(char));
        strcpy((*A)->info.lexema, lexema);
        (*A)->info.lexema[strlen(lexema)] = '\0';
        (*A)->info.dato.comando = cmd;
        (*A)->tipo = COMANDO;
        (*A)->izq = NULL;
        (*A)->der = NULL;
    //guiamos busqueda por la izquierda
    } else if (strcmp(lexema, (*A)->info.lexema) < 0) {
        insertar_comando(&(*A)->izq, lexema, cmd);
    //guiamos busqueda por la derecha
    } else if (strcmp(lexema, (*A)->info.lexema) > 0) {
        insertar_comando(&(*A)->der, lexema, cmd);
    //actualizamos el valor
    } else {
        (*A)->info.dato.comando = cmd;
    }
}

//funcion que inserta una constante. Si ya existe ese lexema, lo actualiza
void insertar_constante(abin *A, char *lexema, double val) {
    //creamos el nodo
    if (esVacio(*A)) {
        *A = (abin)malloc(sizeof(struct celda));
        (*A)->info.lexema = (char*) malloc(strlen(lexema) + 1 * sizeof(char));
        strcpy((*A)->info.lexema, lexema);
        (*A)->info.lexema[strlen(lexema)] = '\0';
        (*A)->info.dato.valor = val;
        (*A)->tipo = CONSTANTE;
        (*A)->izq = NULL;
        (*A)->der = NULL;
    //guiamos busqueda por la izquierda
    } else if (strcmp(lexema, (*A)->info.lexema) < 0) {
        insertar_constante(&(*A)->izq, lexema, val);
    //guiamos busqueda por la derecha
    } else if (strcmp(lexema, (*A)->info.lexema) > 0) {
        insertar_constante(&(*A)->der, lexema, val);
    //actualizamos el valor
    } else {
        (*A)->info.dato.valor = val;
    }
}

//funcion que devuelve el valor almacenado en el nodo
double recuperar(abin A, char *lexema) {
    if (strcmp(lexema, A->info.lexema) < 0) {
        return recuperar(A->izq, lexema);
    } else if (strcmp(lexema, A->info.lexema) > 0) {
        return recuperar(A->der, lexema);
    } else {
        return A->info.dato.valor;
    }
}

//funcion que comprueba si en el arbol existe el lexema con el tipo especificado. Si existe, guarda en el puntero control un 1, sino 0
void existe(abin A, char *lexema, int tipo, int *control) {
    if (esVacio(A)) { //si no esta el lexema
        *control = 0;
    } else if (strcmp(lexema, A->info.lexema) < 0) {
        existe(A->izq, lexema, tipo, control);
    } else if (strcmp(lexema, A->info.lexema) > 0) {
        existe(A->der, lexema, tipo, control);
    } else { //si se encontro el lexema
        if (A->tipo == tipo) { //si el tipo coincide
            *control = 1;
        } else { //no es el tipo de nodo que buscamos
            *control = 0;
        }
    }
}

//funcion privada que recorre el arbol para imprimirlo
void _imprimir(abin A) {
    if (!esVacio(A)) {

        //voy al subarbol izquierdo
        if (!esVacio(A->izq)) {
            _imprimir(A->izq);
        }

        //imprimo informacion del nodo dependiendo del tipo
        if (A->tipo == ID) {
            printf("Variable: %s\t Valor %f\n", A->info.lexema, A->info.dato.valor);

        } else if (A->tipo == FUNCION) {
            printf("Funcion: %10s\n", A->info.lexema);

        } else {
            printf("Constante: %s\t Valor %f\n", A->info.lexema, A->info.dato.valor);
        }

        //voy al subarbol derecho
        if (!esVacio(A->der)) {
            _imprimir(A->der);
        }
    }
}

//funcion que imprime el arbol
void imprimir_arbol(abin A) {
    printf("\n\n-------------------- TABLA DE SIMBOLOS --------------------\n");
    _imprimir(A);
    printf("---------------------------------------------------------------\n\n");
}

//funcion auxiliar que recorre el arbol e imprime las variables
void _imprimir_variables(abin A) {
    if (!esVacio(A)) {

        //voy al subarbol izquierdo
        if (!esVacio(A->izq)) {
            _imprimir_variables(A->izq);
        }

        //imprimo informacion del nodo si es una variable
        if (A->tipo == ID) {
            printf("Variable: %10s", A->info.lexema);
            printf("%10s: %-5f\n", "Valor", A->info.dato.valor);
        }

        //voy al subarbol derecho
        if (!esVacio(A->der)) {
            _imprimir_variables(A->der);
        }
    }
}

//funcion que imprime las variables del arbol
void imprimir_variables(abin A) {
    printf("\n\n-------------------- VARIABLES --------------------\n");
    _imprimir_variables(A);
    printf("---------------------------------------------------------------\n\n");
}

//funcion que busca la funcion con determinado lexema y la ejecuta para las entradas input1 e input2, guardando el resultado en el puntero valor
void funcion_dos_inputs(abin A, char *lexema, double input1, double input2, double *valor) {
    if (strcmp(lexema, A->info.lexema) < 0) {
        funcion_dos_inputs(A->izq, lexema, input1, input2, valor);
    } else if (strcmp(lexema, A->info.lexema) > 0) {
        funcion_dos_inputs(A->der, lexema, input1, input2, valor);
    } else {
        *valor = A->info.dato.funcion(input1, input2);
    }
}

//funcion que busca la funcion con determinado lexema y la ejecuta para la entrada input, guardando el resultado en el puntero valor
void funcion_un_input(abin A, char *lexema, double input, double *valor) {
    if (strcmp(lexema, A->info.lexema) < 0) {
        funcion_un_input(A->izq, lexema, input, valor);
    } else if (strcmp(lexema, A->info.lexema) > 0) {
        funcion_un_input(A->der, lexema, input, valor);
    } else {
        *valor = A->info.dato.funcion(input);
    }
}

//funcion que busca el comando con determinado lexema y lo ejecuta. No guarda ninguna salida
void funcion_sin_inputs(abin A, char *lexema) {
    if (strcmp(lexema, A->info.lexema) < 0) {
        funcion_sin_inputs(A->izq, lexema);
    } else if (strcmp(lexema, A->info.lexema) > 0) {
        funcion_sin_inputs(A->der, lexema);
    } else {
        A->info.dato.funcion();
    }
}

//funcion que elimina los nodos del arbol que almacenan una variable, liberando su memoria
void destruir_variables(abin *A, int *puntero) {
    int izq = 0, der = 0;
    if (!esVacio(*A)) {
        destruir_variables(&(*A)->izq, &izq);
        destruir_variables(&(*A)->der, &der);

        if (izq) {
            (*A)->izq = NULL;
        }
        if (der) {
            (*A)->der = NULL;
        }

        if ((*A)->tipo == ID) {
            free((*A)->info.lexema);
            (*A)->info.lexema = NULL;
            free(*A);
            *A = NULL;
        }
    }
}