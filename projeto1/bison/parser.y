%code requires {
    #include "Action.hpp"
    #include "ActionStacker.hpp"
    #include "macros.hpp"
    #include "utils.hpp"
}

%{
#include <cmath>
#include <iostream>
#include <unordered_map>

extern int yylex();
extern void yyerror(const char* s, ...);
%}

%code {
    ActionStacker actions;
}

%define parse.trace

/* yylval == %union
 * union informs the different ways we can store data
 */
%union {
    Type type;
    utils::literal value;
    Operator operation;
    char * var;
}

/* token defines our terminal symbols (tokens).
 */
%token <type> T_TYPE T_CAST
%token <value> T_NUMBER T_BOOL
%token <var> T_VAR
%token <operation> T_PLUS T_MINUS T_TIMES T_DIVIDE T_COMPARISON
%token <operation> T_AND T_OR T_NOT
%token T_IF T_THEN T_ELSE T_FOR
%token T_ASSIGN T_COMMA T_NL
%token T_OPAR T_CPAR T_OBLOCK T_CBLOCK

/* type defines the type of our nonterminal symbols.
 * Types should match the names used in the union.
 * Example: %type<node> expr
 */
%type <var> program lines line declaration var_list var_def assignment expr
%type <var> variable type literal pure_literal if_clause open_block close_block
%type <var> block new_line opt_nl opt_lines for_clause

/* Operator precedence for mathematical operators
 * The latest it is listed, the highest the precedence
 * left, right, nonassoc
 */
/* TODO: is %left the right choice for comparison operators? */
/* TODO: check if the precedence order is correct */
%nonassoc T_CAST
%left T_AND T_OR
%nonassoc T_NOT
%left T_COMPARISON
%left T_PLUS T_MINUS
%left T_TIMES T_DIVIDE
%nonassoc T_OPAR T_CPAR
%nonassoc U_MINUS

/* Starting rule 
 */
%start program

%%

program     : lines
            | { $$ = 0; }
            ;

lines       : line
            | lines line
            ;

line        : new_line { actions.push(new Nop()); }
            | declaration new_line
            | assignment new_line
            | if_clause new_line
            | for_clause new_line
            ;

if_clause   : T_IF expr opt_nl T_THEN open_block block {
                auto accepted = actions.pop();
                auto bool_expr = actions.pop();
                actions.push(new Conditional(bool_expr, accepted));
             }
            | T_IF expr opt_nl T_THEN open_block block T_ELSE open_block block {
                auto rejected = actions.pop();
                auto accepted = actions.pop();
                auto bool_expr = actions.pop();
                actions.push(new Conditional(bool_expr, accepted, rejected));
             }
            ;

for_clause  : T_FOR assignment T_COMMA expr T_COMMA assignment open_block block {
                auto code = actions.pop();
                auto update = actions.pop();
                auto test = actions.pop();
                auto init = actions.pop();
                actions.push(new Loop(init, test, update, code));
             }
            | T_FOR T_COMMA expr T_COMMA assignment open_block block {
                auto code = actions.pop();
                auto update = actions.pop();
                auto test = actions.pop();
                auto init = nullptr;
                actions.push(new Loop(init, test, update, code));
             }
            | T_FOR assignment T_COMMA expr T_COMMA open_block block {
                auto code = actions.pop();
                auto update = nullptr;
                auto test = actions.pop();
                auto init = actions.pop();
                actions.push(new Loop(init, test, update, code));
             }
            | T_FOR T_COMMA expr T_COMMA open_block block {
                auto code = actions.pop();
                auto update = nullptr;
                auto test = actions.pop();
                auto init = nullptr;
                actions.push(new Loop(init, test, update, code));
             }
            ;

open_block  : T_OBLOCK { Scope::open(); }
            ;

block       : new_line opt_lines close_block { $$ = 0; }
            ;

close_block : T_CBLOCK { Scope::close(); }
            ;

opt_lines   : lines
            | { $$ = 0; actions.push(new Nop()); }
            ;

new_line    : T_NL { ++utils::counter(); $$ = 0; }
            ;

opt_nl      : new_line
            | { $$ = 0; }
            ;

declaration : type var_list
            ;

type        : T_TYPE   { actions.push(new Declaration($1)); }
            ;

var_list    : var_def
            | var_list T_COMMA var_def
            ;

var_def     : T_VAR T_ASSIGN literal {
                auto name = std::string($1);
                auto value = actions.pop();
                dynamic_cast<Declaration*>(actions.top())->add(name, value);
             }
            | T_VAR {
                auto name = std::string($1);
                dynamic_cast<Declaration*>(actions.top())->add(name);
             }
            ;

assignment  : variable T_ASSIGN expr {
                auto expr = actions.pop();
                auto var = actions.pop();
                actions.push(new Assignment(var, expr));
             }
            ;

variable    : T_VAR { actions.push(new Variable($1)); }
            ;

pure_literal: T_NUMBER         { actions.push(new Constant($1.type, std::string($1.value))); }
            | T_BOOL           { actions.push(new Constant($1.type, std::string($1.value))); }

literal     : pure_literal
            | T_MINUS T_NUMBER { actions.push(new Constant($2.type, "-" + std::string($2.value))); }

expr        : pure_literal
            | variable
            | T_CAST expr                {
                auto body = actions.pop();
                actions.push(new Cast($1, body));
             }
            | expr T_COMPARISON expr     {
                auto right = actions.pop();
                auto left = actions.pop();
                actions.push(new Comparison($2, left, right));
             }
            | expr T_AND expr            {
                auto right = actions.pop();
                auto left = actions.pop();
                actions.push(new BoolOperation($2, left, right));
             }
            | expr T_OR expr             {
                auto right = actions.pop();
                auto left = actions.pop();
                actions.push(new BoolOperation($2, left, right));
             }
            | T_NOT expr                 {
                auto body = actions.pop();
                actions.push(new BoolOperation($1, body));
             }
            | expr T_PLUS expr           {
                auto right = actions.pop();
                auto left = actions.pop();
                actions.push(new Operation($2, left, right));
             }
            | expr T_MINUS expr          {
                auto right = actions.pop();
                auto left = actions.pop();
                actions.push(new Operation($2, left, right));
             }
            | expr T_TIMES expr          {
                auto right = actions.pop();
                auto left = actions.pop();
                actions.push(new Operation($2, left, right));
             }
            | expr T_DIVIDE expr         {
                auto right = actions.pop();
                auto left = actions.pop();
                actions.push(new Operation($2, left, right));
             }
            | T_MINUS expr %prec U_MINUS {
                auto body = actions.pop();
                actions.push(new UnaryMinus(body));
             }
            | T_OPAR expr T_CPAR         {
                auto body = actions.pop();
                actions.push(new Parenthesis(body));
             }
            ;

%%

