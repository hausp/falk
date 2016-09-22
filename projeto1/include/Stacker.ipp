
template<typename T>
void Stacker<T>::push(const T& value) {
    stack.insert(value);
}

template<typename T>
const T& Stacker<T>::top() const {
    return stack.top();
}
