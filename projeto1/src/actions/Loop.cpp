#include "Action.hpp"

Loop::Loop(Action* init, Action* test, Action* update, Action* code)
 : init(init), test(test), update(update), code(code) {

}