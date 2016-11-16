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
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_TYPE(falk::Type::REAL, falk::location());
}

{complex_type} {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_TYPE(falk::Type::COMPLEX, falk::location());
}

{bool_type} {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_TYPE(falk::Type::BOOL, falk::location());
}

{var_decl} {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_VAR(falk::location());
}

{arr_decl} {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_ARRAY(falk::location());
}

{mat_decl} {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_MATRIX(falk::location());
}

{real} {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    auto rvalue = analyser.make_real(yytext);
    return falk::parser::make_REAL(std::move(rvalue), falk::location());
}

{complex} {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    auto rvalue = analyser.make_complex(yytext);
    return falk::parser::make_COMPLEX(std::move(rvalue), falk::location());
}

{bool_literal} {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    auto rvalue = analyser.make_boolean(yytext);
    return falk::parser::make_BOOL(std::move(rvalue), falk::location());
}

{if_literal} {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_IF(falk::location());
}

{else_literal} {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_ELSE(falk::location());
}

{for_literal} {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_FOR(falk::location());
}

{while_literal} {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_WHILE(falk::location());
}

in {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_IN(falk::location());
}

return {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_RET(falk::location());
}

function {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_FUN(falk::location());
}

"typeof" {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_TYPEOF(falk::location());
}

{name} {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_ID(yytext, falk::location());
}

"+"  {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_PLUS(falk::op::Arithmetical::ADD, falk::location());
}

"-"  {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_MINUS(falk::op::Arithmetical::SUB, falk::location());
}

"*"  {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_TIMES(falk::op::Arithmetical::MULT, falk::location());
}

"/"  {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_DIVIDE(falk::op::Arithmetical::DIV, falk::location());
}

"**" {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_POWER(falk::op::Arithmetical::POW, falk::location());
}

"%"  {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_MOD(falk::op::Arithmetical::MOD, falk::location());
}

"+="  {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_ASSIGNOP(falk::op::Arithmetical::ADD, falk::location());
}

"-="  {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_ASSIGNOP(falk::op::Arithmetical::SUB, falk::location());
}

"*="  {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_ASSIGNOP(falk::op::Arithmetical::MULT, falk::location());
}

"/="  {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_ASSIGNOP(falk::op::Arithmetical::DIV, falk::location());
}

"**=" {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_ASSIGNOP(falk::op::Arithmetical::POW, falk::location());
}

"%="  {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_ASSIGNOP(falk::op::Arithmetical::MOD, falk::location());
}

"==" {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_COMPARISON(falk::op::Comparison::EQ, falk::location());
}

"!=" {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_COMPARISON(falk::op::Comparison::NE, falk::location());
}

">"  {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_COMPARISON(falk::op::Comparison::GT, falk::location());
}

"<"  {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_COMPARISON(falk::op::Comparison::LT, falk::location());
}

">=" {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_COMPARISON(falk::op::Comparison::GE, falk::location());
}

"<=" {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_COMPARISON(falk::op::Comparison::LE, falk::location());
}

"&"  {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_AND(falk::op::Logical::AND, falk::location());
}

"|"  {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_OR(falk::op::Logical::OR, falk::location());
}

"!"  {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_NOT(falk::op::Logical::NOT, falk::location());
}

"("  {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_OPAR(falk::location());
}

")"  {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_CPAR(falk::location());
}

"["  {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_OBRACKET(falk::location());
}

"]"  {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_CBRACKET(falk::location());
}

":"  {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_COLON(falk::location());
}

"."  {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_DOT(falk::location());
}

"="  {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_ASSIGN(falk::location());
}

","  {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_COMMA(falk::location());
}

"\n" {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_NL(falk::location());
}

";" {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::parser::make_SEMICOLON(falk::location());
}

<<EOF>> { return yyterminate(); }

{nonacceptable} {
    // std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO
    // lexical_error("unknown symbol %s\n", strdup(yytext));
}

%%