#ifndef ACTION_HPP
#define ACTION_HPP

#include <list>
#include <vector>
#include "SymbolMap.hpp"
#include "macros.hpp"

namespace {
    auto& symbols = SymbolMap::instance();
}

class Action {
 public:
    virtual ~Action() {}
    virtual std::string to_string(unsigned = 0) const = 0;
    virtual bool error() const { return false; }
    virtual Type type() const = 0;
};

class Nop : public Action {
 public:
    std::string to_string(unsigned = 0) const override {
        return "";
    }
    Type type() const override { return Type::VOID; }
};

class Declaration : public Action {
 public:
    Declaration(Type);
    void add(const std::string&);
    void add(const std::string&, Action*);
    std::string to_string(unsigned = 0) const override;
    Type type() const override;

 private:
    Type t;
    std::vector<std::pair<std::string, std::string>> values;
};


class Variable : public Action {
 public:
    Variable(const std::string&);
    bool error() const override;
    Type type() const override;
    std::string to_string(unsigned = 0) const override;

 private:
    bool fail;
    Type t;
    std::string name;
};


class Constant : public Action {
 public:
    Constant(Type type, const std::string& value);
    bool error() const override;
    Type type() const override;
    std::string to_string(unsigned = 0) const override;

 private:
    Type t;
    std::string value;
};


class Operation : public Action {
 public:
    template<typename... Args>
    Operation(Operator op, Action* first, Args&&... args) : op(op) {
        t = first->type();
        set_children(first, std::forward<Args>(args)...);
    }

    template<typename... Args>
    Operation(Operator op, Type type, Args&&... args)
     : op(op), t(type) {
        set_children(std::forward<Args>(args)...);
    }

    bool error() const override;
    Type type() const override;
    std::string to_string(unsigned = 0) const override;
    virtual std::string op_string() const;
    void set_type(Type);

 private:
    Operator op;
    Type t;
    bool fail = false;
    bool needs_coercion = false;
    std::list<Action*> children;

    void check(Action*);
    void set_children();

    template<typename... Args>
    void set_children(Action* action, Args&&... args) {
        fail = fail || action->error();
        if (!fail) {
            check(action);
        }
        children.push_back(action);
        set_children(std::forward<Args>(args)...);
    }
};


class Comparison : public Operation {
 public:
    template<typename... Args>
    Comparison(Operator op, Args&&... args)
     : Operation(op, std::forward<Args>(args)...) {
        set_type(Type::BOOL);
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

class Cast : public Operation {
 public:
    Cast(Type type, Action* operand) : Operation(Operator::CAST, operand) {
        set_type(type);
    }

    std::string op_string() const override {
        return "[" + utils::to_string(type()) + "]";
    }
};


class Assignment : public Action {
 public:
    Assignment(Action*, Action*);
    std::string to_string(unsigned = 0) const override;
    Type type() const override;

 private:
    Action* var;
    Action* rhs;
    bool fail;
};

class Conditional : public Action {
 public:
    Conditional(Action*, Action*, Action* = nullptr);
    std::string to_string(unsigned = 0) const override;
    Type type() const override { return Type::VOID; }
    bool error() const override { return fail; };
 private:
    Action* condition;
    Action* accepted;
    Action* rejected;
    bool fail;
};

class Loop : public Action {
 public:
    Loop(Action*, Action*, Action*, Action*);
    std::string to_string(unsigned = 0) const override;
    Type type() const override { return Type::VOID; }
    bool error() const override { return fail; }
 private:
    Action* init;
    Action* test;
    Action* update;
    Action* code;
    bool fail = false;
};

class ParamList : public Action {
 public:
    void add(Type, const std::string&);
    std::string to_string(unsigned = 0) const override;
    Type type() const override { return Type::VOID; }
 private:
    std::list<std::pair<Type, std::string>> vars;
};

// Function
class Fun : public Action {
 public:
    Fun(Type, const std::string&);
    void bind(Action*, Action* = nullptr);
    std::string to_string(unsigned = 0) const override;
    Type type() const override { return ret; }
    bool error() const override { return fail; }
 private:
    std::string name;
    Action* params;
    Action* body;
    Type ret;
    bool fail;
};


class ExpressionList : public Action {
 public:
    void add(Action*);
    size_t size() const { return expressions.size(); }
    std::string to_string(unsigned = 0) const override;
    Type type() const override { return Type::VOID; }
    bool error() const override { return fail; }

    auto begin() const { return expressions.cbegin(); }
    auto begin() { return expressions.begin(); }
    auto end() const { return expressions.cend(); }
    auto end() { return expressions.end(); }

 private:
    std::list<Action*> expressions;
    bool fail;
};


class FunCall : public Action {
 public:
    FunCall(const std::string&, Action*);
    std::string to_string(unsigned = 0) const override;
    Type type() const override;
    bool error() const override { return fail; }

 private:
    std::string name;
    ExpressionList* args;
    bool fail;
};


class Return : public Action {
 public:
    Return(Action*);
    std::string to_string(unsigned = 0) const override;
    Type type() const override;
    bool error() const override { return fail; }

 private:
    Action* operand;
    bool fail;
};


struct Scope {
    static void open();
    static void close();
};

inline void Scope::open() {
    symbols.open_scope();
}

inline void Scope::close() {
    symbols.close_scope();
}

#endif /* ACTION_HPP */
