/* Copyright 2016 Marleson Graf <aszdrick@gmail.com>
   Ghabriel Nunes <ghabriel.nunes@gmail.com> 
   Vinicius Marino Calvo Torres de Freitas <vinimmbb@gmail.com> */

/*
 * Action Stacker Class Definition
 *      This is a stack of actions, basically a stack manager for the
 *  compiler. It's coherence must be kept by the grammar's (parser.y) 
 *  semantic actions.
 */

#ifndef ACTION_STACKER_HPP
#define ACTION_STACKER_HPP

#include <list>
#include <stack>

class Action;
struct Type;

class ActionStacker {
 public:
    ~ActionStacker();
    void push(Action*);
    void pop_delete();
    Action* pop();
    Action* top();
    void print() const;
    void open_scope();
    void close_scope();

 private:
    std::list<Action*> actions;
    std::stack<Type> types;
};

#endif /* ACTION_STACKER_HPP */
