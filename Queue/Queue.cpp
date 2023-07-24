#include "../Array/Array.cpp"
#include<stdexcept>
#include<iostream>

template<typename T>
class Queue: public Array<T>
{
private:
    int front_index;
    int back_index;
public:
    T& front();
    T& back();
    void push(T data);
    void pop();
    bool empty() override;
    int getsize() override;
    Queue();
    ~Queue();
};

template<typename T>
T& Queue<T>::front()
{
    if (this->empty())
    {
        throw std::out_of_range("Queue is empty");
    }
    return this->get(front_index);
}

template<typename T>
T& Queue<T>::back()
{
    if (this->empty())
    {
        throw std::out_of_range("Queue is empty");
    }
    return this->get(back_index - 1);
}

template<typename T>
void Queue<T>::push(T data)
{
    this->push_back(data);
    back_index++;
}

template<typename T>
void Queue<T>::pop()
{
    if (this->empty())
    {
        throw std::out_of_range("Queue is empty");
    }
    front_index++;
}

template<typename T>
bool Queue<T>::empty()
{
    return front_index == back_index;
}

template<typename T>
int Queue<T>::getsize()
{
    return back_index - front_index;
}

template<typename T>
Queue<T>::Queue()
{
    front_index = 0;
    back_index = 0;
}

template<typename T>
Queue<T>::~Queue()
{
}