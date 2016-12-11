
#include <chrono>
#include <fstream>
#include <thread>
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

    if (argc >= 3) {
        context.console_mode(argv[2] != std::to_string(0));
    }

    std::ifstream stream;
    if (argc >= 4) {
        stream.open(argv[3], std::ifstream::in);
        context.console_mode(false);
        context.switch_input_stream(&stream);
    }

    auto ret = context.run();

    std::this_thread::sleep_for(std::chrono::seconds(10));

    return ret;
}
