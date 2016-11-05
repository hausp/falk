%{
	#include <iostream>
	#include <cstdlib>
	#include "Scanner.h"
	#include "Driver.hpp"
	#include "parser.hpp"
	#include "location.hh"

	#define yyterminate() falk::Parser::make_END(falk::location());

    // Updates location based in token length
	#define YY_USER_ACTION driver.increaseLocation(yyleng);
%}

/* Options */

/* uncommenting it gives a warning: -s option given but default rule
   can be matched */
/* %option nodefault */
%option noyywrap
/* enable c++ support */
%option c++
/* name of scanner class */
%option yyclass="Scanner"
/* prefix of FlexLexer */
%option prefix="Falk_"

/* Regex definitions */

var_decl var
arr_decl array
mat_decl matrix

real_type real
complex_type complex 
bool_type bool 

real [0-9]+|[0-9]*\.[0-9]+
complex {real}i
bool_literal true|false
name [a-zA-Z][a-zA-Z0-9_]*

if_literal if
else_literal else
for_literal for
while_literal while

end_of_command ;|\n

/* TODO */
nonacceptable ©

%%

[ \t] ;

{real_type} {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // return falk::parser::make_REAL(falk::location());
}

{complex_type} {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // return falk::parser::make_COMPLEX(falk::location());
}

{bool_type} {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // Type type(PrimitiveType::BOOL);
    // yylval.type = type;
    // return T_TYPE;
}

{var_decl} {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // return T_VAR;
}

{arr_decl} {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // return T_ARRAY;
}

{mat_decl} {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // return T_MATRIX;
}

{real} {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // Type type(PrimitiveType::REAL);
    // yylval.value = {strdup(yytext), type};
    // return T_REAL;
}

{complex} {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // Type type(PrimitiveType::COMPLEX);
    // yylval.value = {strdup(yytext), type};
    // return T_COMPLEX;
}

{bool_literal} {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // Type type(PrimitiveType::BOOL);
    // yylval.value = {strdup(yytext), type};
    // return T_BOOL;
}

{if_literal} {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // return T_IF;
}

{else_literal} {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // return T_ELSE;
}

{for_literal} {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // return T_FOR;
}

{while_literal} {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // return T_WHILE;
}

in {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // return T_IN;
}

return {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // return T_RET;
}

function {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // return T_FUN;
}

"typeof" {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // return T_TYPEOF;
}

{name} {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // yylval.var = strdup(yytext); return T_ID;
}

"+"  {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // yylval.arithmetical = falk::op::Arithmetical::ADD;
    // return T_PLUS;
 }

"-"  {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // yylval.arithmetical = falk::op::Arithmetical::SUB;
    // return T_MINUS;
 }

"*"  {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // yylval.arithmetical = falk::op::Arithmetical::MULT;
    // return T_TIMES;
 }

"/"  {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // yylval.arithmetical = falk::op::Arithmetical::DIV;
    // return T_DIVIDE;
 }

"**" {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // yylval.arithmetical = falk::op::Arithmetical::POW;
    // return T_POWER;
 }

"%"  {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // yylval.arithmetical = falk::op::Arithmetical::MOD;
    // return T_MOD;
}

"==" {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // yylval.comparison = falk::op::Comparison::EQ;
    // return T_COMPARISON;
}

"!=" {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // yylval.comparison = falk::op::Comparison::NE;
    // return T_COMPARISON;
}

">"  {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // yylval.comparison = falk::op::Comparison::GT;
    // return T_COMPARISON;
}

"<"  {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // yylval.comparison = falk::op::Comparison::LT;
    // return T_COMPARISON;
}

">=" {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // yylval.comparison = falk::op::Comparison::GE;
    // return T_COMPARISON;
}

"<=" {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // yylval.comparison = falk::op::Comparison::LE;
    // return T_COMPARISON;
}

"&"  {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // yylval.logical = falk::op::Logical::AND;
    // return T_AND;
}

"|"  {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // yylval.logical = falk::op::Logical::OR;
    // return T_OR;
}

"!"  {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // yylval.logical = falk::op::Logical::NOT;
    // return T_NOT;
}

"("  {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // return T_OPAR;
}

")"  {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // return T_CPAR;
}

"["  {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // return T_OINDEX;
}

"]"  {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // return T_CINDEX;
}

":"  {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // return T_OBLOCK;
}

"."  {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // return T_CBLOCK;
}

"="  {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // return T_ASSIGN;
}

","  {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // return T_COMMA;
}

{end_of_command} {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // return T_EOC;
}

{nonacceptable} {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // lexical_error("unknown symbol %s\n", strdup(yytext));
}

%%
