%skeleton "lalr1.cc"
%require "3.0"
%defines

%define parser_class_name { parser }
%define api.token.constructor
%define api.value.type variant
%define parse.assert
%define api.namespace { falk }

// this code goes on hpp
%code requires {
    #include "base/definitions.hpp"
    #include "lpi/context.hpp"

    namespace falk { class scanner; }
}

// this code goes on cpp
%code top {
    #include "scanner.hpp"
    #include "parser.hpp"
    #include "location.hh"

    static falk::parser::symbol_type yylex(falk::scanner& scanner) {
        return scanner.next_token();
    }
}

%lex-param   { falk::scanner &scanner }
%parse-param { falk::scanner &scanner }
%parse-param { falk::analyser &analyser }
%parse-param { lpi::context &context }

%locations

%define parse.trace
%define parse.error verbose
%define api.token.prefix {TOKEN_}

// Tokens
%token VAR       "var keyword";
%token ARRAY     "array keyword";
%token MATRIX    "matrix keyword";
%token TYPEOF    "typeof operator";
%token SEMICOLON "semicolon";
%token NL        "new line";
%token IF        "if keyword";
%token THEN      "then keyword";
%token ELSE      "else keyword";
%token FOR       "for keyword";
%token WHILE     "while keyword";
%token IN        "in keyword";
%token RET       "return keyword";
%token FUN       "function keyword";
%token ASSIGN    "=";
%token COMMA     ",";
%token OPAR      "(";
%token CPAR      ")";
%token COLON     ":";
%token DOT       ".";
%token OBRACKET  "[";
%token CBRACKET  "]";
%token EOF 0     "end of file";

%token<std::string> ID   "variable identifier";
%token<falk::type> TYPE       "type identifier";
%token<falk::real> REAL       "real value";
%token<falk::complex> COMPLEX "complex value";
%token<falk::boolean> BOOL    "boolean value";

%token<falk::op::arithmetic> PLUS      "+";
%token<falk::op::arithmetic> MINUS     "-";
%token<falk::op::arithmetic> TIMES     "*";
%token<falk::op::arithmetic> DIVIDE    "/";
%token<falk::op::arithmetic> POWER     "**";
%token<falk::op::arithmetic> MOD       "%";
%token<falk::op::assignment> ASSIGNOP  "assignment operator";
%token<falk::op::comparison> COMPARISON "comparison operator";;
%token<falk::op::logic> AND "&";
%token<falk::op::logic> OR  "|";
%token<falk::op::logic> NOT "!";

// Non-terminals
%type<falk::list>  block block_body;
%type<falk::list>  conditional loop;
%type<falk::rvalue> command;
%type<falk::rvalue> arr_size mat_size;
%type<falk::rvalue> flat_expr expr single_calc;
%type<falk::rvalue> index rvalue;
%type<falk::lvalue> assignment;
%type<falk::lvalue> lvalue;
%type<falk::declaration> declaration;
%type<falk::list> container container_body
// %type<falk::list> array_list scalar_list
// %type<falk::list> matrix_list matrix_list_body;

// Operators precedence.
// The latest it is listed, the highest the precedence.
// Possible types: left, right, nonassoc
%left AND OR
%nonassoc NOT
%left COMPARISON
%left PLUS MINUS
%left TIMES DIVIDE MOD
%left POWER
%nonassoc U_MINUS
%nonassoc U_PLUS
%nonassoc OPAR CPAR

%start program

%%

program:
      init
    | program new_line  { analyser.prompt(); }
    | entry eoc         { analyser.prompt(); }
    | program error eoc { yyerrok; analyser.prompt(); };
    // | program function

init: %empty { analyser.initialize(); };

entry: program command { analyser.process($2); };

new_line: NL { context.count_new_line(); };

eoc: SEMICOLON | new_line;

block:
    COLON block_body DOT {
        $$ = $2;
    }
    | COLON command DOT {
        $$ = falk::block();
        $$ += $2;
    }
    | COLON DOT {
        $$ = falk::block();
    };

block_body:
    new_line {
        $$ = falk::block();
    }
    | command eoc {
        $$ = falk::block();
        $$ += $1;
    }
    | block_body new_line {
        $$ = $1;
    }
    | block_body command eoc {
        $$ = $1;
        $$ += $2;
    }
    | block_body error eoc {
        yyerrok;
    };

command:
    SEMICOLON     { $$ = {}; }
    | single_calc { $$ = $1; }
    | assignment  { $$ = $1.extract(); }
    | declaration { $$ = $1.extract(); }
    | conditional { $$ = $1.extract(); }
    | loop        { $$ = $1.extract(); }
    ;

declaration:
    VAR ID COLON TYPE {
        auto decl = falk::declare_variable{$2, structural::type::SCALAR, $4};
        $$ = falk::declaration(decl);
    }
    | VAR ID ASSIGN rvalue {
        auto decl = falk::declare_variable{$2, structural::type::SCALAR};
        $$ = falk::declaration(decl, $4);
    }
    | ARRAY arr_size ID {
        // TODO
        $$ = falk::declaration();
    }
    | ARRAY ID ASSIGN rvalue {
        auto decl = falk::declare_variable{$2, structural::type::ARRAY};
        $$ = falk::declaration(decl, $4);
    }
    | MATRIX mat_size ID {
        // TODO
        $$ = falk::declaration();
    }
    | MATRIX ID ASSIGN rvalue {
        auto decl = falk::declare_variable{$2, structural::type::MATRIX};
        $$ = falk::declaration(decl, $4);
    };

assignment:
    lvalue ASSIGN rvalue {
        $1 = $3;
        $$ = $1;
    }
    | lvalue ASSIGNOP rvalue {
        $$ = make_assignment($2, $1, $3);
    };

single_calc: expr { $$ = $1; };

conditional:
    IF OPAR expr CPAR block {
        $$ = falk::conditional();
        $$ += $3;
        $$ += $5;
        $$ += falk::rvalue();
    }
    | IF OPAR expr CPAR block ELSE block {
        $$ = falk::conditional();
        $$ += $3;
        $$ += $5;
        $$ += $7;
    };

loop:
    WHILE OPAR expr CPAR block {
        $$ = falk::loop();
        $$ += $3;
        $$ += $5;
    };

rvalue:
    expr {
        $$ = $1;
    };

arr_size:
    OBRACKET REAL CBRACKET {
        // $$ = analyser.make_array_index($2);
    };

mat_size:
    OBRACKET REAL COMMA REAL CBRACKET {
        // $$ = analyser.make_matrix_index($2, $4);
    };

lvalue:
    ID {
        $$ = falk::var_id{$1};
        $$.set_index(falk::rvalue(), falk::rvalue());
    }
    | ID OBRACKET index CBRACKET {
        $$ = falk::var_id{$1};
        $$.set_index($3, falk::rvalue());
    }
    | ID OBRACKET index COMMA index CBRACKET {
        $$ = falk::var_id{$1};
        $$.set_index($3, $5);
    }
    | ID OBRACKET COMMA index CBRACKET {
        $$ = falk::var_id{$1};
        $$.set_index(falk::rvalue(), $4);
    };
    

index:
    lvalue { $$ = $1; }
    | REAL { $$ = $1; };

container:
    OBRACKET container_body CBRACKET {
        $$ = $2;
    };

container_body:
    expr {
        $$ = falk::create_structure();
        $$ += $1;
    }
    | container_body COMMA expr {
        $$ = $1;
        $$ += $3;
    };

flat_expr:
    REAL {
        $$ = falk::scalar($1);
    }
    | COMPLEX {
        $$ = falk::scalar($1);
    }
    | BOOL {
        $$ = falk::scalar($1);
    }
    | lvalue {
        $$ = $1;
    }
    | expr COMPARISON expr {
        $$ = make_comparison($2, $1, $3);
    }
    | expr PLUS expr {
        $$ = $1 + $3;
    }
    | expr MINUS expr {
        $$ = $1 - $3;
    }
    | expr TIMES expr {
        $$ = $1 * $3;
    }
    | expr DIVIDE expr {
        $$ = $1 / $3;
    }
    | expr POWER expr {
        $$ = falk::rvalue::pow($1, $3);
    }
    | expr MOD expr {
        $$ = $1 % $3;
    }
    | expr AND expr {
        $$ = $1 && $3;
    }
    | expr OR expr {
        $$ = $1 || $3;
    }
    // | NOT expr {
    //     $$ = $1 % $3;
    // }
    | MINUS expr %prec U_MINUS {
        $$ = -$2;
    }
    | PLUS expr %prec U_PLUS {
        $$ = $2;
    }
    | OPAR expr CPAR {
        $$ = std::move($2);
    };

expr:
    flat_expr {
        $$ = $1;
    }
    | container {
        $$ = $1.extract();
    };
%%

void falk::parser::error(const location& loc, const std::string& message) {
    std::cout <<  "[Line " << context.line_count() << "] syntax error: " << message << std::endl;// << "Location: " << loc << std::endl;
}
