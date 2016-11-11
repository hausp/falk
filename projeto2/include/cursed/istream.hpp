
#ifndef CURSED_ISTREAMBUF_HPP
#define CURSED_ISTREAMBUF_HPP

#include <streambuf>
#include <iostream>

namespace cursed {
    class basic_terminal;

    class istreambuf : public std::streambuf {
     public:
        istreambuf(basic_terminal&);

        int_type underflow();
        int_type uflow();
        int_type pbackfail(int_type ch);
        std::streamsize showmanyc();
     private:
        cursed::basic_terminal& terminal;
        std::string line = "";
        size_t current = 0;
    };

    template<bool Override>
    class istream;

    template<>
    class istream<true> : public std::istream {
     public:
        istream(basic_terminal&, std::istream& = std::cin);
        ~istream();
     private:
        istreambuf buffer;
        std::istream& source;
        std::streambuf * const source_buffer;
    };

    template<>
    class istream<false> : public std::istream {
     public:
        istream(basic_terminal&);
     private:
        istreambuf buffer;
    };
}

#endif /* CURSED_ISTREAMBUF_HPP */
