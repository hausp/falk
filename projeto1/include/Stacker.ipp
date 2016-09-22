
template<typename T>
void Stacker<T>::push(const T& value) {
    stack.insert(value);
}

template<typename T>
const T& Stacker<T>::top() {
    return stack.top();
}

template<typename T>
void Stacker<T>::clear() {
    stack.clear();
}
