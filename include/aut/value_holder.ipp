
template<typename T, int64_t S>
template<typename... Targs>
aut::value_holder<T,S,true>::value_holder(Targs... elements):
 container{{std::move(elements)...}} { }

template<typename T, int64_t S>
bool aut::value_holder<T,S,true>::add(T u) {
    if (size < S) {
        container[size] = std::move(u);
        ++size;
        return true;
    }
    return false;
}

template<typename T, int64_t S>
bool aut::value_holder<T,S,true>::empty() const {
    return size == 0;
}

template<typename T, int64_t S>
T aut::value_holder<T,S,true>::last() const {
    return container.at(size - 1);
}

template<typename T, int64_t S>
aut::value_holder<T,S,false>::value_holder() { }

template<typename T, int64_t S>
template<typename... Targs>
aut::value_holder<T,S,false>::value_holder(Targs... elements):
 container{{std::move(elements)...}} { }

template<typename T, int64_t S>
bool aut::value_holder<T,S,false>::add(T u) {
    container.emplace_back(std::move(u));
    return true;
}

template<typename T, int64_t S>
bool aut::value_holder<T,S,false>::empty() const {
    return container.empty();
}

template<typename T, int64_t S>
T aut::value_holder<T,S,false>::last() const {
    return container.back();
}