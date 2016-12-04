
#include <fstream>
#include "aut/cursed/overterm.hpp"
#include "base/types.hpp"
#include "lpi/lpa_context.hpp"
#include "scanner.hpp"

int main(int argc, char** argv) {
    using terminal = cursed::overterm<true>;
    std::unique_ptr<terminal> term;
    if (argc <= 1 || argv[1] != std::to_string(0)) {
        term = std::make_unique<terminal>();
    }

    lpi::lpa_context<falk::scanner, falk::parser, falk::analyser> context;

    std::ifstream stream;
    if (argc >= 3) {
        stream.open(argv[2], std::ifstream::in);
        context.console_mode(false);
        context.switch_input_stream(&stream);
    }

    return context.run();
}
