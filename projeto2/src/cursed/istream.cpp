
#include <ncurses.h>
#include "cursed/basic_terminal.hpp"
#include "cursed/istream.hpp"

cursed::istreambuf::istreambuf(basic_terminal& terminal):
 terminal{terminal} { }

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


cursed::istream<true>::istream(basic_terminal& terminal, std::istream& in):
 std::istream{&buffer},
 buffer{terminal},
 source{in},
 source_buffer{in.rdbuf()} {
    in.rdbuf(rdbuf());
}

cursed::istream<true>::~istream() {
    source.rdbuf(source_buffer);
}

cursed::istream<false>::istream(basic_terminal& terminal):
 std::istream{&buffer},
 buffer{terminal} { }
