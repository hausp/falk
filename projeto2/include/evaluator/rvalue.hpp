
#ifndef FALK_EVALUATOR_RVALUE
#define FALK_EVALUATOR_RVALUE

#include "ast/node.hpp"
#include "Evaluator.hpp"

namespace falk {
    class Evaluator::rvalue : public ast::tnode<Evaluator> {
        friend class Evaluator;
     public:
        rvalue(Type, const std::string&);
        void traverse(Evaluator&);
     private:
        std::string value;
    };

    inline Evaluator::rvalue::rvalue(Type type, const std::string& value):
     ast::tnode<Evaluator>{type}, value{value} { }

    void Evaluator::rvalue::traverse(Evaluator& ev) {
        ev.evaluate(*this);
    }
}

#endif /* FALK_EVALUATOR_RVALUE */
