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
    int value;
    char * var;
}

/* token defines our terminal symbols (tokens).
 */
%token <type> T_TYPE
%token <var> T_VAR
%token <value> T_NUMBER
%token T_PLUS T_TIMES T_DIVIDE T_MINUS T_OPAR T_CPAR T_ASSIGN T_COMMA T_NL

/* type defines the type of our nonterminal symbols.
 * Types should match the names used in the union.
 * Example: %type<node> expr
 */
%type <value> program lines line declaration var_list var_def assignment expr variable typenode

/* Operator precedence for mathematical operators
 * The latest it is listed, the highest the precedence
 * left, right, nonassoc
 */
//%left T_ASSIGN
%left T_PLUS T_MINUS
%left T_TIMES T_DIVIDE
%nonassoc T_OPAR T_CPAR
%nonassoc U_MINUS

/* Starting rule 
 */
%start program

%%

program:
    lines { actions.print(); }
    ;

lines:
    line
    | lines line
    ;

line:
    T_NL { $$ = 0; ++utils::counter(); } // bison forced me to do this
    | declaration T_NL { ++utils::counter(); }
    | assignment T_NL { ++utils::counter(); }
    ;

declaration:
    typenode var_list
    ;

typenode:
    T_TYPE { actions.push(new Declaration($1)); }
    ;

var_list:
    var_def
    | var_list T_COMMA var_def
    ;

var_def:
    T_VAR T_ASSIGN T_NUMBER {
            auto name = std::string($1);
            auto value = std::to_string($3);
            dynamic_cast<Declaration*>(actions.top())->add(name, value);
        }
    | T_VAR {
            auto name = std::string($1);
            dynamic_cast<Declaration*>(actions.top())->add(std::string($1));
        }
    ;

assignment:
    variable T_ASSIGN expr {
        auto expr = actions.pop();
        auto var = actions.pop();
        actions.push(new Assignment(dynamic_cast<Variable*>(var), expr));
    }
    ;

variable:
    T_VAR { actions.push(new Variable($1)); }
    ;

expr:
    T_NUMBER                     { actions.push(new Constant(Type::INT, std::to_string($1))); }
    | variable
    | expr T_PLUS expr           {
            auto right = actions.pop();
            auto left = actions.pop();
            actions.push(new Operation(Operator::PLUS, left, right));
        }
    | expr T_MINUS expr          {
            auto right = actions.pop();
            auto left = actions.pop();
            actions.push(new Operation(Operator::MINUS, left, right));
        }
    | expr T_TIMES expr          {
            auto right = actions.pop();
            auto left = actions.pop();
            actions.push(new Operation(Operator::TIMES, left, right));
        }
    | expr T_DIVIDE expr         {
            auto right = actions.pop();
            auto left = actions.pop();
            actions.push(new Operation(Operator::DIVIDE, left, right));
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

