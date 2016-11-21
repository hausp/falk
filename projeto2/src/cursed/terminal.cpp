
#include <ncurses.h>
#include "cursed/istreambuf.hpp"
#include "cursed/ostreambuf.hpp"
#include "cursed/terminal.hpp"

cursed::terminal::terminal():
  inbuffer{*this},
  input{&inbuffer},
  output{&outbuffer} {
    // init ncurses
    initscr();
    // do not buffer && let ncurses handle interrupt and 
    // flow control characters 
    cbreak();
    // enable scrolling, i.e., isert new lines at end of terminal
    scrollok(stdscr, true);
    // enable treatment of special characters (e.g. KEY_LEFT)
    keypad(stdscr, true);
    // TODO
    mouseinterval(0);
    // enforces use of 8 bit char
    meta(stdscr, true);
    // set scrolling area (not sure about that)
    wsetscrreg(stdscr, 0, 100);
    // refresh screen like crazy
    immedok(stdscr, true);
    // disable echoing chars when getch is called
    noecho();
}

cursed::terminal::~terminal() {
    endwin();
}

std::ostream& cursed::terminal::ostream() {
    return output;
}

std::istream& cursed::terminal::istream() {
    return input;
}

std::string cursed::terminal::get_line() {
    buffer_it = buffer.end();
    current_input = "";

    getyx(stdscr, cursor_y, cursor_x);
    o_cursor_x = cursor_x;

    int ch;
    while((ch = getch()) != '\n' && ch != '\r') {
        switch(ch) {
            case KEY_UP:
                up_pressed();
                break;
            case KEY_DOWN:
                down_pressed();
                break;
            case KEY_LEFT:
                left_pressed();
                break;
            case KEY_RIGHT:
                right_pressed();
                break;
            case KEY_BACKSPACE:
                backspace_pressed();
                break;
            case KEY_DC:
                delete_pressed();
                break;
            case KEY_HOME:
                home_pressed();
                break;
            case KEY_END:
                end_pressed();
                break;
            // case KEY_PPAGE:
            //     page_up_pressed();
            //     break;
            // case KEY_NPAGE:
            //     page_down_pressed();
            //     break;
            default:
                save_character(ch);
        }
    }

    if (current_input.size() > 0) {
        buffer.push_back(current_input);
    }
    current_input.push_back(ch);
    mvprintw(cursor_y, o_cursor_x, current_input.c_str());
    return current_input;
}

void cursed::terminal::delete_pressed() {
    if (cursor_x > o_cursor_x) {
        wdelch(stdscr);
        current_input.erase(cursor_x - o_cursor_x, 1);
    }
}

void cursed::terminal::up_pressed() {
    if (buffer_it != buffer.begin()) {
        if (buffer_it == buffer.end()) {
            unsaved_input = current_input;
        }

        buffer_it = std::prev(buffer_it);
        current_input = *buffer_it;
        while (cursor_x > o_cursor_x) {
            --cursor_x;
            mvwdelch(stdscr, cursor_y, cursor_x);
        }
        mvwprintw(stdscr, cursor_y, o_cursor_x, current_input.c_str());
        cursor_x = o_cursor_x + current_input.size();
    }
}

void cursed::terminal::down_pressed() {
    if (buffer_it != buffer.end()) {
        current_input.clear();
        while (cursor_x > o_cursor_x) {
            --cursor_x;
            mvwdelch(stdscr, cursor_y, cursor_x);
        }

        buffer_it = std::next(buffer_it);

        if (buffer_it != buffer.end()) {
            current_input = *buffer_it;
        } else {
            current_input = unsaved_input;
        }

        wprintw(stdscr, current_input.c_str());
        cursor_x = o_cursor_x + current_input.size();
    }
}

void cursed::terminal::left_pressed() {
    if (cursor_x > o_cursor_x) {
        --cursor_x;
        wmove(stdscr, cursor_y, cursor_x);
    }    
}

void cursed::terminal::right_pressed() {
    if (cursor_x < current_input.size() + o_cursor_x) {
        ++cursor_x;
        wmove(stdscr, cursor_y, cursor_x);
    }
}

void cursed::terminal::backspace_pressed() {
    if (cursor_x > o_cursor_x) {
        --cursor_x;
        mvwdelch(stdscr, cursor_y, cursor_x);
        current_input.erase(cursor_x - o_cursor_x, 1);
    } else {
        wmove(stdscr, cursor_y, cursor_x);
    }
}

void cursed::terminal::home_pressed() {
    cursor_x = o_cursor_x;
    wmove(stdscr, cursor_y, cursor_x);
}

void cursed::terminal::end_pressed() {
    cursor_x = o_cursor_x + current_input.size();
    wmove(stdscr, cursor_y, cursor_x);
}

void cursed::terminal::page_up_pressed() {
    wscrl(stdscr, -1);
}

void cursed::terminal::page_down_pressed() {
    wscrl(stdscr, 1);
}

void cursed::terminal::save_character(int ch) {
    if (isprint(ch)) {
        current_input.insert(cursor_x - o_cursor_x, 1, ch);
        mvwprintw(stdscr, cursor_y, o_cursor_x, current_input.c_str());
        ++cursor_x;
        wmove(stdscr, cursor_y, cursor_x);
    }
}
