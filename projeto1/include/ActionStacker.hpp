#ifndef ACTION_STACKER_HPP
#define ACTION_STACKER_HPP

#include <list>
#include <stack>

class Action;
enum class Type;

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
