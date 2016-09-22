#include "symbol_map.hpp"

bool symbol_map::declare(const std::string& name, const Type& type) {
	if (vars.count(name)) {
        return false;
    }
    vars[name] = type;
    return true;
}
