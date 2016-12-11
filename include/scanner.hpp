
#ifndef FALK_SCANNER_HPP
#define FALK_SCANNER_HPP

#if !defined(yyFlexLexerOnce)
#undef yyFlexLexer
#define yyFlexLexer Falk_FlexLexer
#include <FlexLexer.h>
#endif

#undef YY_DECL
#define YY_DECL falk::parser::symbol_type falk::scanner::next_token()

#include "base/definitions.hpp"
#include "lpi/context.hpp"
#include "parser.hpp"

namespace falk {
    class scanner : public yyFlexLexer {
     public:
        scanner(falk::analyser& analyser, lpi::context& context):
                analyser{analyser}, context{context} {}
    	virtual ~scanner() {}
    	virtual parser::symbol_type next_token();
    private:
        falk::analyser& analyser;
        lpi::context& context;
    };
}

#endif /* FALK_SCANNER_HPP */
