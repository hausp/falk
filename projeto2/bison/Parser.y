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
%token <falk::value> REAL "real value";
%token <falk::value> COMPLEX "complex value";
%token <falk::value> BOOL "boolean value";

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
%token <falk::op::Arithmetical> ASSIGNOP
%token <falk::op::Comparison> COMPARISON
%token <falk::op::Logical> AND OR NOT


// %type<int> eoc opt_nl
%type <int> program command new_line eoc
%type <int> assignment arr_size mat_size simple_id id index
%type <falk::value> expr single_calc rvalue

/* Operator precedence for mathematical operators
 * The latest it is listed, the highest the precedence
 * left, right, nonassoc
 */
%left AND OR
%nonassoc NOT
%left COMPARISON
%left PLUS MINUS
%left TIMES DIVIDE MOD
%left POWER
%nonassoc U_MINUS
%nonassoc OPAR CPAR

%start program

%%

program     : %empty           { $$ = 0; }
            | program new_line { $$ = 0; }
            | program command eoc { $$ = 0; }
            // | program function
            ;

eoc         : SEMICOLON { $$ = 0; }
            | new_line  { $$ = 0; }
            ;

// lines       : line       { /* TODO: create lines with line */ }
//             | lines line { /* TODO: add line to lines */ }

// line        : new_line
//             | commands new_line

new_line    : NL { analyser.new_line(); }
            ;

// commands    : command
//             | commands SEMICOLON command
//             ;

command     : SEMICOLON    { $$ = 0; }
            | single_calc  { $$ = 0; }
            | var_decl     { /* TODO */ }
            | assignment   { /* TODO */ }
            ;

var_decl    : VAR ID
            | VAR ID COLON TYPE /* Aqui pode dar ruim */
            | VAR ID ASSIGN rvalue
            | ARRAY arr_size ID
            | ARRAY ID ASSIGN rvalue
            | MATRIX mat_size ID
            | MATRIX ID ASSIGN rvalue
            ;

assignment  : id ASSIGN rvalue
            | id ASSIGNOP rvalue /* TODO: find a way to allow this without conflicts */
            ;

single_calc : expr {
                analyser.single_calculus($1);
                $$ = $1;
             }
            ;

rvalue      : expr { $$ = $1; }
            ;

arr_size    : OBRACKET REAL CBRACKET { $$ = 0; /* TODO */ }
            ;

mat_size    : OBRACKET REAL COMMA REAL CBRACKET { $$ = 0; /* TODO */ }
            ;

simple_id   : ID { $$ = 0; /* TODO */ }
            | ID OBRACKET index CBRACKET { $$ = 0; /* TODO */ }
            | ID OBRACKET index COMMA index CBRACKET { $$ = 0; /* TODO */ }
            ;

id          : simple_id { $$ = 0; /* TODO */ }
            | ID OBRACKET COMMA index CBRACKET { $$ = 0; /* TODO */ }
            ;

index       : simple_id { $$ = 0; /* TODO */ }
            | REAL      { $$ = 0; /* TODO */ }
            ;

// op          : COMPARISON    { $$ = 0; /* TODO */ }
//             | AND           { $$ = 0; /* TODO */ }
//             | OR            { $$ = 0; /* TODO */ }
//             | NOT           { $$ = 0; /* TODO */ }
//             | PLUS          { $$ = 0; /* TODO */ }
//             | MINUS         { $$ = 0; /* TODO */ }
//             | TIMES         { $$ = 0; /* TODO */ }
//             | DIVIDE        { $$ = 0; /* TODO */ }
//             | POWER         { $$ = 0; /* TODO */ }
//             | MOD           { $$ = 0; /* TODO */ }
//             ;

expr        : REAL                      { $$ = $1; }
            | COMPLEX                   { $$ = $1; }
            | BOOL                      { $$ = $1; }
            | id                        { $$ = falk::ev::TRUE; /* TODO */ }
            | expr COMPARISON expr      { $$ = falk::ev::TRUE; /* TODO: use $2.operation */ }
            | expr PLUS expr            { $$ = $1 + $3; }
            | expr MINUS expr           { $$ = $1 - $3; }
            | expr TIMES expr           { $$ = $1 * $3; }
            | expr DIVIDE expr          { $$ = $1 / $3; }
            | expr POWER expr           { $$ = Analyser::pow($1, $3); }
            | expr MOD expr             { $$ = $1 % $3; }
            | MINUS expr %prec U_MINUS  { $$ = -$2; }
            | OPAR expr CPAR            { $$ = $2; }
            ;
%%

void falk::Parser::error(const location &loc , const std::string &message) {
	std::cout << "Error: " << message << std::endl;// << "Location: " << loc << std::endl;
}
