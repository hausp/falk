
template<typename T>
void Stacker<T>::push(const T& value) {
    stack.push(value);
}

template<typename T>
const T& Stacker<T>::top() {
    return stack.top();
}

template<typename T>
void Stacker<T>::clear() {
    decltype(stack)().swap(stack);
}
