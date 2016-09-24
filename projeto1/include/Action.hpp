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
    void add(const std::string&, const std::string&);
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
    Operation(Operator op, Action* first, Args&&... args)
     : op(op), t(dynamic_cast<TypedAction*>(first)->type()) {
        set_children(first, std::forward<Args>(args)...);
    }

    bool error() const override;
    Type type() const override;
    std::string to_string() const override;
    virtual std::string op_string() const;

 private:
    Operator op;
    Type t;
    bool fail = false;
    std::list<Action*> children;

    void set_children() {}

    template<typename... Args>
    void set_children(Action* action, Args&&... args) {
        auto typed = dynamic_cast<TypedAction*>(action);
        if (typed->type() != t) {
            // TODO: show an error (see v0.2 error reporting)
            fail = true;
        }
        fail = fail || typed->error();
        children.push_back(action);
        set_children(std::forward<Args>(args)...);
    }
};

class UnaryMinus : public Operation {
 public:
    UnaryMinus(Action* operand) : Operation(Operator::MINUS, operand) {}

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
    Action* rhs;
};

#endif /* ACTION_HPP */
