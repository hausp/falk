%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0"
%defines
%define parser_class_name { parser }

%define api.token.constructor
%define api.value.type variant
%define parse.assert
%define api.namespace { falk }

// this code goes to hpp
%code requires {
    #include <iostream>
    #include <string>
    #include <cstdint>
    #include "base/definitions.hpp"
    #include "lpi/context.hpp"

    namespace falk {
        class scanner;
    }
}

// this code goes to cpp
%code top {
    #include <iostream>
    #include "scanner.hpp"
    #include "parser.hpp"
    #include "location.hh"
    
    static falk::parser::symbol_type yylex(falk::scanner& scanner) {
        return scanner.next_token();
    }
}

%lex-param { falk::scanner &scanner }
%parse-param { falk::scanner &scanner }
%parse-param { falk::analyser &analyser }
%parse-param { lpi::context &context }
%locations
%define parse.trace
%define parse.error verbose

%define api.token.prefix {TOKEN_}

%token<std::string> ID      "variable identifier";
%token<falk::Type>  TYPE    "type identifier";
%token<falk::real>  REAL    "real value";
%token<falk::complex> COMPLEX "complex value";
%token<falk::boolean> BOOL    "boolean value";

%token VAR       "var keyword";
%token ARRAY     "array keyword";
%token MATRIX    "matrix keyword";
%token TYPEOF    "typeof operator";
%token SEMICOLON "semicolon";
%token NL        "new line";
%token IF        "if keyword";
%token THEN      "then keyword";
%token ELSE      "else keyword";
%token FOR       "for keyword";
%token WHILE     "while keyword";
%token IN        "in keyword";
%token RET       "return keyword";
%token FUN       "function keyword";
%token ASSIGN    "=";
%token COMMA     ";";
%token OPAR      "(";
%token CPAR      ")";
%token COLON     ":";
%token DOT       ".";
%token OBRACKET  "[";
%token CBRACKET  "]";
%token EOF 0     "end of file";

%token<falk::op::Arithmetical> PLUS     "+";
%token<falk::op::Arithmetical> MINUS    "-";
%token<falk::op::Arithmetical> TIMES    "*";
%token<falk::op::Arithmetical> DIVIDE   "/";
%token<falk::op::Arithmetical> POWER    "**";
%token<falk::op::Arithmetical> MOD      "%";
%token<falk::op::Arithmetical> ASSIGNOP; // TODO: description?

%token<falk::op::Comparison> COMPARISON; // TODO: description?

%token<falk::op::Logical> AND "&";
%token<falk::op::Logical> OR  "|";
%token<falk::op::Logical> NOT "!";

%type<falk::generic> program;
%type<falk::generic> command;
%type<falk::generic> new_line eoc;
%type<falk::generic> declaration;
%type<falk::generic> assignment;
%type<falk::value> identifier;
%type<falk::array_index> arr_size;
%type<falk::matrix_index> mat_size;
%type<falk::value> expr single_calc;
%type<falk::generic> index rvalue;
%type<falk::generic> init_list; // CHANGE THIS

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

program :
    %empty {
        $$ = analyser.create_program();
    }
    | program new_line {
        $$ = analyser.append($1, $2);
    }
    | program command eoc {
        $$ = analyser.append($1, $2);
        $$ = analyser.append($$, $3);
    };
    // | program function

eoc :
    SEMICOLON {
        $$ = analyser.semicolon();
    }
    | new_line {
        $$ = $1;
    };

new_line :
    NL { $$ = analyser.new_line(); };

command :
    SEMICOLON { $$ = analyser.empty_command(); }
    | single_calc { $$ = $1; }
    | declaration { $$ = $1; }
    | assignment { $$ = $1; };

declaration :
    VAR ID {
        $$ = analyser.declare_variable($2);
    }
    | VAR ID COLON TYPE { /* Aqui pode dar ruim */
        $$ = analyser.declare_variable($2, $4);
    }
    | VAR ID ASSIGN rvalue {
        $$ = analyser.declare_variable($2, $4);
    }
    | ARRAY arr_size ID {
        $$ = analyser.declare_array($3, $2);
    }
    | ARRAY ID ASSIGN rvalue {
        $$ = analyser.declare_array($2, $4);
    }
    | MATRIX mat_size ID {
        $$ = analyser.declare_matrix($3, $2);
    }
    | MATRIX ID ASSIGN rvalue { // TODO: init_list or something different?
        $$ = analyser.declare_matrix($2, $4);   
    };

init_list: %empty // TODO

assignment :
    identifier ASSIGN rvalue {
        $$ = analyser.assign($1, $3);
    }
    | identifier ASSIGNOP rvalue {
        /* TODO: find a way to allow this without conflicts */
        $$ = analyser.assign($1, $3, $2);
    };

single_calc :
    expr {
        $$ = analyser.single_calculation($1);
    };

rvalue :
    expr {
        $$ = $1;
    }
    | init_list // TODO
    ;

arr_size :
    OBRACKET REAL CBRACKET {
        $$ = analyser.make_array_index($2);
    };

mat_size :
    OBRACKET REAL COMMA REAL CBRACKET {
        $$ = analyser.make_matrix_index($2, $4);
    };

identifier :
    ID {
        $$ = analyser.retrieve_identifier($1);
    }
    | ID OBRACKET index CBRACKET {
        auto index = analyser.make_array_index($3);
        $$ = analyser.retrieve_identifier($1, index);
    }
    | ID OBRACKET index COMMA index CBRACKET {
        auto index = analyser.make_matrix_index($3, $5);
        $$ = analyser.retrieve_identifier($1, index);
    }
    | ID OBRACKET COMMA index CBRACKET {
        auto index = analyser.make_matrix_index($4);
        $$ = analyser.retrieve_identifier($1, index);
    };
    

index :
    identifier {
        $$ = $1;
    }
    | REAL {
        $$ = $1;
    };

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

expr :
    REAL {
        $$ = $1;
    }
    | COMPLEX {
        $$ = $1;
    }
    | BOOL {
        $$ = $1;
    }
    | identifier {
        $$ = falk::ev::TRUE; /* TODO */
    }
    | expr COMPARISON expr {
        $$ = falk::ev::TRUE; /* TODO: use $2.operation */
    }
    | expr PLUS expr {
        $$ = $1 + $3;
    }
    | expr MINUS expr {
        $$ = $1 - $3;
    }
    | expr TIMES expr {
        $$ = $1 * $3;
    }
    | expr DIVIDE expr {
        $$ = $1 / $3;
    }
    | expr POWER expr {
        $$ = analyser.pow($1, $3);
    }
    | expr MOD expr {
        $$ = $1 % $3;
    }
    | MINUS expr %prec U_MINUS {
        $$ = -$2;
    }
    | OPAR expr CPAR {
        $$ = $2;
    };
%%

void falk::parser::error(const location &loc , const std::string &message) {
	std::cout << "Error: " << message << std::endl;// << "Location: " << loc << std::endl;
}
