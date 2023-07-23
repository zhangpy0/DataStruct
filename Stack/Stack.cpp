#include<iostream>
#include "Data.cpp"

using namespace std;

template<typename T>
class Stack
{
private:
    Data<T>* data;
    int size;
    int top;
public:
    Stack();
    ~Stack();
    bool empty();
    T top();
    void push(T data);
    void pop();
};

