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

%token<std::string> ID        "variable identifier";
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
%token<falk::op::arithmetic> ASSIGNOP  "assignment operator";
%token<falk::op::comparison> COMPARISON "comparison operator";;
%token<falk::op::logic> AND "&";
%token<falk::op::logic> OR  "|";
%token<falk::op::logic> NOT "!";

// Non-terminals
%type<falk::list> block block_body;
%type<falk::list> conditional loop;
%type<falk::value> command;
%type<falk::value> identifier arr_size mat_size;
%type<falk::value> flat_expr expr single_calc;
%type<falk::value> index rvalue;
%type<falk::value> assignment;
%type<falk::value> declaration;
%type<falk::array> array_list scalar_list
%type<falk::matrix> matrix_list matrix_list_body;

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
    | program new_line {
        analyser.prompt();
    }
    | entry eoc {
        analyser.prompt();
    }
    | program error eoc {
        yyerrok;
        analyser.prompt();
    }
    // | program function

init: %empty {
    analyser.initialize();
};

entry: program command {
    analyser.process($2);
};

eoc: SEMICOLON | new_line;

new_line: NL {
    context.count_new_line();
};

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
    | declaration { $$ = $1; }
    | assignment  { $$ = $1; }
    | conditional { $$ = $1; }
    | loop        { $$ = $1; }
    ;

declaration:
    VAR ID {
        // $$ = analyser.declare_variable($2);
    }
    | VAR ID COLON TYPE { /* Aqui pode dar ruim */
        // $$ = analyser.declare_variable($2, $4);
    }
    | VAR ID ASSIGN rvalue {
        // $$ = analyser.declare_variable($2, $4);
    }
    | ARRAY arr_size ID {
        // $$ = analyser.declare_array($3, $2);
    }
    | ARRAY ID ASSIGN rvalue {
        // $$ = analyser.declare_array($2, $4);
    }
    | MATRIX mat_size ID {
        // $$ = analyser.declare_matrix($3, $2);
    }
    | MATRIX ID ASSIGN rvalue {
        // $$ = analyser.declare_matrix($2, $4);
    };

assignment:
    identifier ASSIGN rvalue {
        // $$ = analyser.assign($1, $3);
    }
    | identifier ASSIGNOP rvalue {
        // $$ = analyser.assign($1, $3, $2);
    };

single_calc:
    expr {
        // $$ = falk::calculation();
        $$ = $1;
    };

conditional:
    IF OPAR expr CPAR block {
        $$ = falk::conditional();
        $$ += $3;
        $$ += $5;
        $$ += std::make_shared<falk::empty>();
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

identifier:
    ID {
        // $$ = analyser.retrieve_identifier($1);
    }
    | ID OBRACKET index CBRACKET {
        // auto index = analyser.make_array_index($3);
        // $$ = analyser.retrieve_identifier($1, index);
    }
    | ID OBRACKET index COMMA index CBRACKET {
        // auto index = analyser.make_matrix_index($3, $5);
        // $$ = analyser.retrieve_identifier($1, index);
    }
    | ID OBRACKET COMMA index CBRACKET {
        // auto index = analyser.make_matrix_index($4);
        // $$ = analyser.retrieve_identifier($1, index);
    };
    

index:
    identifier {
        // $$ = $1;
    }
    | REAL {
        // $$ = $1;
    };

array_list:
    OBRACKET scalar_list CBRACKET {
        $$ = $2;
    };

matrix_list:
    OBRACKET matrix_list_body CBRACKET {
        $$ = $2;
    };

scalar_list:
    flat_expr {
        $$ = analyser.extract($$, $1);
    }
    | scalar_list COMMA flat_expr {
        $$ = analyser.extract($1, $3);
    };

matrix_list_body:
    array_list {
        $$.push_back($1);
    }
    | matrix_list_body COMMA array_list {
        $$ = $1;
        $$.push_back($3);
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
    | identifier {
        $$ = falk::scalar(true); /* TODO */
    }
    | expr COMPARISON expr {
        $$ = falk::scalar(true); /* TODO: use $2.operation */
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
        $$ = falk::value::pow($1, $3);
    }
    | expr MOD expr {
        $$ = $1 % $3;
    }
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
    | array_list {
        $$ = $1;
    }
    | matrix_list {
        $$ = $1;        
    };
%%

void falk::parser::error(const location& loc, const std::string& message) {
	std::cout <<  "[Line " << context.line_count() << "] syntax error: " << message << std::endl;// << "Location: " << loc << std::endl;
}
