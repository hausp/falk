template<Type type>
void symbol_map::declare(const std::string& name) {
	variable<type> var;
	// vars[name] = {type, };
}

template<Type type>
void symbol_map::assign(const std::string& name, const todo<type>& value) {
	if (!vars.count(name)) {
		declare<type>(name);
	}

	auto& var = todo(name);
	if (var.already_defined) {
		var.value = value;
		var.already_defined = true;
	}
}

template<Type type>
variable<type>& symbol_map::todo(const std::string& name) {

}
