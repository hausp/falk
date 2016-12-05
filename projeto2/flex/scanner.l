%{
	#include <iostream>
	#include <cstdlib>

	#include "base/definitions.hpp"
    #include "location.hh"
    #include "parser.hpp"
    #include "scanner.hpp"

    #define YY_INTERACTIVE

	#define yyterminate() falk::parser::make_EOF(falk::location());

    // Updates location based in token length
	#define YY_USER_ACTION context.increase_location(yyleng);
%}

/* Options */

/* uncommenting it gives a warning: -s option given but default rule
   can be matched */
/* %option nodefault */
%option noyywrap
/* enable c++ support */
%option c++
/* name of scanner class */
%option yyclass="scanner"
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

end_of_command ;|\n

nonacceptable [^-\+\*\(\)/=%,;\.\n0-9A-Za-z_ \t><!&|:\[\]]+

%%

[ \t] ;

\/\/[^\n]*\n		        ;
\/\*([^\*]|\*[^/])*\*\/     ;

{real_type} {
    return falk::parser::make_TYPE(falk::type::REAL, falk::location());
}

{complex_type} {
    return falk::parser::make_TYPE(falk::type::COMPLEX, falk::location());
}

{bool_type} {
    return falk::parser::make_TYPE(falk::type::BOOL, falk::location());
}

{var_decl} {
    return falk::parser::make_VAR(falk::location());
}

{arr_decl} {
    return falk::parser::make_ARRAY(falk::location());
}

{mat_decl} {
    return falk::parser::make_MATRIX(falk::location());
}

{real} {
    auto rvalue = analyser.make_real(yytext);
    return falk::parser::make_REAL(std::move(rvalue), falk::location());
}

{complex} {
    auto rvalue = analyser.make_complex(yytext);
    return falk::parser::make_COMPLEX(std::move(rvalue), falk::location());
}

{bool_literal} {
    auto rvalue = analyser.make_boolean(yytext);
    return falk::parser::make_BOOL(std::move(rvalue), falk::location());
}

"if" {
    return falk::parser::make_IF(falk::location());
}

"else" {
    return falk::parser::make_ELSE(falk::location());
}

"for" {
    return falk::parser::make_FOR(falk::location());
}

"while" {
    return falk::parser::make_WHILE(falk::location());
}

"include" {
    return falk::parser::make_INCLUDE(falk::location());
}

"auto" {
    return falk::parser::make_AUTO(falk::location());
}

"undef" {
    return falk::parser::make_UNDEF(falk::location());
}

"in" {
    return falk::parser::make_IN(falk::location());
}

"return" {
    return falk::parser::make_RET(falk::location());
}

"function" {
    return falk::parser::make_FUN(falk::location());
}

"typeof" {
    return falk::parser::make_TYPEOF(falk::location());
}

{name} {
    return falk::parser::make_ID(yytext, falk::location());
}

"+"  {
    return falk::parser::make_PLUS(falk::op::arithmetic::ADD, falk::location());
}

"-"  {
    return falk::parser::make_MINUS(falk::op::arithmetic::SUB, falk::location());
}

"*"  {
    return falk::parser::make_TIMES(falk::op::arithmetic::MULT, falk::location());
}

"/"  {
    return falk::parser::make_DIVIDE(falk::op::arithmetic::DIV, falk::location());
}

"**" {
    return falk::parser::make_POWER(falk::op::arithmetic::POW, falk::location());
}

"%"  {
    return falk::parser::make_MOD(falk::op::arithmetic::MOD, falk::location());
}

"+="  {
    return falk::parser::make_ASSIGNOP(falk::op::assignment::ADD, falk::location());
}

"-="  {
    return falk::parser::make_ASSIGNOP(falk::op::assignment::SUB, falk::location());
}

"*="  {
    return falk::parser::make_ASSIGNOP(falk::op::assignment::MULT, falk::location());
}

"/="  {
    return falk::parser::make_ASSIGNOP(falk::op::assignment::DIV, falk::location());
}

"**=" {
    return falk::parser::make_ASSIGNOP(falk::op::assignment::POW, falk::location());
}

"%="  {
    return falk::parser::make_ASSIGNOP(falk::op::assignment::MOD, falk::location());
}

"&="  {
    return falk::parser::make_ASSIGNOP(falk::op::assignment::AND, falk::location());
}

"|="  {
    return falk::parser::make_ASSIGNOP(falk::op::assignment::OR, falk::location());
}

"==" {
    return falk::parser::make_COMPARISON(falk::op::comparison::EQ, falk::location());
}

"!="|"<>" {
    return falk::parser::make_COMPARISON(falk::op::comparison::NE, falk::location());
}

">"  {
    return falk::parser::make_COMPARISON(falk::op::comparison::GT, falk::location());
}

"<"  {
    return falk::parser::make_COMPARISON(falk::op::comparison::LT, falk::location());
}

">=" {
    return falk::parser::make_COMPARISON(falk::op::comparison::GE, falk::location());
}

"<=" {
    return falk::parser::make_COMPARISON(falk::op::comparison::LE, falk::location());
}

"&"  {
    return falk::parser::make_AND(falk::op::logic::AND, falk::location());
}

"|"  {
    return falk::parser::make_OR(falk::op::logic::OR, falk::location());
}

"!"  {
    return falk::parser::make_NOT(falk::op::logic::NOT, falk::location());
}

"("  {
    return falk::parser::make_OPAR(falk::location());
}

")"  {
    return falk::parser::make_CPAR(falk::location());
}

"["  {
    return falk::parser::make_OBRACKET(falk::location());
}

"]"  {
    return falk::parser::make_CBRACKET(falk::location());
}

":"  {
    return falk::parser::make_COLON(falk::location());
}

"."  {
    return falk::parser::make_DOT(falk::location());
}

"="  {
    return falk::parser::make_ASSIGN(falk::location());
}

","  {
    return falk::parser::make_COMMA(falk::location());
}

"\n" {
    return falk::parser::make_NL(falk::location());
}

";" {
    return falk::parser::make_SEMICOLON(falk::location());
}

\"[^\"]*\" {
    auto content = std::string(yytext);
    content = content.substr(1, content.size() - 2);
    return falk::parser::make_STRING(content, falk::location());
}

{nonacceptable} {
    std::string message = "unknown symbol ";
    message += yytext;
    message += "\n";
    lpi::lexical_error(context, message);
}

<<EOF>> {
    std::cout << "hello" << std::endl;
    return yyterminate();
}

%%
