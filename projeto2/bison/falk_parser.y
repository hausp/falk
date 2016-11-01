%code requires {} // TODO

%{} // TODO

%code {} // TODO

%define parse.trace

/* yylval == %union
 * union informs the different ways we can store data
 */
%union {} // TODO

/* token defines our terminal symbols (tokens).
 */
%token <type> T_TYPE T_CAST
%token <value> T_INT T_FLOAT T_BOOL
%token <var> T_VAR
%token <operation> T_PLUS T_MINUS T_TIMES T_DIVIDE T_COMPARISON
%token <operation> T_AND T_OR T_NOT
%token T_IF T_THEN T_ELSE T_FOR
%token T_ASSIGN T_COMMA T_NL
%token T_OPAR T_CPAR T_OBLOCK T_CBLOCK
%token T_RET T_FUN T_REF T_ADDR

/* type defines the type of our nonterminal symbols.
 * Types should match the names used in the union.
 * Example: %type<node> expr
 */
%type <var> program lines line declaration

/* Operator precedence for mathematical operators
 * The latest it is listed, the highest the precedence
 * left, right, nonassoc
 */
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

/*
 * The language syntax grammar. Pushes actions into the action stacker
 * which are then popped when aggregate actions need them. When the program
 * finishes, the action stacker iterates over all stored actions and prints
 * them sequentially, granting that the output of the compiler is shown correctly.
 */

program     : setup commands finish
            | {} // TODO
            ;

setup       : {} // TODO
            ;

finish      : {} // TODO

commands    : command
            | commands command
            ;

command     : var_decl T_EOC
            | assignment T_EOC
            /* TODO: other commands */
            ;

var_decl    : T_VAR T_ID
            | T_VAR T_ID T_OBLOCK T_TYPE /* Aqui pode dar ruim */
            | T_VAR T_ID T_ASSIGN rvalue
            | T_ARRAY arr_size T_ID
            | T_ARRAY T_ID T_ASSIGN rvalue
            | T_MATRIX mat_size T_ID
            | T_MATRIX T_ID T_ASSIGN rvalue
            ;

assignment  : id T_ASSIGN rvalue
            | id op T_ASSIGN rvalue

rvalue      : expr
            ;

arr_size    : T_OINDEX T_REAL T_CINDEX
            ;

mat_size    : T_OINDEX T_REAL T_COMMA T_REAL T_CINDEX
            ;

simple_id   : T_ID
            | T_ID T_OINDEX index T_CINDEX
            | T_ID T_OINDEX index T_COMMA index T_CINDEX
            ;

id          : simple_id
            | T_ID T_OINDEX T_COMMA index T_CINDEX
            ;

index       : simple_id
            | T_REAL
            ;

expr        : real_expr
            | complex_expr
            ;

op          : T_COMPARISON
            | T_AND
            | T_OR
            | T_NOT
            | T_PLUS
            | T_MINUS
            | T_TIMES
            | T_DIVIDE
            | T_POWER
            | T_MOD
            ;

real_expr   : id
            | real_expr T_COMPARISON real_expr      {} // TODO
            | real_expr T_AND real_expr             {} // TODO
            | real_expr T_OR real_expr              {} // TODO
            | T_NOT real_expr                       {} // TODO
            | real_expr T_PLUS real_expr            {} // TODO
            | real_expr T_MINUS real_expr           {} // TODO
            | real_expr T_TIMES real_expr           {} // TODO
            | real_expr T_DIVIDE real_expr          {} // TODO
            | real_expr T_POWER real_expr           {} // TODO
            | real_expr T_MOD real_expr             {} // TODO
            | T_MINUS real_expr %prec U_MINUS       {} // TODO
            | T_OPAR real_expr T_CPAR               {} // TODO
            ;

complex_expr: id
            | complex_expr T_COMPARISON complex_expr      {} // TODO
            | complex_expr T_AND complex_expr             {} // TODO
            | complex_expr T_OR complex_expr              {} // TODO
            | T_NOT complex_expr                          {} // TODO
            | complex_expr T_PLUS complex_expr            {} // TODO
            | complex_expr T_MINUS complex_expr           {} // TODO
            | complex_expr T_TIMES complex_expr           {} // TODO
            | complex_expr T_DIVIDE complex_expr          {} // TODO
            | complex_expr T_POWER complex_expr           {} // TODO
            | complex_expr T_MOD complex_expr             {} // TODO
            | T_MINUS complex_expr %prec U_MINUS          {} // TODO
            | T_OPAR complex_expr T_CPAR                  {} // TODO
            ;

%%
