
#include "aut/cursed/overterm.hpp"
#include "lpi/lpa_context.hpp"
#include "scanner.hpp"

#include "base/types.hpp"

int main(int, char **) {
    cursed::overterm<true> terminal;

    lpi::lpa_context<falk::scanner, falk::parser, falk::analyser> context;

    return context.run();
}
