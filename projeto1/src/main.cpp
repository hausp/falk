#include <iostream>
#include "ActionStacker.hpp"

extern int yyparse();
//extern int yydebug;
// extern std::unique_ptr<stx::Node> root;
extern ActionStacker actions;

int main(int argc, char **argv) {
    //yydebug = 1;              //remove comment to have verbose debug messages
    yyparse();                  //parses whole input
    actions.print();
    return 0;
}
