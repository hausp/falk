
#ifndef CURSED_ISTREAMBUF_HPP
#define CURSED_ISTREAMBUF_HPP

#include <streambuf>

namespace cursed {
    class terminal;

    class istreambuf : public std::streambuf {
     public:
        istreambuf(terminal&);

        int_type underflow();
        int_type uflow();
        int_type pbackfail(int_type ch);
        std::streamsize showmanyc();
     private:
        cursed::terminal& term;
        std::string line = "";
        size_t current = 0;
    };
}

#endif /* CURSED_ISTREAMBUF_HPP */
