
#ifndef CURSED_OSTREAMBUF_HPP
#define CURSED_OSTREAMBUF_HPP

#include <streambuf>
#include <ncurses.h>
#include <iostream>

namespace cursed {
    class ostreambuf : public std::streambuf {
    public:
        int_type overflow(int_type c) override {
            addch(c);
            return c;
        }
    };

    template<bool Override>
    class ostream;

    template<>
    class ostream<true> : public std::ostream {
     public:
        ostream(std::ostream& out = std::cout):
         std::ostream{&buffer},
         source{out},
         source_buffer{out.rdbuf()} {
            out.rdbuf(rdbuf());
        }

        ~ostream() {
            source.rdbuf(source_buffer);
        }
     private:
        ostreambuf buffer;
        std::ostream& source;
        std::streambuf * const source_buffer;
    };

    template<>
    class ostream<false> : public std::ostream {
     public:
        ostream() : std::ostream{&buffer} { }
     private:
        ostreambuf buffer;
    };
}

#endif /* CURSED_OSTREAMBUF_HPP */
