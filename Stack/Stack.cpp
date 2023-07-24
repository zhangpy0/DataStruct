#include<iostream>
#include "../Array/Array.cpp"
#include<stdexcept>

using namespace std;

template<typename T>
class Stack: public Array<T>
{
public:
    T top();
    void push(T data);
    void pop();
    // bool empty();
    // int size();
    Stack();
    ~Stack();
};

template<typename T>
T Stack<T>::top()
{
    if (this->getsize() == 0)
    {
        throw out_of_range("Stack is empty");
    }
    return this->get(this->getsize()-1);
}

template<typename T>
void Stack<T>::push(T data)
{
    this->push_back(data);
}

template<typename T>
void Stack<T>::pop()
{
    this->pop_back();
}

// template<typename T>
// int Stack<T>::size()
// {
//     return this->size;
// }

template<typename T>
Stack<T>::Stack()
{
}

template<typename T>
Stack<T>::~Stack()
{
}
