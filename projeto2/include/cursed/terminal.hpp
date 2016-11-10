
#ifndef CURSED_TERMINAL_HPP
#define CURSED_TERMINAL_HPP

#include <list>
#include <string>
#include "basic_terminal.hpp"
#include "istream.hpp"
#include "ostream.hpp"

namespace cursed {
    template<bool Override>
    class terminal : public basic_terminal {
     public:
        terminal();
        ~terminal();

        std::ostream& ostream();

        std::string get_line() override;
     private:
        cursed::ostream<Override> output;
        cursed::istream<Override> input;
        std::list<std::string> buffer;
        std::string current_input;
        std::string unsaved_input;
        unsigned o_cursor_x = 0;
        unsigned cursor_x = 0;
        unsigned cursor_y = 0;
    };
}

#include "terminal.ipp"

#endif /* CURSED_TERMINAL_HPP */
