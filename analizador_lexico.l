%{

#include "tabla_simbolos.h"
#include "definiciones.h"
#include "errores.h"
#include "analizador_sintactico.tab.h"
    
//funcion que lee el fichero con las operaciones
void abrir_fichero(char *fichero);

//funcion que cierra el fichero con las operaciones si estaba abierto
void cerrar_fichero();

//funcion para mostrar los resultados despues de cada operacion
void mostrar_resultados();

//funcion para ocultar los resultados despues de cada operacion
void ocultar_resultados();

%}

%option noinput nounput noyywrap yylineno header-file="lex.yy.h"

NUEVALINEA \n
ESPACIO [ ]
SEPARADOR (\r|\t|{ESPACIO})+
DIGITO [0-9]

IDENTIFICADOR [a-zA-Z_][a-zA-Z0-9_]*

NUMERO_CON_DECIMALES {DIGITO}*\.{DIGITO}+
NUMERO_ENTERO {DIGITO}+
NUMERO_EXPONENCIAL ({NUMERO_CON_DECIMALES}|{NUMERO_ENTERO})[eE][+-]?{NUMERO_ENTERO}
NUMERO {NUMERO_CON_DECIMALES}|{NUMERO_ENTERO}|{NUMERO_EXPONENCIAL}

OPERADOR_SIMPLE [=+*/%^,.!><();-]

ARCHIVO [a-zA-Z0-9_]+\.[a-zA-Z0-9]+

%x LECTURA

%%

"exit"  {
        cerrar_fichero();
        yylex_destroy();
        yyterminate();
}

"load"  {
        BEGIN(LECTURA);
        return(LOAD);
        }

<LECTURA>{ARCHIVO}  {
                    yylval.cadena = (char *)malloc(strlen(yytext + 1));
                    strcpy(yylval.cadena, yytext);
                    yylval.cadena[strlen(yytext)] = '\0';
                    BEGIN(INITIAL);
                    return(ARCHIVO);
                    }


{SEPARADOR}

{NUEVALINEA} return ((int)*yytext);

{IDENTIFICADOR} {
                //reservo memoria
                yylval.cadena = (char *)malloc(strlen(yytext + 1) * sizeof(char));
                //copio la cadena
                strcpy(yylval.cadena, yytext);
                yylval.cadena[strlen(yytext)] = '\0';
                return(IDENTIFICADOR);
                }

{OPERADOR_SIMPLE} return ((int)*yytext);

{NUMERO}    {
            yylval.numero = atof(yytext);
            return(NUMERO);
            }

. error_lexico(yylineno);

<<EOF>> {
        cerrar_fichero();
        return '\n';
        }

%%

//variable para controlar si se ejecuto algun script
int script = 0; 

//funcion que abre un fichero
void abrir_fichero(char *fichero) {
    yyin = fopen(fichero, "r");
    if (!yyin) { //si error al abrir
        error_fichero(); //imprimimos error
        yyin = stdin; //entrada estandar
    } else {
        script = 1;
    }
}

//funcion que cierra el fichero si esta abierto
void cerrar_fichero() {
    if (script) {
        fclose(yyin);
        script = 0;
        yyrestart(stdin); //entrada estandar
    }
}
