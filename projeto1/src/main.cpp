#include <iostream>

extern int yyparse();
//extern int yydebug;
// extern std::unique_ptr<stx::Node> root;

int main(int argc, char **argv) {
    //yydebug = 1;              //remove comment to have verbose debug messages
    yyparse();                  //parses whole input
    // if (root) {
	   //  std::cout << *root << std::endl;
    // }
    return 0;
}
