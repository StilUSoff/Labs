#include <iostream>
#include <stdexcept>


class StackException {
    std::string message;

public: 
    StackException(std::string message): message{message}{};
    void Out() const {cout << message << endl;}
};

class StackOverflow: public StackException {
public:
    StackOverflow(std::string message): StackException(message) {}
};

class StackUnderflow: public StackException {
public:
    StackUnderflow(std::string message): StackException(message) {}
};

class StackOutOfRange: public StackException {
public:
    StackOutOfRange(std::string message): StackException(message) {}
};


template <typename T, size_t MaxSize>
class MyStack {

private:
    T stack[MaxSize];
    size_t size;
    
public:
    MyStack() : size(0) {};

    const T& operator[](size_t index) const;
    void Push(const T& value);
    T Pop();

    size_t GetSize() const;
    size_t Capacity() const;
};


template <typename T, size_t MaxSize>
void MyStack<T, MaxSize>::Push(const T& value) {
    if (size >= MaxSize) {
        throw StackOverflow("Stack overflow");
    }
    stack[size++] = value;
}

template <typename T, size_t MaxSize>
T MyStack<T, MaxSize>::Pop() {
    if (size == 0) {
        throw StackUnderflow("Stack underflow");
    }
    return stack[--size];
}

template <typename T, size_t MaxSize>
size_t MyStack<T, MaxSize>::GetSize() const {
    return size;
}

template <typename T, size_t MaxSize>
size_t MyStack<T, MaxSize>::Capacity() const {
    return MaxSize;
}

template <typename T, size_t MaxSize>
const T& MyStack<T, MaxSize>::operator[](size_t index) const {
    if (index >= size) {
        throw StackOutOfRange("Index " + std::to_string(index) + " is out of range");
    }
    return stack[index];
}