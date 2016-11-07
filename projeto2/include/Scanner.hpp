
#ifndef FALK_SCANNER_HPP
#define FALK_SCANNER_HPP

#if !defined(yyFlexLexerOnce)
#undef yyFlexLexer
#define yyFlexLexer Falk_FlexLexer
#include <FlexLexer.h>
#endif

#undef YY_DECL
#define YY_DECL falk::Parser::symbol_type falk::Scanner::get_next_token()

#include "base/definitions.hpp"
#include "Parser.hpp"

namespace falk {
    class Driver;

    class Scanner : public yyFlexLexer {
     public:
        Scanner(Analyser& analyser, Driver& driver):
            analyser{analyser}, driver{driver} {}
    	virtual ~Scanner() {}
    	virtual Parser::symbol_type get_next_token();
    private:
        Analyser& analyser;
        Driver& driver;
    };
}

#endif /* FALK_SCANNER_HPP */
