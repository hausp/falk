
#include <ncurses.h>
#include "cursed/istreambuf.hpp"
#include "cursed/terminal.hpp"

cursed::istreambuf::istreambuf(cursed::terminal& term):
 terminal{term} { }

cursed::istreambuf::int_type cursed::istreambuf::underflow() {
    if (current == line.size()) {
        line = terminal.get_line();
        current = 0;
    }

    return traits_type::to_int_type(line[current]);
}

cursed::istreambuf::int_type cursed::istreambuf::uflow() {
    auto ch = underflow();
    ++current;
    return ch;
}

cursed::istreambuf::int_type cursed::istreambuf::pbackfail(int_type ch) {
    if (current == 0 || (ch != traits_type::eof() && ch != line[current-1])) {
        return traits_type::eof();
    }
    return traits_type::to_int_type(line[--current]);
}

std::streamsize cursed::istreambuf::showmanyc() {
    return line.size() - current;
}
