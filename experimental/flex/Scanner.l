%{
	#include <iostream>
	#include <cstdlib>
	#include "Scanner.hpp"
	#include "Driver.hpp"
	#include "Parser.hpp"
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
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_TYPE(falk::Type::REAL, falk::location());
}

{complex_type} {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_TYPE(falk::Type::COMPLEX, falk::location());
}

{bool_type} {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_TYPE(falk::Type::BOOL, falk::location());
}

{var_decl} {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_VAR(falk::location());
}

{arr_decl} {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_ARRAY(falk::location());
}

{mat_decl} {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_MATRIX(falk::location());
}

{real} {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_REAL({yytext, falk::Type::REAL}, falk::location());
}

{complex} {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_COMPLEX({yytext, falk::Type::COMPLEX}, falk::location());
}

{bool_literal} {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_BOOL({yytext, falk::Type::BOOL}, falk::location());
}

{if_literal} {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_IF(falk::location());
}

{else_literal} {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_ELSE(falk::location());
}

{for_literal} {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_FOR(falk::location());
}

{while_literal} {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_WHILE(falk::location());
}

in {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_IN(falk::location());
}

return {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_RET(falk::location());
}

function {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_FUN(falk::location());
}

"typeof" {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_TYPEOF(falk::location());
}

{name} {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_ID(yytext, falk::location());
}

"+"  {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_ADD(falk::op::Arithmetical::ADD, falk::location());
 }

"-"  {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_SUB(falk::op::Arithmetical::SUB, falk::location());
 }

"*"  {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_MULT(falk::op::Arithmetical::MULT, falk::location());
 }

"/"  {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_DIV(falk::op::Arithmetical::DIV, falk::location());
 }

"**" {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_POW(falk::op::Arithmetical::POW, falk::location());
 }

"%"  {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_MOD(falk::op::Arithmetical::MOD, falk::location());
}

"==" {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_COMPARISON(falk::op::Comparison::EQ, falk::location());
}

"!=" {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_COMPARISON(falk::op::Comparison::NE, falk::location());
}

">"  {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_COMPARISON(falk::op::Comparison::GT, falk::location());
}

"<"  {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_COMPARISON(falk::op::Comparison::LT, falk::location());
}

">=" {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_COMPARISON(falk::op::Comparison::GE, falk::location());
}

"<=" {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_COMPARISON(falk::op::Comparison::LE, falk::location());
}

"&"  {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_AND(falk::op::Logical::AND, falk::location());
}

"|"  {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_OR(falk::op::Logical::OR, falk::location());
}

"!"  {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_NOT(falk::op::Logical::NOT, falk::location());
}

"("  {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_OPAR(falk::location());
}

")"  {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_CPAR(falk::location());
}

"["  {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_OINDEX(falk::location());
}

"]"  {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_CINDEX(falk::location());
}

":"  {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_OBLOCK(falk::location());
}

"."  {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_CBLOCK(falk::location());
}

"="  {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_ASSIGN(falk::location());
}

","  {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_COMMA(falk::location());
}

{end_of_command} {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO: pass real location of token, not an empty one
    return falk::Parser::make_EOC(falk::location());
}

{nonacceptable} {
    std::cout << "scanner scanning: " << yytext << std::endl;
    // TODO
    // lexical_error("unknown symbol %s\n", strdup(yytext));
}

%%
