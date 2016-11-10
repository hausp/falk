
#include <ncurses.h>

template<bool Override>
cursed::terminal<Override>::terminal(): input{*this} {
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

template<bool Override>
cursed::terminal<Override>::~terminal() {
    endwin();
}

template<bool Override>
std::ostream& cursed::terminal<Override>::ostream() {
    return output;
}

template<bool Override>
std::string cursed::terminal<Override>::get_line() {
    auto buffer_it = buffer.end();
    current_input = "";

    getyx(stdscr, cursor_y, cursor_x);
    o_cursor_x = cursor_x;

    int ch;
    while((ch = getch()) != '\n' && ch != '\r') {
        switch(ch) {
            case KEY_UP: {
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
                break;
            }
            case KEY_DOWN: {
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
                break;
            }
            case KEY_LEFT: {
                if (cursor_x > o_cursor_x) {
                    --cursor_x;
                    wmove(stdscr, cursor_y, cursor_x);
                }
                break;
            }
            case KEY_RIGHT: {
                if (cursor_x < current_input.size() + o_cursor_x) {
                    ++cursor_x;
                    wmove(stdscr, cursor_y, cursor_x);
                }
                break;
            }
            case KEY_BACKSPACE: {
                if (cursor_x > o_cursor_x) {
                    --cursor_x;
                    mvwdelch(stdscr, cursor_y, cursor_x);
                    current_input.erase(cursor_x - o_cursor_x, 1);
                } else {
                    wmove(stdscr, cursor_y, cursor_x);
                }
                break;
            }
            case KEY_DC: {
                if (cursor_x > o_cursor_x) {
                    wdelch(stdscr);
                    current_input.erase(cursor_x - o_cursor_x, 1);
                }
                break;
            }
            case KEY_HOME: {
                cursor_x = o_cursor_x;
                wmove(stdscr, cursor_y, cursor_x);
                break;
            }
            case KEY_END: {
                cursor_x = o_cursor_x + current_input.size();
                wmove(stdscr, cursor_y, cursor_x);
                break;
            }
            default: {
                if (isprint(ch)) {
                    current_input.insert(cursor_x - o_cursor_x, 1, ch);
                    mvwprintw(stdscr, cursor_y, o_cursor_x, current_input.c_str());
                    ++cursor_x;
                    wmove(stdscr, cursor_y, cursor_x);
                }
            }
        }
    }

    if (current_input.size() > 0) {
        buffer.push_back(current_input);
    }
    current_input.push_back(ch);
    mvprintw(cursor_y, o_cursor_x, current_input.c_str());
    return current_input;
}