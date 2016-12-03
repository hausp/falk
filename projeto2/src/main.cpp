
#include "aut/cursed/overterm.hpp"
#include "lpi/lpa_context.hpp"
#include "scanner.hpp"

#include "base/types.hpp"

int main(int argc, char** argv) {
    using terminal = cursed::overterm<true>;
    std::unique_ptr<terminal> term;
    if (argc <= 1 || argv[1] != std::to_string(0)) {
        term = std::make_unique<terminal>();
    }

    lpi::lpa_context<falk::scanner, falk::parser, falk::analyser> context;

    return context.run();
}
