/* Copyright 2016 Marleson Graf <aszdrick@gmail.com>
   Ghabriel Nunes <ghabriel.nunes@gmail.com> 
   Vinicius Marino Calvo Torres de Freitas <vinimmbb@gmail.com> */

/*
 * Action classes definitions
 *      Actions are translation units that convert basic structures from
 *  the input language to its corresponding representation in the output
 *  language.
 *      The superclass Action derives into multiple definitions, each one 
 *  responsible for a different part of the code syntax.
 *      Actions trigger errors when they are missused, for instance undeclared
 *  variables or incompatible types being used in arithmetic operations.
 */

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

/*
 * No-Operation Action
 *      Nop is a non-operative action, which means it does nothing at all.
 *  It is used to keep the coherence of the action stack (read ActionStacker's 
 *  description) when some piece of code should be there, but isn't like an empty
 *  block.
 */
class Nop : public Action {
 public:
    std::string to_string(unsigned = 0) const override {
        return "";
    }
    Type type() const override { return PrimitiveType::VOID; }
};

/*
 * Declaration Action
 *      Declaration agregates different symbol declarations. This can be a 
 *  variable declaration (VarDecl) or an array declaration (ArrayDecl).
 */
class Declaration : public Action {
 public:
    Declaration(Type, const std::string& = "var");
    ~Declaration() {
        while (!declarations.empty()) {
            delete declarations.back();
            declarations.pop_back();
        }
    }
    void add(const std::string&);
    void add(const std::string&, Action*);
    void add(const std::string&, const utils::literal&);
    void set_symbol_type(const std::string& id) { symbol_type = id; }
    std::string to_string(unsigned = 0) const override;
    Type type() const override { return t; }

 private:
    Type t;
    std::string symbol_type;
    std::list<Action*> declarations;
};

class VarDecl : public Action {
 public:
    VarDecl(Type, const std::string&, Action* = nullptr);
    ~VarDecl() {
        delete value;
    }
    std::string to_string(unsigned = 0) const override;
    Type type() const override { return t; }

 private:
    Type t;
    std::string name;
    Action* value;
};

class ArrayDecl : public Action {
 public:
    ArrayDecl(Type, const std::string&, const std::string&);
    std::string to_string(unsigned = 0) const override;
    Type type() const override { return t; }

 private:
    Type t;
    std::string name;
    std::string size;
};

/*
 * Variable Action
 *      Represents the use of a variable.
 */
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

/*
 * Constant Action
 *      Represents the use of a constant value, such as "1" or "2".
 */
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

/*
 * Operation Action
 *      Operations is a superclass for all operation types.
 *  It represents operands as children of a node: 'n' children are supported. 
 */
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

    ~Operation() {
        while (!children.empty()) {
            delete children.back();
            children.pop_back();
        }
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
        set_type(PrimitiveType::BOOL);
    }
};

class BoolOperation : public Operation {
 public:
    template<typename... Args>
    BoolOperation(Operator op, Args&&... args)
     : Operation(op, PrimitiveType::BOOL, std::forward<Args>(args)...) {}
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

/*
 * Assignment Action
 *      Represents an assignment. Stores info about variables in a Symbol Map
 *  (read SymbolMap's description).
 */
class Assignment : public Action {
 public:
    Assignment(Action*, Action*);
    ~Assignment() {
        delete var;
        delete rhs;
    }
    std::string to_string(unsigned = 0) const override;
    Type type() const override;

 private:
    Action* var;
    Action* rhs;
    bool fail;
};

/*
 * Block Action
 *      Represents a group of lines of code.
 */
class Block : public Action {
 public:
    void add(Action*);
    ~Block() {
        while (!lines.empty()) {
            delete lines.back();
            lines.pop_back();
        }
    }
    std::string to_string(unsigned = 0) const override;
    Type type() const override { return PrimitiveType::VOID; }
 private:
    std::list<Action*> lines;
};

/*
 * Conditional Action
 *      Represents "if then else" constructions in the language.
 */
class Conditional : public Action {
 public:
    Conditional(Action*, Action*, Action* = nullptr);
    ~Conditional() {
        delete condition;
        delete accepted;
        delete rejected;
    }
    std::string to_string(unsigned = 0) const override;
    Type type() const override { return PrimitiveType::VOID; }
    bool error() const override { return fail; };
 private:
    Action* condition;
    Action* accepted;
    Action* rejected;
    bool fail;
};

/*
 * Loop Action
 *      Represents "for loop" constructions in the language.
 */
class Loop : public Action {
 public:
    Loop(Action*, Action*, Action*, Action*);
    ~Loop() {
        delete init;
        delete test;
        delete update;
        delete code;
    }
    std::string to_string(unsigned = 0) const override;
    Type type() const override { return PrimitiveType::VOID; }
    bool error() const override { return fail; }
 private:
    Action* init;
    Action* test;
    Action* update;
    Action* code;
    bool fail = false;
};

/*
 * Parameter List Action
 *      This action contains parameters for a function declaration
 *  or a function call.
 */
class ParamList : public Action {
 public:
    void add(Type, const std::string&);
    std::string to_string(unsigned = 0) const override;
    Type type() const override { return PrimitiveType::VOID; }

    auto begin() const { return vars.cbegin(); }
    auto begin() { return vars.begin(); }
    auto end() const { return vars.cend(); }
    auto end() { return vars.end(); }
 private:
    std::list<std::pair<Type, std::string>> vars;
};

/*
 * Function Action
 *      Represents a function declaration and/or definition.
 */
class Fun : public Action {
 public:
    Fun(Type, const std::string&);
    ~Fun() {
        delete params;
        delete body;
    }
    void inject(Action*);
    void bind(Action*, Action* = nullptr);
    std::string to_string(unsigned = 0) const override;
    Type type() const override { return ret; }
    bool error() const override { return fail; }
 private:
    std::string name;
    Action* params;
    Action* body;
    Type ret;
    bool fail = false;
};

/*
 * Expression List Action
 *      Represents a list of expressions used in function calls.
 */
class ExpressionList : public Action {
 public:
    ~ExpressionList() {
        while (!expressions.empty()) {
            delete expressions.back();
            expressions.pop_back();
        }
    }
    void add(Action*);
    size_t size() const { return expressions.size(); }
    std::string to_string(unsigned = 0) const override;
    Type type() const override { return PrimitiveType::VOID; }
    bool error() const override { return fail; }

    auto begin() const { return expressions.cbegin(); }
    auto begin() { return expressions.begin(); }
    auto end() const { return expressions.cend(); }
    auto end() { return expressions.end(); }

 private:
    std::list<Action*> expressions;
    bool fail;
};

/*
 * Function Call Action
 *      Represents a function call. Contains an expression list internally.
 */
class FunCall : public Action {
 public:
    FunCall(const std::string&, Action*);
    ~FunCall() {
        delete args;
    }
    std::string to_string(unsigned = 0) const override;
    Type type() const override { return t; }
    bool error() const override { return fail; }

 private:
    std::string name;
    ExpressionList* args;
    bool fail;
    Type t;
};

/*
 * Return Action
 *      Represents a ret statement, used in function bodies.
 */
class Return : public Action {
 public:
    Return(Action*);
    ~Return() {
        delete operand;
    }
    std::string to_string(unsigned = 0) const override;
    Type type() const override;
    bool error() const override { return fail; }

 private:
    Action* operand;
    bool fail;
};

/*
 * Array Index Action
 *      Represents the application of the index operator in an array.
 */
class ArrayIndex : public Action {
 public:
    ArrayIndex(const std::string&, Action*);
    ~ArrayIndex() {
        delete index;
    }
    std::string to_string(unsigned = 0) const override;
    Type type() const override { return t; }
    bool error() const override { return fail; }
 private:
    Type t;
    std::string name;
    Action* index;
    bool fail;
};

/*
 * Address Action
 *      Represents the application of the addr operator in an lvalue.
 */
class Address : public Action {
 public:
    Address(Action*);
    ~Address() {
        delete lvalue;
    }
    std::string to_string(unsigned = 0) const override;
    Type type() const override { return t; }
    bool error() const override { return fail; }
 private:
    Type t;
    Action* lvalue;
    bool fail;
};

/*
 * Reference Action
 *      Represents the application of the ref operator in an lvalue.
 */
class Reference : public Action {
 public:
    Reference(Action*);
    ~Reference() {
        delete lvalue;
    }
    std::string to_string(unsigned = 0) const override;
    Type type() const override { return t; }
    bool error() const override { return fail; }
 private:
    Type t;
    Action* lvalue;
    bool fail;
};

#endif /* ACTION_HPP */
