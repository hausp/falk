%code requires {
    #include "symbol_map.hpp"
    #include "SyntaxTree.hpp"
    #include "Stacker.hpp"
}

%{
#include <cmath>
#include <iostream>
#include <unordered_map>

extern int yylex();
extern void yyerror(const char* s, ...);
%}

%code {
    symbol_map symbols;
}

%define parse.trace

/* yylval == %union
 * union informs the different ways we can store data
 */
%union {
    Type type;
    int value;
    char * var;
    polska::NodePtr node; // TODO: make this a lot worse to make it work NodePty->Node*
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
%type <node> command assignment program lines line expr variable declaration opt_init var_decl

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

program: /*use ctrl+d to stop*/
    lines /*$$ = $1 when nothing is said*/
    ;

lines: 
    line /*$$ = $1 when nothing is said*/
    | lines line
    ;

line: 
    T_NL { $$ = 0; }
    | command T_NL
    ;

command:
    declaration
    | assignment
    ;

declaration:
    T_TYPE T_VAR opt_init opt_others {
        Types::push($1); // TODO: fix this
        $$ = polska::Node::declaration($1, $2, $3, symbols);
        MagicEntity::push($$); // opt_others must know $$
    }
    ;

variable:
    T_VAR { $$ = polska::Node::create_literal($1); } // TODO: check if the variable was declared
    ;

assignment:
    variable T_ASSIGN expr { $$ = polska::Node::create_operator(polska::Operator::ASSIGN, $1, $3); }
    ;

opt_init:
    T_ASSIGN T_NUMBER { $$ = polska::Node::create_literal($2); }
    | { $$ = nullptr; }
    ;

expr:
    T_NUMBER { $$ = polska::Node::create_literal($1); }
    | expr T_PLUS expr { $$ = polska::Node::create_operator(polska::Operator::PLUS, $1, $3); }
    | expr T_MINUS expr { $$ = polska::Node::create_operator(polska::Operator::MINUS, $1, $3); }
    | expr T_TIMES expr { $$ = polska::Node::create_operator(polska::Operator::TIMES, $1, $3); }
    | expr T_DIVIDE expr { $$ = polska::Node::create_operator(polska::Operator::DIVIDE, $1, $3); }
    | T_MINUS expr %prec U_MINUS { $$ = polska::Node::create_operator(polska::Operator::MINUS, $2); }
    | T_OPAR expr T_CPAR { $$ = polska::Node::create_operator(polska::Operator::PAR, $2); }
    ;


opt_others:
    T_COMMA var_decl
    | { MagicEntity::clear(); }
    ;

var_decl:
    T_VAR opt_init opt_others {
        auto type = Types::top();
        // $$->aux(type, $1, $2);
        if (!symbols.declare($1, type)) {
            utils::error<Error::MULTIPLE_DEFINITION>();
        }

        polska::NodePtr node;
        if ($2) {
            auto var_node = polska::Node::create_literal($1);
            node = polska::Node::create_operator(polska::Operator::ASSIGN, var_node, $2);
        } else {
            node = polska::Node::create_literal($1);
        }
        auto parent = MagicEntity::top();
        parent.children.push_back(std::move(node));
    }
    ;

%%

