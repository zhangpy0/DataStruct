#include<iostream>
#include<string.h>
#include "../Data/Data.cpp"
#include<stdexcept>

template<typename T>
class Array
{
private:
    Data<T>* data;
    int size;
    int capacity;

    void addCapacity();
    void reduceCapacity();
public:
    Data<T>* iterator;

    Array();
    Array(int capacity);
    Array(Array<T>& datas);

    ~Array();
    void push_back(T data);
    void pop_back();
    void insert(int index, T data);
    void insert(int index, Array<T> data);
    
    void erase(int index);
    void erase(int start, int end);

    virtual int getsize();
    int getcapacity();
    T& get(int index);
    void set(int index, T data);
    virtual bool empty();
    void clear();
    void resize(int capacity);

    T& operator[](int index);
    Array<T>& operator=(Array<T>& data);
    bool operator==(Array<T>& data);
    bool operator!=(Array<T>& data);

    Data<T>* begin();
    Data<T>* end();
};

template<typename T>
void Array<T>::addCapacity()
{
    if (this->size == this->capacity)
    {
        if (this->capacity < 64)
        {
            this->capacity += 8;
        }
        else
        {
            this->capacity *= 2;
        }
        this->resize(this->capacity);
    }
}

template<typename T>
void Array<T>::reduceCapacity()
{
    if (this->size < this->capacity / 2 && this->capacity > 64)
    {
        this->capacity /= 2;
        this->resize(this->capacity);
    }
}

template<typename T>
Array<T>::Array()
{
    this->size = 0;
    this->capacity = 8;
    this->data = new Data<T>[this->capacity];
    this->iterator = nullptr;
}

template<typename T>
Array<T>::Array(int capacity)
{
    this->size = capacity;
    this->capacity = capacity;
    this->data = new Data<T>[this->capacity];
    this->iterator = nullptr;
}

template<typename T>
Array<T>::Array(Array<T>& datas)
{
    this->size = datas.size;
    this->capacity = datas.capacity;
    this->data = new Data<T>[this->capacity];
    for (int i = 0; i < this->size; i++)
    {
        this->data[i] = datas.data[i];
    }
    this->iterator = nullptr;
}

template<typename T>
Array<T>::~Array()
{
    delete[] this->data;
}

template<typename T>
void Array<T>::push_back(T data)
{
    this->addCapacity();
    this->data[this->size] = data;
    this->size++;
}

template<typename T>
void Array<T>::pop_back()
{
    this->reduceCapacity();
    this->size--;
}

template<typename T>
void Array<T>::insert(int index, T data)
{
    if (index < 0 || index > this->size)
    {
        throw std::out_of_range("Index out of range");
        return;
    }
    this->addCapacity();
    for (int i = this->size; i > index; i--)
    {
        this->data[i] = this->data[i - 1];
    }
    this->data[index] = data;
    this->size++;
}

template<typename T>
void Array<T>::insert(int index, Array<T> datas)
{
    if (index < 0 || index > this->size)
    {
        throw std::out_of_range("Index out of range");
        return;
    }
    this->size += datas.getsize();
    this->capacity += datas.getsize();
    this->resize(this->capacity);
    for (int i = this->size - 1; i >= index + datas.getsize(); i--)
    {
        this->data[i] = this->data[i - datas.getsize()];
    }
}


template<typename T>
void Array<T>::erase(int index)
{
    if (index < 0 || index >= this->size)
    {
        throw std::out_of_range("Index out of range");
        return;
    }
    for (int i = index; i < this->size - 1; i++)
    {
        this->data[i] = this->data[i + 1];
    }
    this->size--;
    this->reduceCapacity();
}

template<typename T>
void Array<T>::erase(int start, int end)
{
    if (start < 0 || start >= this->size || end < 0 || end >= this->size)
    {
        throw std::out_of_range("Index out of range");
        return;
    }
    if (start > end)
    {
        throw std::out_of_range("Start index is greater than end index");
        return;
    }
    for (int i = start; i < this->size - (end - start); i++)
    {
        this->data[i] = this->data[i + (end - start) + 1];
    }
    this->size -= (end - start) + 1;
    this->reduceCapacity();
}

template<typename T>
int Array<T>::getsize()
{
    return this->size;
}

template<typename T>
int Array<T>::getcapacity()
{
    return this->capacity;
}

template<typename T>
T& Array<T>::get(int index)
{
    if (index < 0 || index >= this->size)
    {
        throw std::out_of_range("Index out of range");
    }
    return this->data[index].getData();
}

template<typename T>
void Array<T>::set(int index, T data)
{
    if (index < 0 || index >= this->capacity)
    {
        throw std::out_of_range("Index out of range");
        return;
    }
    this->data[index] = data;
}

template<typename T>
bool Array<T>::empty()
{
    return this->size == 0;
}

template<typename T>
void Array<T>::clear()
{
    this->size = 0;
    this->capacity = 8;
    this->resize(this->capacity);
}

template<typename T>
void Array<T>::resize(int capacity)
{
    Data<T>* temp = new Data<T>[capacity];
    memcpy(temp, this->data, this->size * sizeof(Data<T>));
    delete[] this->data;
    this->data = temp;
    this->capacity = capacity;

    if (this->data == nullptr)
    {
        throw std::bad_alloc();
        return;
    }
    if (this->size > capacity)
    {
        throw std::out_of_range("Size is greater than capacity");
        return;
    }
}

template<typename T>
T& Array<T>::operator[](int index)
{
    if (index < 0 || index >= this->capacity)
    {
        throw std::out_of_range("Index out of range");
        return this->data[0].getData();
    }
    return this->data[index].getData();
}

template<typename T>
Array<T>& Array<T>::operator=(Array<T>& datas)
{
    this->size = datas.getsize();
    this->capacity = datas.getcapacity();
    this->data = new Data<T>[this->capacity];
    memcpy(this->data, datas.data, this->size * sizeof(Data<T>));
    return *this;
}

template<typename T>
bool Array<T>::operator==(Array<T>& datas)
{
    if (this->size != datas.size)
    {
        return false;
    }
    for (int i = 0; i < this->size; i++)
    {
        if (this->data[i] != datas.data[i])
        {
            return false;
        }
    }
    return true;
}

template<typename T>
bool Array<T>::operator!=(Array<T>& datas)
{
    return !(*this == datas);
}

template<typename T>
Data<T>* Array<T>::begin()
{
    return &this->data[0];
}

template<typename T>
Data<T>* Array<T>::end()
{
    return &this->data[this->size];
}

