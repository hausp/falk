// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.
// //                    "%code top" blocks.
#line 25 "bison/parser.y" // lalr1.cc:397

    #include <iostream>
    #include "scanner.hpp"
    #include "parser.hpp"
    #include "location.hh"
    
    static falk::parser::symbol_type yylex(falk::scanner& scanner) {
        return scanner.next_token();
    }

#line 45 "src/parser.cpp" // lalr1.cc:397


// First part of user declarations.

#line 50 "src/parser.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "parser.hpp"

// User implementation prologue.

#line 64 "src/parser.cpp" // lalr1.cc:412


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 9 "bison/parser.y" // lalr1.cc:479
namespace  falk  {
#line 150 "src/parser.cpp" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
   parser ::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
   parser :: parser  (falk::scanner &scanner_yyarg, falk::analyser &analyser_yyarg, lpi::context &context_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      scanner (scanner_yyarg),
      analyser (analyser_yyarg),
      context (context_yyarg)
  {}

   parser ::~ parser  ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
   parser ::by_state::by_state ()
    : state (empty_state)
  {}

  inline
   parser ::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
   parser ::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
   parser ::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
   parser ::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
   parser ::symbol_number_type
   parser ::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
   parser ::stack_symbol_type::stack_symbol_type ()
  {}


  inline
   parser ::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 4: // "type identifier"
        value.move< falk::Type > (that.value);
        break;

      case 52: // arr_size
        value.move< falk::array_index > (that.value);
        break;

      case 5: // "real value"
      case 6: // "complex value"
      case 7: // "boolean value"
      case 43: // program
      case 44: // eoc
      case 45: // new_line
      case 46: // command
      case 47: // declaration
      case 48: // init_list
      case 49: // assignment
      case 50: // single_calc
      case 51: // rvalue
      case 55: // index
      case 56: // expr
        value.move< falk::generic > (that.value);
        break;

      case 54: // identifier
        value.move< falk::identifier > (that.value);
        break;

      case 53: // mat_size
        value.move< falk::matrix_index > (that.value);
        break;

      case 30: // "+"
      case 31: // "-"
      case 32: // "*"
      case 33: // "/"
      case 34: // "**"
      case 35: // "%"
      case 36: // ASSIGNOP
        value.move< falk::op::Arithmetical > (that.value);
        break;

      case 37: // COMPARISON
        value.move< falk::op::Comparison > (that.value);
        break;

      case 38: // "&"
      case 39: // "|"
      case 40: // "!"
        value.move< falk::op::Logical > (that.value);
        break;

      case 3: // "variable identifier"
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
   parser ::stack_symbol_type&
   parser ::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 4: // "type identifier"
        value.copy< falk::Type > (that.value);
        break;

      case 52: // arr_size
        value.copy< falk::array_index > (that.value);
        break;

      case 5: // "real value"
      case 6: // "complex value"
      case 7: // "boolean value"
      case 43: // program
      case 44: // eoc
      case 45: // new_line
      case 46: // command
      case 47: // declaration
      case 48: // init_list
      case 49: // assignment
      case 50: // single_calc
      case 51: // rvalue
      case 55: // index
      case 56: // expr
        value.copy< falk::generic > (that.value);
        break;

      case 54: // identifier
        value.copy< falk::identifier > (that.value);
        break;

      case 53: // mat_size
        value.copy< falk::matrix_index > (that.value);
        break;

      case 30: // "+"
      case 31: // "-"
      case 32: // "*"
      case 33: // "/"
      case 34: // "**"
      case 35: // "%"
      case 36: // ASSIGNOP
        value.copy< falk::op::Arithmetical > (that.value);
        break;

      case 37: // COMPARISON
        value.copy< falk::op::Comparison > (that.value);
        break;

      case 38: // "&"
      case 39: // "|"
      case 40: // "!"
        value.copy< falk::op::Logical > (that.value);
        break;

      case 3: // "variable identifier"
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
   parser ::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
   parser ::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
   parser ::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
   parser ::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
   parser ::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
   parser ::debug_stream () const
  {
    return *yycdebug_;
  }

  void
   parser ::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


   parser ::debug_level_type
   parser ::debug_level () const
  {
    return yydebug_;
  }

  void
   parser ::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline  parser ::state_type
   parser ::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
   parser ::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
   parser ::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
   parser ::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            symbol_type yylookahead (yylex (scanner));
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 4: // "type identifier"
        yylhs.value.build< falk::Type > ();
        break;

      case 52: // arr_size
        yylhs.value.build< falk::array_index > ();
        break;

      case 5: // "real value"
      case 6: // "complex value"
      case 7: // "boolean value"
      case 43: // program
      case 44: // eoc
      case 45: // new_line
      case 46: // command
      case 47: // declaration
      case 48: // init_list
      case 49: // assignment
      case 50: // single_calc
      case 51: // rvalue
      case 55: // index
      case 56: // expr
        yylhs.value.build< falk::generic > ();
        break;

      case 54: // identifier
        yylhs.value.build< falk::identifier > ();
        break;

      case 53: // mat_size
        yylhs.value.build< falk::matrix_index > ();
        break;

      case 30: // "+"
      case 31: // "-"
      case 32: // "*"
      case 33: // "/"
      case 34: // "**"
      case 35: // "%"
      case 36: // ASSIGNOP
        yylhs.value.build< falk::op::Arithmetical > ();
        break;

      case 37: // COMPARISON
        yylhs.value.build< falk::op::Comparison > ();
        break;

      case 38: // "&"
      case 39: // "|"
      case 40: // "!"
        yylhs.value.build< falk::op::Logical > ();
        break;

      case 3: // "variable identifier"
        yylhs.value.build< std::string > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 120 "bison/parser.y" // lalr1.cc:859
    {
        yylhs.value.as< falk::generic > () = analyser.create_program();
    }
#line 700 "src/parser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 123 "bison/parser.y" // lalr1.cc:859
    {
        yylhs.value.as< falk::generic > () = analyser.append(yystack_[1].value.as< falk::generic > (), yystack_[0].value.as< falk::generic > ());
    }
#line 708 "src/parser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 126 "bison/parser.y" // lalr1.cc:859
    {
        yylhs.value.as< falk::generic > () = analyser.append(yystack_[2].value.as< falk::generic > (), yystack_[1].value.as< falk::generic > ());
        yylhs.value.as< falk::generic > () = analyser.append(yylhs.value.as< falk::generic > (), yystack_[0].value.as< falk::generic > ());
    }
#line 717 "src/parser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 133 "bison/parser.y" // lalr1.cc:859
    {
        yylhs.value.as< falk::generic > () = analyser.semicolon();
    }
#line 725 "src/parser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 136 "bison/parser.y" // lalr1.cc:859
    {
        yylhs.value.as< falk::generic > () = yystack_[0].value.as< falk::generic > ();
    }
#line 733 "src/parser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 141 "bison/parser.y" // lalr1.cc:859
    { yylhs.value.as< falk::generic > () = analyser.new_line(); }
#line 739 "src/parser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 144 "bison/parser.y" // lalr1.cc:859
    { yylhs.value.as< falk::generic > () = analyser.empty_command(); }
#line 745 "src/parser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 145 "bison/parser.y" // lalr1.cc:859
    { yylhs.value.as< falk::generic > () = yystack_[0].value.as< falk::generic > (); }
#line 751 "src/parser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 146 "bison/parser.y" // lalr1.cc:859
    { yylhs.value.as< falk::generic > () = yystack_[0].value.as< falk::generic > (); }
#line 757 "src/parser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 147 "bison/parser.y" // lalr1.cc:859
    { yylhs.value.as< falk::generic > () = yystack_[0].value.as< falk::generic > (); }
#line 763 "src/parser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 150 "bison/parser.y" // lalr1.cc:859
    {
        yylhs.value.as< falk::generic > () = analyser.declare_variable(yystack_[0].value.as< std::string > ());
    }
#line 771 "src/parser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 153 "bison/parser.y" // lalr1.cc:859
    { /* Aqui pode dar ruim */
        yylhs.value.as< falk::generic > () = analyser.declare_variable(yystack_[2].value.as< std::string > (), yystack_[0].value.as< falk::Type > ());
    }
#line 779 "src/parser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 156 "bison/parser.y" // lalr1.cc:859
    {
        yylhs.value.as< falk::generic > () = analyser.declare_variable(yystack_[2].value.as< std::string > (), yystack_[0].value.as< falk::generic > ());
    }
#line 787 "src/parser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 159 "bison/parser.y" // lalr1.cc:859
    {
        yylhs.value.as< falk::generic > () = analyser.declare_array(yystack_[0].value.as< std::string > (), yystack_[1].value.as< falk::array_index > ());
    }
#line 795 "src/parser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 162 "bison/parser.y" // lalr1.cc:859
    {
        yylhs.value.as< falk::generic > () = analyser.declare_array(yystack_[2].value.as< std::string > (), yystack_[0].value.as< falk::generic > ());
    }
#line 803 "src/parser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 165 "bison/parser.y" // lalr1.cc:859
    {
        yylhs.value.as< falk::generic > () = analyser.declare_matrix(yystack_[0].value.as< std::string > (), yystack_[1].value.as< falk::matrix_index > ());
    }
#line 811 "src/parser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 168 "bison/parser.y" // lalr1.cc:859
    { // TODO: init_list or something different?
        yylhs.value.as< falk::generic > () = analyser.declare_matrix(yystack_[2].value.as< std::string > (), yystack_[0].value.as< falk::generic > ());   
    }
#line 819 "src/parser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 175 "bison/parser.y" // lalr1.cc:859
    {
        yylhs.value.as< falk::generic > () = analyser.assign(yystack_[2].value.as< falk::identifier > (), yystack_[0].value.as< falk::generic > ());
    }
#line 827 "src/parser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 178 "bison/parser.y" // lalr1.cc:859
    {
        /* TODO: find a way to allow this without conflicts */
        yylhs.value.as< falk::generic > () = analyser.assign(yystack_[2].value.as< falk::identifier > (), yystack_[0].value.as< falk::generic > (), yystack_[1].value.as< falk::op::Arithmetical > ());
    }
#line 836 "src/parser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 184 "bison/parser.y" // lalr1.cc:859
    {
        yylhs.value.as< falk::generic > () = analyser.single_calculation(yystack_[0].value.as< falk::generic > ());
    }
#line 844 "src/parser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 189 "bison/parser.y" // lalr1.cc:859
    {
        yylhs.value.as< falk::generic > () = yystack_[0].value.as< falk::generic > ();
    }
#line 852 "src/parser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 196 "bison/parser.y" // lalr1.cc:859
    {
        yylhs.value.as< falk::array_index > () = analyser.make_array_index(yystack_[1].value.as< falk::generic > ());
    }
#line 860 "src/parser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 201 "bison/parser.y" // lalr1.cc:859
    {
        yylhs.value.as< falk::matrix_index > () = analyser.make_matrix_index(yystack_[3].value.as< falk::generic > (), yystack_[1].value.as< falk::generic > ());
    }
#line 868 "src/parser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 206 "bison/parser.y" // lalr1.cc:859
    {
        yylhs.value.as< falk::identifier > () = analyser.retrieve_identifier(yystack_[0].value.as< std::string > ());
    }
#line 876 "src/parser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 209 "bison/parser.y" // lalr1.cc:859
    {
        auto index = analyser.make_array_index(yystack_[1].value.as< falk::generic > ());
        yylhs.value.as< falk::identifier > () = analyser.retrieve_identifier(yystack_[3].value.as< std::string > (), index);
    }
#line 885 "src/parser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 213 "bison/parser.y" // lalr1.cc:859
    {
        auto index = analyser.make_matrix_index(yystack_[3].value.as< falk::generic > (), yystack_[1].value.as< falk::generic > ());
        yylhs.value.as< falk::identifier > () = analyser.retrieve_identifier(yystack_[5].value.as< std::string > (), index);
    }
#line 894 "src/parser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 217 "bison/parser.y" // lalr1.cc:859
    {
        auto index = analyser.make_matrix_index(yystack_[1].value.as< falk::generic > ());
        yylhs.value.as< falk::identifier > () = analyser.retrieve_identifier(yystack_[4].value.as< std::string > (), index);
    }
#line 903 "src/parser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 224 "bison/parser.y" // lalr1.cc:859
    {
        yylhs.value.as< falk::generic > () = yystack_[0].value.as< falk::identifier > ();
    }
#line 911 "src/parser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 227 "bison/parser.y" // lalr1.cc:859
    {
        yylhs.value.as< falk::generic > () = yystack_[0].value.as< falk::generic > ();
    }
#line 919 "src/parser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 244 "bison/parser.y" // lalr1.cc:859
    {
        yylhs.value.as< falk::generic > () = yystack_[0].value.as< falk::generic > ();
    }
#line 927 "src/parser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 247 "bison/parser.y" // lalr1.cc:859
    {
        yylhs.value.as< falk::generic > () = yystack_[0].value.as< falk::generic > ();
    }
#line 935 "src/parser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 250 "bison/parser.y" // lalr1.cc:859
    {
        yylhs.value.as< falk::generic > () = yystack_[0].value.as< falk::generic > ();
    }
#line 943 "src/parser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 253 "bison/parser.y" // lalr1.cc:859
    {
        yylhs.value.as< falk::generic > () = falk::ev::TRUE; /* TODO */
    }
#line 951 "src/parser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 256 "bison/parser.y" // lalr1.cc:859
    {
        yylhs.value.as< falk::generic > () = falk::ev::TRUE; /* TODO: use $2.operation */
    }
#line 959 "src/parser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 259 "bison/parser.y" // lalr1.cc:859
    {
        yylhs.value.as< falk::generic > () = yystack_[2].value.as< falk::generic > () + yystack_[0].value.as< falk::generic > ();
    }
#line 967 "src/parser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 262 "bison/parser.y" // lalr1.cc:859
    {
        yylhs.value.as< falk::generic > () = yystack_[2].value.as< falk::generic > () - yystack_[0].value.as< falk::generic > ();
    }
#line 975 "src/parser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 265 "bison/parser.y" // lalr1.cc:859
    {
        yylhs.value.as< falk::generic > () = yystack_[2].value.as< falk::generic > () * yystack_[0].value.as< falk::generic > ();
    }
#line 983 "src/parser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 268 "bison/parser.y" // lalr1.cc:859
    {
        yylhs.value.as< falk::generic > () = yystack_[2].value.as< falk::generic > () / yystack_[0].value.as< falk::generic > ();
    }
#line 991 "src/parser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 271 "bison/parser.y" // lalr1.cc:859
    {
        yylhs.value.as< falk::generic > () = analyser.pow(yystack_[2].value.as< falk::generic > (), yystack_[0].value.as< falk::generic > ());
    }
#line 999 "src/parser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 274 "bison/parser.y" // lalr1.cc:859
    {
        yylhs.value.as< falk::generic > () = yystack_[2].value.as< falk::generic > () % yystack_[0].value.as< falk::generic > ();
    }
#line 1007 "src/parser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 277 "bison/parser.y" // lalr1.cc:859
    {
        yylhs.value.as< falk::generic > () = -yystack_[0].value.as< falk::generic > ();
    }
#line 1015 "src/parser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 280 "bison/parser.y" // lalr1.cc:859
    {
        yylhs.value.as< falk::generic > () = yystack_[1].value.as< falk::generic > ();
    }
#line 1023 "src/parser.cpp" // lalr1.cc:859
    break;


#line 1027 "src/parser.cpp" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
   parser ::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
   parser ::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char  parser ::yypact_ninf_ = -35;

  const signed char  parser ::yytable_ninf_ = -1;

  const signed char
   parser ::yypact_[] =
  {
     -35,    21,   -35,   -10,   -35,   -35,   -35,     2,     7,     8,
     -35,   -35,     1,     1,   -35,    38,   -35,   -35,   -35,   -19,
      39,    44,    53,    37,    18,    74,    56,    80,    84,   -35,
      23,   -35,   -35,   -35,   -35,     1,     1,     1,     1,     1,
       1,     1,     1,     1,   -35,    81,   -35,   -14,     1,    85,
       1,    59,   -35,     1,    67,   -35,   -35,   -35,   -35,    39,
     -35,    48,    48,    57,    57,   -35,    57,    31,    63,    81,
     -35,   -35,   -35,   -35,   -35,   -35,    88,   -35,    65,    66,
     -35,   -35
  };

  const unsigned char
   parser ::yydefact_[] =
  {
       2,     0,     1,    27,    33,    34,    35,     0,     0,     0,
       8,     7,     0,     0,     3,     0,    10,    11,     9,    36,
      22,     0,    12,     0,     0,     0,     0,     0,     0,    36,
       0,    44,     5,     4,     6,    19,    19,     0,     0,     0,
       0,     0,     0,     0,    32,     0,    31,     0,    19,     0,
      19,     0,    15,    19,     0,    17,    45,    24,    20,    23,
      21,    38,    39,    40,    41,    42,    43,    37,     0,     0,
      28,    14,    13,    16,    25,    18,     0,    30,     0,     0,
      29,    26
  };

  const signed char
   parser ::yypgoto_[] =
  {
     -35,   -35,   -35,    82,   -35,   -35,   -35,   -35,   -35,   -34,
     -35,   -35,    -1,   -23,     0
  };

  const signed char
   parser ::yydefgoto_[] =
  {
      -1,     1,    33,    14,    15,    16,    57,    17,    18,    58,
      25,    28,    29,    47,    59
  };

  const unsigned char
   parser ::yytable_[] =
  {
      19,    20,    60,    35,     3,    22,     4,     5,     6,    69,
      23,    26,    30,    31,    71,    70,    73,    36,    21,    75,
      46,     2,    68,    51,     3,    12,     4,     5,     6,     7,
       8,     9,    13,    10,    11,    24,    27,    61,    62,    63,
      64,    65,    66,    67,    46,    12,    78,     3,    56,    44,
      32,    11,    13,    37,    38,    39,    40,    41,    42,    50,
      43,    37,    38,    39,    40,    41,    42,    45,    46,    37,
      38,    39,    40,    41,    42,    48,    43,    52,    53,    49,
      39,    40,    41,    42,     3,    54,    44,    55,    74,    72,
      76,    41,    77,    79,    80,    81,     0,    34
  };

  const signed char
   parser ::yycheck_[] =
  {
       1,     1,    36,    22,     3,     3,     5,     6,     7,    23,
       3,     3,    12,    13,    48,    29,    50,    36,    28,    53,
      21,     0,    45,     5,     3,    24,     5,     6,     7,     8,
       9,    10,    31,    12,    13,    28,    28,    37,    38,    39,
      40,    41,    42,    43,    45,    24,    69,     3,    25,     5,
      12,    13,    31,    30,    31,    32,    33,    34,    35,    22,
      37,    30,    31,    32,    33,    34,    35,    23,    69,    30,
      31,    32,    33,    34,    35,    22,    37,     3,    22,    26,
      32,    33,    34,    35,     3,     5,     5,     3,    29,     4,
      23,    34,    29,     5,    29,    29,    -1,    15
  };

  const unsigned char
   parser ::yystos_[] =
  {
       0,    43,     0,     3,     5,     6,     7,     8,     9,    10,
      12,    13,    24,    31,    45,    46,    47,    49,    50,    54,
      56,    28,     3,     3,    28,    52,     3,    28,    53,    54,
      56,    56,    12,    44,    45,    22,    36,    30,    31,    32,
      33,    34,    35,    37,     5,    23,    54,    55,    22,    26,
      22,     5,     3,    22,     5,     3,    25,    48,    51,    56,
      51,    56,    56,    56,    56,    56,    56,    56,    55,    23,
      29,    51,     4,    51,    29,    51,    23,    29,    55,     5,
      29,    29
  };

  const unsigned char
   parser ::yyr1_[] =
  {
       0,    42,    43,    43,    43,    44,    44,    45,    46,    46,
      46,    46,    47,    47,    47,    47,    47,    47,    47,    48,
      49,    49,    50,    51,    51,    52,    53,    54,    54,    54,
      54,    55,    55,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    56
  };

  const unsigned char
   parser ::yyr2_[] =
  {
       0,     2,     0,     2,     3,     1,     1,     1,     1,     1,
       1,     1,     2,     4,     4,     3,     4,     3,     4,     0,
       3,     3,     1,     1,     1,     3,     5,     1,     4,     6,
       5,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     2,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const  parser ::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"variable identifier\"",
  "\"type identifier\"", "\"real value\"", "\"complex value\"",
  "\"boolean value\"", "\"var keyword\"", "\"array keyword\"",
  "\"matrix keyword\"", "\"typeof operator\"", "\"semicolon\"",
  "\"new line\"", "\"if keyword\"", "\"then keyword\"", "\"else keyword\"",
  "\"for keyword\"", "\"while keyword\"", "\"in keyword\"",
  "\"return keyword\"", "\"function keyword\"", "\"=\"", "\";\"", "\"(\"",
  "\")\"", "\":\"", "\".\"", "\"[\"", "\"]\"", "\"+\"", "\"-\"", "\"*\"",
  "\"/\"", "\"**\"", "\"%\"", "ASSIGNOP", "COMPARISON", "\"&\"", "\"|\"",
  "\"!\"", "U_MINUS", "$accept", "program", "eoc", "new_line", "command",
  "declaration", "init_list", "assignment", "single_calc", "rvalue",
  "arr_size", "mat_size", "identifier", "index", "expr", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
   parser ::yyrline_[] =
  {
       0,   120,   120,   123,   126,   133,   136,   141,   144,   145,
     146,   147,   150,   153,   156,   159,   162,   165,   168,   172,
     175,   178,   184,   189,   192,   196,   201,   206,   209,   213,
     217,   224,   227,   244,   247,   250,   253,   256,   259,   262,
     265,   268,   271,   274,   277,   280
  };

  // Print the state stack on the debug stream.
  void
   parser ::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
   parser ::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 9 "bison/parser.y" // lalr1.cc:1167
} //  falk 
#line 1456 "src/parser.cpp" // lalr1.cc:1167
#line 283 "bison/parser.y" // lalr1.cc:1168


void falk::parser::error(const location &loc , const std::string &message) {
	std::cout << "Error: " << message << std::endl;// << "Location: " << loc << std::endl;
}
