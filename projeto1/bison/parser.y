%code requires {
    #include "symbol_map.hpp"
}

%{
#include <cmath>
#include <iostream>
#include <unordered_map>

extern int yylex();
extern void yyerror(const char* s, ...);
%}

%code {
    symbol_map symbols;
}

%define parse.trace

/* yylval == %union
 * union informs the different ways we can store data
 */
%union {
    Type type;
    int value;
    char * var;
}

/* token defines our terminal symbols (tokens).
 */
%token <type> T_TYPE
%token <var> T_VAR
%token <value> T_NUMBER
%token T_PLUS T_TIMES T_DIVIDE T_MINUS T_OPAR T_CPAR T_ASSIGN T_COMMA T_NL

/* type defines the type of our nonterminal symbols.
 * Types should match the names used in the union.
 * Example: %type<node> expr
 */
%type <type> program lines line expr
%type <var> assignment
%type <int> opt_init

/* Operator precedence for mathematical operators
 * The latest it is listed, the highest the precedence
 * left, right, nonassoc
 */
//%left T_ASSIGN
%left T_PLUS T_MINUS
%left T_TIMES T_DIVIDE
%nonassoc T_OPAR T_CPAR
%nonassoc U_MINUS

/* Starting rule 
 */
%start program

%%

program: /*use ctrl+d to stop*/
    lines /*$$ = $1 when nothing is said*/
    ;

lines: 
    line /*$$ = $1 when nothing is said*/
    | lines line
    ;

line: 
    T_NL { $$ = 0; }
    | declaration T_NL { std::cout << "gg" << std::endl; }
    ;

expr:
    ;

declaration:
    T_TYPE T_VAR opt_init opt_others { symbols.assign($2, {$1, $3}); }
    ;

opt_init:
    T_ASSIGN T_NUMBER { $$ = $2; }
    |                 { $$ = 0; }
    ;

opt_others:
    T_COMMA declaration
    |
    ;

%%

