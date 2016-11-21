
#ifndef FALK_EV_LVALUE_HPP
#define FALK_EV_LVALUE_HPP

#include "rvalue.hpp"

namespace falk {
    namespace ev {
        class lvalue {
         public:
            lvalue(const std::string&, rvalue = rvalue{});

            

            operator rvalue() const { return value; }
         private:
            rvalue value;
        };
    }
}

#endif /* FALK_EV_LVALUE_HPP */
