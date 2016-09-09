template<Type type>
void symbol_map::declare(const std::string& name) {
	variable<type> var;
	std::pair<Type, unsigned> pair{type, container<type>().size()};
	vars[name] = pair;
}

template<Type type>
void symbol_map::assign(const std::string& name, const todo<type>& value) {
	if (!vars.count(name)) {
		declare<type>(name);
	}

	auto& var = container<type>().at(name);
	if (var.already_defined) {
		var.value = value;
		var.already_defined = true;
	}
}

template<>
inline auto& symbol_map::container<Type::INT>() {
    return int_vars;
}
