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

    namespace falk {
        class Scanner;
        class Driver;
    }
}

%code top {
    #include <iostream>
    #include "Scanner.h"
    #include "parser.hpp"
    #include "Driver.hpp"
    #include "location.hh"
    
    // yylex() arguments are defined in parser.y
    static falk::Parser::symbol_type yylex(falk::Scanner &scanner, falk::Driver &driver) {
        return scanner.get_next_token();
    }
}

%lex-param { falk::Scanner &scanner }
%lex-param { falk::Driver &driver }
%parse-param { falk::Scanner &scanner }
%parse-param { falk::Driver &driver }
%locations
%define parse.trace
%define parse.error verbose

%define api.token.prefix {TOKEN_}

%token END 0 "end of file"
%token <std::string> STRING  "string";
%token <uint64_t> NUMBER "number";
%token LEFTPAR "leftpar";
%token RIGHTPAR "rightpar";
%token SEMICOLON "semicolon";
%token COMMA "comma";

%start program

%%

program: {
        std::cout << "*** RUN ***" << std::endl;
        std::cout << std::endl << "prompt> ";
        
        driver.clear();
    }
    ;
%%

void falk::Parser::error(const location &loc , const std::string &message) {
	std::cout << "Error: " << message << std::endl << "Location: " << loc << std::endl;
}
