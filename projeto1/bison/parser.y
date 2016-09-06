%{
#include <cmath>
#include <iostream>
#include <unordered_map>

extern int yylex();
extern void yyerror(const char* s, ...);
%}

%code requires{
    enum class Type {
        INT
    };
}

%define parse.trace

/* yylval == %union
 * union informs the different ways we can store data
 */
%union {
    Type type;
}

/* token defines our terminal symbols (tokens).
 */
%token <type> T_TYPE
%token <var> T_VAR
%token T_PLUS T_TIMES T_DIVIDE T_MINUS T_OPAR T_CPAR T_ASSIGN T_NL

/* type defines the type of our nonterminal symbols.
 * Types should match the names used in the union.
 * Example: %type<node> expr
 */
%type <type> program lines line expr
%type <var> assignment

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

%code {
    std::unordered_map<char, complex> vars;
}

%%

program: /*use ctrl+d to stop*/
    lines /*$$ = $1 when nothing is said*/
    ;

lines: 
    line /*$$ = $1 when nothing is said*/
    | lines line
    ;

line: 
    T_NL { $$ = {0, 0} /*NULL*/; } /*nothing here to be used */
    | expr T_NL { std::cout << "Res: " << $1.real << " + " << $1.imag << 'i' << std::endl; }
    ;

expr:
    ;

%%

