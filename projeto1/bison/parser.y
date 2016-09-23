%code requires {
    #include "SymbolMap.hpp"
    #include "SyntaxTree.hpp"
    #include "macros.hpp"
}

%{
#include <cmath>
#include <iostream>
#include <unordered_map>

extern int yylex();
extern void yyerror(const char* s, ...);
%}

%code {
    SymbolMap symbols;
    std::unique_ptr<stx::Node> root;
    size_t line_number = 1;
}

%define parse.trace

/* yylval == %union
 * union informs the different ways we can store data
 */
%union {
    Type type;
    int value;
    char * var;
    stx::Node* node; // TODO: make this a lot worse to make it work NodePty->Node*
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
%type <node> program lines line declaration var_list var_def assignment expr variable typenode

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

program: lines { root.reset($1); }
    ;

lines: line       { $$ = new stx::Node(); if ($1) $$->set_children(stx::NodePtr($1)); }
    |  lines line { if ($2) $1->set_children(stx::NodePtr($2)); }
    ;

line: T_NL             { $$ = nullptr; } /* nullptr treated in lines */
    | declaration T_NL {
        $$ = new stx::Node();
        $$->set_children(stx::NodePtr($1), stx::NodePtr(stx::Node::make_literal("\n")));
        ++line_number; }
    | assignment T_NL  {
        $$ = new stx::Node();
        $$->set_children(stx::NodePtr($1), stx::NodePtr(stx::Node::make_literal("\n")));
        ++line_number; }
    ;

declaration: typenode var_list { $$ = $1; $$->set_children(stx::NodePtr($2)); }
    ;

typenode: T_TYPE { $$ = symbols.make_declaration($1); }
    ;

var_list: var_def { $$ = new stx::Node(); $$->set_children(stx::NodePtr($1)); }
    |    var_list T_COMMA var_def { $1->set_children(stx::NodePtr(stx::Node::make_literal(",")), stx::NodePtr($3)); }
    ;

var_def: T_VAR T_ASSIGN T_NUMBER { $$ = symbols.declare($1, $3, line_number); }
    |    T_VAR { $$ = symbols.declare($1, line_number); }
    ;

assignment: variable T_ASSIGN expr { $$ = stx::Node::make_assignment(stx::NodePtr($1), stx::NodePtr($3)); }
    ;

variable: T_VAR { $$ = symbols.retrieve($1, line_number); }
    ;

expr: T_NUMBER                   { $$ = stx::Node::make_literal($1); }
    | expr T_PLUS expr           { $$ = stx::Node::make_operator(stx::Operator::PLUS, stx::NodePtr($1), stx::NodePtr($3)); }
    | expr T_MINUS expr          { $$ = stx::Node::make_operator(stx::Operator::MINUS, stx::NodePtr($1), stx::NodePtr($3)); }
    | expr T_TIMES expr          { $$ = stx::Node::make_operator(stx::Operator::TIMES, stx::NodePtr($1), stx::NodePtr($3)); }
    | expr T_DIVIDE expr         { $$ = stx::Node::make_operator(stx::Operator::DIVIDE, stx::NodePtr($1), stx::NodePtr($3)); }
    | T_MINUS expr %prec U_MINUS { $$ = stx::Node::make_operator(stx::Operator::MINUS, stx::NodePtr($2)); }
    | T_OPAR expr T_CPAR         { $$ = stx::Node::make_operator(stx::Operator::PAR, stx::NodePtr($2)); }
    ;

/*
opt_init:
    T_ASSIGN T_NUMBER { $$ = stx::Node::make_literal($2); }
    | { $$ = nullptr; }
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

        stx::NodePtr node;
        if ($2) {
            auto var_node = stx::Node::make_literal($1);
            node = stx::Node::operator(stx::Operator::ASSIGN, var_node, $2);
        } else {
            node = stx::Node::make_literal($1);
        }
        auto parent = MagicEntity::top();
        parent.children.push_back(std::move(node));
    }
    ;
*/
%%

