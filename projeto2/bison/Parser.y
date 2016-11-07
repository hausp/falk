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

%token<std::string> ID "container identifier";
%token <falk::Type> TYPE "primitive type";
%token <falk::real> REAL "real value";
%token <falk::complex> COMPLEX "complex value";
%token <falk::boolean> BOOL "boolean value";

%token VAR    "var keyword";
%token ARRAY  "array keyword";
%token MATRIX "matrix keyword";
%token TYPEOF "typeof operator";
%token SEMICOLON "semicolon";
%token NL "new line";
%token IF THEN ELSE FOR WHILE IN RET FUN
%token ASSIGN COMMA
%token OPAR CPAR OBLOCK CBLOCK OINDEX CINDEX

%token EOF 0 "end of file"

%token <falk::op::Arithmetical> ADD SUB MULT DIV POW MOD
%token <falk::op::Comparison> COMPARISON
%token <falk::op::Logical> AND OR NOT


// %type<int> eoc opt_nl
%type<int> program line lines command commands new_line
// %type <int> assignment arr_size mat_size simple_id id index op
%type <falk::real> real_expr real_calc
%type <falk::complex> complex_expr complex_calc
// %type <falk::rvalue> rvalue expr

/* Operator precedence for mathematical operators
 * The latest it is listed, the highest the precedence
 * left, right, nonassoc
 */
%left T_AND T_OR
%nonassoc T_NOT
%left T_COMPARISON
%left T_ADD T_SUB
%left T_MULT T_DIV T_MOD
%left T_POW
%nonassoc U_SUB
%nonassoc T_OPAR T_CPAR

%start program

%%

program     :               { $$ = 0; }
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

command     :              { $$ = 0; }
            | real_calc    { $$ = 0; }
            | complex_calc { $$ = 0; }
            ;

// var_decl    : VAR ID
//             | VAR ID OBLOCK TYPE /* Aqui pode dar ruim */
//             | VAR ID ASSIGN rvalue
//             | ARRAY arr_size ID
//             | ARRAY ID ASSIGN rvalue
//             | MATRIX mat_size ID
//             | MATRIX ID ASSIGN rvalue
//             ;

// assignment  : id ASSIGN rvalue
//             | id op ASSIGN rvalue
//             ;

real_calc      : real_expr {
                    analyser.real_calculus($1);
                    $$ = $1;
                }
               ;

complex_calc   : complex_expr {
                    analyser.complex_calculus($1);
                    $$ = $1;
                }
               ;

// eoc         : NL               { $$ = 0; }
//             | SEMICOLON opt_nl { $$ = 0; }
//             ;

// opt_nl      :    { $$ = 0; }
//             | NL { $$ = 0; }

// rvalue      : real_expr { $$ = $1; }
//             ;

// arr_size    : OINDEX REAL CINDEX
//             ;

// mat_size    : OINDEX REAL COMMA REAL CINDEX
//             ;

// simple_id   : ID
//             | ID OINDEX index CINDEX
//             | ID OINDEX index COMMA index CINDEX
//             ;

// id          : simple_id
//             | ID OINDEX COMMA index CINDEX
//             ;

// index       : simple_id
//             | REAL
//             ;

// op          : COMPARISON
//             | AND
//             | OR
//             | NOT
//             | ADD
//             | SUB
//             | MULT
//             | DIV
//             | POW
//             | MOD
//             ;

real_expr   : REAL                           { $$ = $1; }
            | real_expr COMPARISON real_expr { /* TODO: use $2.operation */ }
            | real_expr ADD real_expr        { $$ = $1 + $3; }
            | real_expr SUB real_expr        { $$ = $1 - $3; }
            | real_expr MULT real_expr       { $$ = $1 * $3; }
            | real_expr DIV real_expr        { $$ = $1 / $3; }
            | real_expr POW real_expr        { /* $$ = falk::pow($1, $3); */ }
            | real_expr MOD real_expr        { /* $$ = $1 % $3; */ }
            | SUB real_expr %prec U_SUB      { $$ = -$2; }
            | OPAR real_expr CPAR            { $$ = $2; }
            ;

complex_expr: COMPLEX                              { $$ = $1; }
            | complex_expr COMPARISON complex_expr { /* TODO: use $2.operation */ }
            | complex_expr ADD complex_expr        { $$ = $1 + $3; }
            | complex_expr SUB complex_expr        { $$ = $1 - $3; }
            | complex_expr MULT complex_expr       { $$ = $1 * $3; }
            | complex_expr DIV complex_expr        { $$ = $1 / $3; }
            | complex_expr POW complex_expr        { /* $$ = falk::pow($1, $3); */ }
            | complex_expr MOD complex_expr        { /* $$ = $1 % $3; */ }
            | SUB complex_expr %prec U_SUB         { $$ = -$2; }
            | OPAR complex_expr CPAR               { $$ = $2; }
            ;
%%

void falk::Parser::error(const location &loc , const std::string &message) {
	std::cout << "Error: " << message << std::endl;// << "Location: " << loc << std::endl;
}
