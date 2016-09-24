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
    void popDelete();
    Action* pop();
    Action* top();
    void print() const;

    // auto begin() { return actions.begin(); }
    // auto begin() const { return actions.cbegin(); }
    // auto end() { return actions.end(); }
    // auto end() const { return actions.cend(); }

 private:
    std::list<Action*> actions;
    std::stack<Type> types;
};

#endif /* ACTION_STACKER_HPP */
