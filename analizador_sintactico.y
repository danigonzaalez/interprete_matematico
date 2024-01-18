%{

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "definiciones.h"
#include "tabla_simbolos.h"
#include "comandos.h"
#include "lex.yy.h"

extern int yylex();

//variable para controlar si se ejecuto algun script
extern int script;

//variable para control la impresion por pantalla de las operaciones
extern int imprimir;

//funcion que lee el fichero con las operaciones
extern void abrir_fichero(char *fichero);

//funcion para activar impresion
extern void mostrar_resultados();

//funcion para desactivar impresion
extern void ocultar_resultados();

//impresion de errores
extern void yyerror(char* s);

//funcion que imprime la ayuda por pantalla
extern void imprimir_ayuda();

%}

//para guardar o numeros o cadenas
%union {
    char *cadena;
    double numero;
};

%start input

%token <numero> NUMERO
%token <cadena> IDENTIFICADOR
%token <cadena> ARCHIVO

%token IMPRIMIR
%token ON
%token OFF
%token WORKSPACE
%token TABLA
%token HELP
%token CLEAR
%token LOAD

%precedence '='
%left '+' '-'
%left '*' '/'
%left '%'
%right '^'
%precedence NEG

%type <numero> expresion
%type <numero> asignacion
%type <numero> operacion
%type <numero> funcion

%%

input: %empty {printf(">> ");}
    | input line
;

line:
    '\n' {printf("\n>> ");}
    | expresion '\n' {if (imprimir) { if (!isnan($1)) { printf("%lf\n", $1); } } if (!script) {printf("\n>> ");} }
    | expresion ';' '\n' {if (!isnan($1)) { printf("%lf\n", $1);} if (!script) {printf("\n>> ");} }
    | error {printf(">> ");}
;

expresion:
    NUMERO {$$ = $1;}
    | IDENTIFICADOR {if (existe_elemento_tabla($1, ID) || existe_elemento_tabla($1, CONSTANTE)) {$$ = obtener_valor_tabla($1);}
                    else {yyerror("variable sin inicializar"); $$ = NAN;} free($1);}
    | asignacion
    | operacion
    | funcion
    | '(' expresion ')' {$$ = $2;}
    | LOAD ARCHIVO {printf("Ejecutando fichero %s\n", $2); $$ = NAN; abrir_fichero($2); free($2);}
;

asignacion:
    IDENTIFICADOR '=' expresion {if (!existe_elemento_tabla($1, CONSTANTE)) {insertar_identificador_tabla($1, $3); $$ = $3;}
                                else {yyerror("no se puede modificar una constante"); $$=NAN;} free($1);}
;

operacion:
    expresion '+' expresion {$$ = $1 + $3;}
    | expresion '-' expresion {$$ = $1 - $3;}
    | expresion '*' expresion {$$ = $1 * $3;}
    | expresion '/' expresion { if ($3 != 0) {$$ = $1 / $3;} else {yyerror("division por 0"); $$ = NAN;}}
    | expresion '%' expresion {$$ = (int)$1 % (int)$3;}
    | '-' expresion %prec NEG {$$ = -$2;}
    | '+' expresion %prec NEG {$$ = $2;}
;

funcion:
    IDENTIFICADOR '(' expresion ')' {if (existe_elemento_tabla($1, FUNCION)) {
                                    $$ = ejecutar_funcion_un_input($1, $3);
                                    } else {yyerror("funcion no reconocida"); $$ = NAN;} free($1);}
    | IDENTIFICADOR '(' expresion ',' expresion ')' {if (existe_elemento_tabla($1, FUNCION)) {
                                    $$ = ejecutar_funcion_dos_input($1, $3, $5);
                                    } else {yyerror("funcion no reconocida"); $$ = NAN;} free($1);}
    | IDENTIFICADOR '(' ')' {if (existe_elemento_tabla($1, COMANDO)) {
                                    $$ = NAN; ejecutar_comando($1);
                                    } else {yyerror("comando no reconocido"); $$ = NAN;} free($1);}
    | expresion '^' expresion {if (existe_elemento_tabla("^", FUNCION)) {
                                    $$ = ejecutar_funcion_dos_input("^", $1, $3);
                                    } else {yyerror("funcion no reconocida"); $$ = NAN;}}
;

%%

void yyerror(char *s) {
    printf("Error: %s\n", s);
}
