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
    #include "definitions.hpp"

    namespace falk {
        class Scanner;
        class Driver;
    }
}

%code top {
    #include <iostream>
    #include "Scanner.hpp"
    #include "Parser.hpp"
    #include "Driver.hpp"
    #include "location.hh"
    
    static falk::Parser::symbol_type yylex(falk::Scanner &scanner) {
        return scanner.get_next_token();
    }
}

%lex-param { falk::Scanner &scanner }
/* %lex-param { falk::Driver &driver } */
%parse-param { falk::Scanner &scanner }
%parse-param { falk::Driver &driver }
%locations
%define parse.trace
%define parse.error verbose

%define api.token.prefix {TOKEN_}

// %token <std::string> STRING  "string";
// %token <uint64_t> NUMBER "number";
// %token LEFTPAR "leftpar";
// %token RIGHTPAR "rightpar";
// %token SEMICOLON "semicolon";
// %token COMMA "comma";

%token<std::string> ID        "container identifier";
%token <falk::Type> TYPE      "container type";
%token <falk::rvalue> REAL    "real value";
%token <falk::rvalue> COMPLEX "complex value";
%token <falk::rvalue> BOOL    "boolean value";

%token VAR    "var keyword";
%token ARRAY  "array keyword";
%token MATRIX "matrix keyword";
%token TYPEOF "typeof operator";
%token IF THEN ELSE FOR WHILE IN RET FUN
%token ASSIGN COMMA EOC
%token OPAR CPAR OBLOCK CBLOCK OINDEX CINDEX

%token END 0 "end of file"

%token <falk::op::Arithmetical> ADD SUB MULT DIV POW MOD
%token <falk::op::Comparison> COMPARISON
%token <falk::op::Logical> AND OR NOT

%type <int> program setup finish commands command var_decl
%type <int> assignment arr_size mat_size simple_id id index op
%type <falk::complex> rvalue expr
%type <falk::real> real_expr
%type <falk::complex> complex_expr


%start program

%%

program     : setup commands finish
            | {} // TODO
            ;

setup       : {} // TODO: open global scope
            ;

finish      : {} // TODO: close global scope

commands    : command
            | commands command
            ;

command     : var_decl EOC
            | assignment EOC
            | simple_calc EOC
            /* TODO: other commands */
            ;

var_decl    : VAR ID
            | VAR ID OBLOCK TYPE /* Aqui pode dar ruim */
            | VAR ID ASSIGN rvalue
            | ARRAY arr_size ID
            | ARRAY ID ASSIGN rvalue
            | MATRIX mat_size ID
            | MATRIX ID ASSIGN rvalue
            ;

assignment  : id ASSIGN rvalue
            | id op ASSIGN rvalue
            ;

simple_calc : expr { /* TODO: print the result */ }

rvalue      : expr { $$ = $1; }
            ;

arr_size    : OINDEX REAL CINDEX
            ;

mat_size    : OINDEX REAL COMMA REAL CINDEX
            ;

simple_id   : ID
            | ID OINDEX index CINDEX
            | ID OINDEX index COMMA index CINDEX
            ;

id          : simple_id
            | ID OINDEX COMMA index CINDEX
            ;

index       : simple_id
            | REAL
            ;

expr        : real_expr    { $$ = $1; }
            | complex_expr { $$ = $1; }
            ;

op          : COMPARISON
            | AND
            | OR
            | NOT
            | ADD
            | SUB
            | MULT
            | DIV
            | POW
            | MOD
            ;

real_expr   : id { $$ = $1; }
            | real_expr COMPARISON real_expr { /* TODO: use $2.operation */ }
            // | real_expr AND real_expr        { $$ = $1 && $3; }
            // | real_expr OR real_expr         { $$ = $1 || $3; }
            // | NOT real_expr                  { $$ = !$2; }
            | real_expr ADD real_expr       { $$ = $1 + $3; }
            | real_expr SUB real_expr      { $$ = $1 - $3; }
            | real_expr MULT real_expr      { $$ = $1 * $3; }
            | real_expr DIV real_expr     { $$ = $1 / $3; }
            | real_expr POW real_expr      { /* $$ = falk::pow($1, $3); */ }
            | real_expr MOD real_expr        { /* $$ = $1 % $3; */ }
            | SUB real_expr %prec U_SUB  { $$ = -$2; }
            | OPAR real_expr CPAR          { $$ = $2; }
            ;

complex_expr: id { $$ = $1; }
            | complex_expr COMPARISON complex_expr { /* TODO: use $2.operation */ }
            // | complex_expr AND complex_expr        { $$ = $1 && $3; }
            // | complex_expr OR complex_expr         { $$ = $1 || $3; }
            // | NOT complex_expr                     { $$ = !$2; }
            | complex_expr ADD complex_expr       { $$ = $1 + $3; }
            | complex_expr SUB complex_expr      { $$ = $1 - $3; }
            | complex_expr MULT complex_expr      { $$ = $1 * $3; }
            | complex_expr DIV complex_expr     { $$ = $1 / $3; }
            | complex_expr POW complex_expr      { /* $$ = falk::pow($1, $3); */ }
            // | complex_expr MOD complex_expr        { $$ = $1 % $3; }
            | SUB complex_expr %prec U_SUB     { $$ = -$2; }
            | OPAR complex_expr CPAR             { $$ = $2; }
            ;
%%

void falk::Parser::error(const location &loc , const std::string &message) {
	std::cout << "Error: " << message << std::endl << "Location: " << loc << std::endl;
}
