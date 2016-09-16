%code requires {
    #include "symbol_map.hpp"
    #include "SyntaxTree.hpp"
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
    polska::NodePtr node;
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
%type <node> expr command assignment program lines line expr variable
%type <var>  opt_others declaration
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
    | command T_NL
    ;

command:
    declaration
    | assignment
    ;

declaration:
    T_TYPE T_VAR opt_init opt_others { Types::register(T_TYPE); symbols.assign($2, {$1, $3}); }
    ;

variable:
    T_VAR { $$ = polska::Node::create($1); }
    ;

assignment:
    variable T_ASSIGN expr { $$ = polska::Node::create(polska::Operator::ASSIGN, $1, $3); }
    ;

opt_init:
    T_ASSIGN T_NUMBER { $$ = $2; }
    | { $$ = 0; }
    ;

expr:
    T_NUMBER { $$ = polska::Node::create(std::to_string($1)); }
    | expr T_PLUS expr { $$ = polska::Node::create(polska::Operator::PLUS, $1, $3); }
    | expr T_MINUS expr { $$ = polska::Node::create(polska::Operator::MINUS, $1, $3); }
    | expr T_TIMES expr { $$ = polska::Node::create(polska::Operator::TIMES, $1, $3); }
    | expr T_DIVIDE expr { $$ = polska::Node::create(polska::Operator::DIVIDE, $1, $3); }
    | T_MINUS expr %prec U_MINUS { $$ = polska::Node::create(polska::Operator::MINUS, $2); }
    | T_OPAR expr T_CPAR { $$ = polska::Node::create(polska::Operator::PAR, $2); }
    ;


opt_others:
    T_COMMA typeless_declaration
    |
    ;

%%

