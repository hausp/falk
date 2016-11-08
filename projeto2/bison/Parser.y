%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0"
%defines
%define parser_class_name { Parser }

%define api.token.constructor
%define api.value.type variant
%define parse.assert
%define api.namespace { falk }

%code requires {
    #include <iostream>
    #include <string>
    #include <cstdint>
    #include "base/definitions.hpp"

    namespace falk {
        class Scanner;
        class Driver;
    }
}

%code top {
    #include <iostream>
    #include "base/Driver.hpp"
    #include "Scanner.hpp"
    #include "Parser.hpp"
    #include "location.hh"
    
    static falk::Parser::symbol_type yylex(falk::Scanner &scanner) {
        return scanner.get_next_token();
    }
}

%lex-param { falk::Scanner &scanner }
%parse-param { falk::Scanner &scanner }
%parse-param { falk::Analyser &analyser }
%parse-param { falk::Driver &driver }
%locations
%define parse.trace
%define parse.error verbose

%define api.token.prefix {TOKEN_}

%token<std::string> ID "variable identifier";
%token <falk::Type> TYPE "type identifier";
%token <falk::numeric> NUMERIC "numeric value";
%token <falk::boolean> BOOL "boolean value";

%token VAR    "var keyword";
%token ARRAY  "array keyword";
%token MATRIX "matrix keyword";
%token TYPEOF "typeof operator";
%token SEMICOLON "semicolon";
%token NL "new line";
%token IF "if keyword";
%token THEN "then keyword";
%token ELSE "else keyword";
%token FOR "for keyword";
%token WHILE "while keyword";
%token IN "in keyword";
%token RET "return keyword";
%token FUN "function keyword";
%token ASSIGN "=";
%token COMMA ";";
%token OPAR "("
%token CPAR ")"
%token COLON ":"
%token DOT "."
%token OBRACKET "["
%token CBRACKET "]"
%token EOF 0 "end of file"

%token <falk::op::Arithmetical> PLUS MINUS TIMES DIVIDE POWER MOD
%token <falk::op::Comparison> COMPARISON
%token <falk::op::Logical> AND OR NOT


// %type<int> eoc opt_nl
%type<int> program line lines command commands new_line
// %type <int> assignment arr_size mat_size simple_id id index op
%type <falk::numeric> numeric_expr single_calc
// %type <falk::complex> complex_expr complex_calc
// %type <falk::rvalue> rvalue expr

/* Operator precedence for mathematical operators
 * The latest it is listed, the highest the precedence
 * left, right, nonassoc
 */
%left T_AND T_OR
%nonassoc T_NOT
%left T_COMPARISON
%left T_PLUS T_MINUS
%left T_TIMES T_DIVIDE T_MOD
%left T_POWER
%nonassoc U_MINUS
%nonassoc T_OPAR T_CPAR

%start program

%%

program     : %empty        { $$ = 0; }
            | program lines { $$ = 0; }
            // | program function 
            ;

lines       : line       { /* TODO: create lines with line */ }
            | lines line { /* TODO: add line to lines */ }

line        : new_line
            | commands new_line

new_line    : NL { analyser.new_line(); }

commands    : command
            | commands SEMICOLON command
            ;

command     : %empty       { $$ = 0; }
            | single_calc  { $$ = 0; }
            ;

// var_decl    : VAR ID
//             | VAR ID COLON TYPE /* Aqui pode dar ruim */
//             | VAR ID ASSIGN rvalue
//             | ARRAY arr_size ID
//             | ARRAY ID ASSIGN rvalue
//             | MATRIX mat_size ID
//             | MATRIX ID ASSIGN rvalue
//             ;

// assignment  : id ASSIGN rvalue
//             | id op ASSIGN rvalue
//             ;

single_calc     : numeric_expr {
                    analyser.single_calculus($1);
                    $$ = $1;
                }
               ;

// rvalue      : expr { $$ = $1; }
//             ;

// arr_size    : OBRACKET REAL CBRACKET
//             ;

// mat_size    : OBRACKET REAL COMMA REAL CBRACKET
//             ;

// simple_id   : ID
//             | ID OBRACKET index CBRACKET
//             | ID OBRACKET index COMMA index CBRACKET
//             ;

// id          : simple_id
//             | ID OBRACKET COMMA index CBRACKET
//             ;

// index       : simple_id
//             | REAL
//             ;

// op          : COMPARISON
//             | AND
//             | OR
//             | NOT
//             | PLUS
//             | MINUS
//             | TIMES
//             | DIVIDE
//             | POWER
//             | MOD
//             ;

numeric_expr: NUMERIC                              { $$ = $1; }
            | numeric_expr COMPARISON numeric_expr { /* TODO: use $2.operation */ }
            | numeric_expr PLUS numeric_expr       { $$ = $1 + $3; }
            | numeric_expr MINUS numeric_expr      { $$ = $1 - $3; }
            | numeric_expr TIMES numeric_expr      { $$ = $1 * $3; }
            | numeric_expr DIVIDE numeric_expr     { $$ = $1 / $3; }
            | numeric_expr POWER numeric_expr      { $$ = Analyser::pow($1, $3); }
            | numeric_expr MOD numeric_expr        { $$ = $1 % $3; }
            | MINUS numeric_expr %prec U_MINUS     { $$ = -$2; }
            | OPAR numeric_expr CPAR               { $$ = $2; }
            ;
%%

void falk::Parser::error(const location &loc , const std::string &message) {
	std::cout << "Error: " << message << std::endl;// << "Location: " << loc << std::endl;
}
