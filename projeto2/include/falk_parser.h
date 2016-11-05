/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_INCLUDE_FALK_PARSER_H_INCLUDED
# define YY_YY_INCLUDE_FALK_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "bison/falk_parser.y" /* yacc.c:1909  */

    #include "definitions.hpp"

#line 48 "include/falk_parser.h" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_TYPE = 258,
    T_REAL = 259,
    T_COMPLEX = 260,
    T_BOOL = 261,
    T_TYPEOF = 262,
    T_VAR = 263,
    T_ARRAY = 264,
    T_MATRIX = 265,
    T_ID = 266,
    T_PLUS = 267,
    T_MINUS = 268,
    T_TIMES = 269,
    T_DIVIDE = 270,
    T_POWER = 271,
    T_MOD = 272,
    T_COMPARISON = 273,
    T_AND = 274,
    T_OR = 275,
    T_NOT = 276,
    T_IF = 277,
    T_THEN = 278,
    T_ELSE = 279,
    T_FOR = 280,
    T_WHILE = 281,
    T_IN = 282,
    T_RET = 283,
    T_FUN = 284,
    T_ASSIGN = 285,
    T_COMMA = 286,
    T_EOC = 287,
    T_OPAR = 288,
    T_CPAR = 289,
    T_OBLOCK = 290,
    T_CBLOCK = 291,
    T_OINDEX = 292,
    T_CINDEX = 293,
    U_MINUS = 294
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 22 "bison/falk_parser.y" /* yacc.c:1909  */

    falk::complex complex;
    falk::real real;
    falk::op::Arithmetical arithmetical;
    falk::op::Comparison comparison;
    falk::op::Logical logical;
    // TODO

#line 109 "include/falk_parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_INCLUDE_FALK_PARSER_H_INCLUDED  */
