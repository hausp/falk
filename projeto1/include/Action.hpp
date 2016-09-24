#ifndef ACTION_HPP
#define ACTION_HPP

#include <list>
#include <vector>
#include "SymbolMap.hpp"

namespace {
    SymbolMap symbols;
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


class Variable : public Action {
public:
    Variable(const std::string& name) : name(name) {}
    std::string to_string() const override {
        return name;
    }

private:
    std::string name;
};


class IntLiteral : public Action {
public:
    IntLiteral(const std::string& value) : value(value) {}
    std::string to_string() const override {
        return value;
    }

private:
    std::string value;
};


class Operation : public Action {
public:
    template<typename... Args>
    Operation(Operator op, Args&&... args) : op(op) {
        set_children(std::forward<Args>(args)...);
    }

    std::string to_string() const override;

private:
    Operator op;
    std::list<Action*> children;

    void set_children() {}

    template<typename... Args>
    void set_children(Action* action, Args&&... args) {
        children.push_back(action);
        set_children(std::forward<Args>(args)...);
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
