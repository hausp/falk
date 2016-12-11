
#ifndef CURSED_TERMINAL_HPP
#define CURSED_TERMINAL_HPP

#include <istream>
#include <list>
#include <ostream>
#include "istreambuf.hpp"
#include "ostreambuf.hpp"

namespace cursed {
    class terminal {
        using Buffer = std::list<std::string>;
     public:
        terminal();
        ~terminal();

        std::istream& istream();
        std::ostream& ostream();
        std::string get_line();
     private:
        istreambuf inbuffer;
        ostreambuf outbuffer;
        std::istream input;
        std::ostream output;
        Buffer buffer;
        Buffer::const_iterator buffer_it;        
        std::string current_input;
        std::string unsaved_input;
        unsigned o_cursor_x = 0;
        unsigned cursor_x = 0;
        unsigned cursor_y = 0;

        void delete_pressed();
        void up_pressed();
        void down_pressed();
        void left_pressed();
        void right_pressed();
        void backspace_pressed();
        void home_pressed();
        void end_pressed();
        void page_up_pressed();
        void page_down_pressed();
        void save_character(int);
    };
}

#endif /* CURSED_TERMINAL_HPP */
