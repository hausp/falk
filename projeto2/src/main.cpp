
#include <iostream>
#include "base/Driver.hpp"
#include "cursed/terminal.hpp"

int main(int, char **) {
    // Damned be all living beings?
    constexpr auto damn_it_all = true;
    cursed::terminal<damn_it_all> terminal;
    
    falk::Driver driver;
    
    return driver.parse();
}
