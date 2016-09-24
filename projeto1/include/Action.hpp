#ifndef ACTION_HPP
#define ACTION_HPP

#include <list>
#include <vector>
#include "SymbolMap.hpp"

namespace {
    auto& symbols = SymbolMap::instance();
}

class Action {
 public:
    virtual ~Action() {}
    virtual std::string to_string() const = 0;
};


class Declaration : public Action {
 public:
    Declaration(Type);
    void add(const std::string&);
    void add(const std::string&, Action*);
    std::string to_string() const override;

 private:
    Type type;
    std::vector<std::pair<std::string, std::string>> values;
};


class TypedAction : public Action {
 public:
    virtual bool error() const = 0;
    virtual Type type() const = 0;
};


class Variable : public TypedAction {
 public:
    Variable(const std::string&);
    bool error() const override;
    Type type() const override;
    std::string to_string() const override;

 private:
    bool fail;
    std::string name;
};


class Constant : public TypedAction {
 public:
    Constant(Type type, const std::string& value);
    bool error() const override;
    Type type() const override;
    std::string to_string() const override;

 private:
    Type t;
    std::string value;
};


class Operation : public TypedAction {
 public:
    template<typename... Args>
    Operation(Operator op, Action* first, Args&&... args) : op(op) {
        auto typed = dynamic_cast<TypedAction*>(first);
        t = typed->type();
        set_children(typed, std::forward<Args>(args)...);
    }

    template<typename... Args>
    Operation(Operator op, Type type, Args&&... args)
     : op(op), t(type) {
        set_children(std::forward<Args>(args)...);
    }

    bool error() const override;
    Type type() const override;
    std::string to_string() const override;
    virtual std::string op_string() const;
    void set_error();

 private:
    Operator op;
    Type t;
    bool fail = false;
    std::list<TypedAction*> children;

    void check(TypedAction* action) {
        auto expected = t;
        auto actual = action->type();
        if (actual != expected) {
            utils::semantic_error<Error::INCOMPATIBLE_OPERANDS>(op, expected, actual);
            fail = true;
        }
    }

    void set_children() {}

    template<typename... Args>
    void set_children(TypedAction* action, Args&&... args) {
        check(action);
        fail = fail || action->error();
        children.push_back(action);
        set_children(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void set_children(Action* action, Args&&... args) {
        set_children(dynamic_cast<TypedAction*>(action), std::forward<Args>(args)...);
    }
};


class BoolOperation : public Operation {
 public:
    template<typename... Args>
    BoolOperation(Operator op, Args&&... args)
     : Operation(op, Type::BOOL, std::forward<Args>(args)...) {}
};

class Parenthesis : public Operation {
 public:
    Parenthesis(Action* operand) : Operation(Operator::PAR, operand) {}

    std::string op_string() const override {
        return "";
    }
};

class UnaryMinus : public Operation {
 public:
    UnaryMinus(Action* operand) : Operation(Operator::UNARY_MINUS, operand) {}

    std::string op_string() const override {
        return "-u";
    }
};


class Assignment : public Action {
 public:
    Assignment(Variable*, Action*);
    std::string to_string() const override;

 private:
    Variable* var;
    TypedAction* rhs;
    bool fail;
};

#endif /* ACTION_HPP */
