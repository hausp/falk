
#ifndef FALK_EV_FUNCTION_HPP
#define FALK_EV_FUNCTION_HPP

namespace falk {
    namespace ev {
        // some black magic to create callable user-defined functions
        class function {
         public:
            function(bool flag = false) : fail{flag} { }

            bool error() const {
                return fail;
            }
            // TODO
         private:
            bool fail;
            // TODO
        };
    }
}

#endif /* FALK_EV_FUNCTION_HPP */
