#include <stdio.h>
#include "errores.h"

void error_parametros() {
    printf("ERROR, parámetros incorrectos\n");
}

void error_fichero() {
    printf("ERROR, no se pudo abrir el fichero con el código fuente\n");
}

void error_lexico(int linea) {
    printf("Linea %d: ERROR, componente léxico no identificado\n", linea);
}