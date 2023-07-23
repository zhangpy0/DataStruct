#include <iostream>

template<typename T>
class Data
{
private:
    T data;
public:
    Data();
    Data(T data);
    ~Data();
    T& getData();

    T& operator=(T data);
    bool operator==(T data);
    bool operator==(Data<T>& data_);
    bool operator!=(T data);
    bool operator!=(Data<T>& data_);
    
    T* operator+(int size);
    T* operator-(int size);
};

template<typename T>
Data<T>::Data()
{
}

template<typename T>
Data<T>::Data(T data)
{
    this->data = data;
}

template<typename T>
Data<T>::~Data()
{
}

template<typename T>
T& Data<T>::getData()
{
    return data;
}

template<typename T>
T& Data<T>::operator=(T data)
{
    this->data = data;
    return this->data;
}

template<typename T>
bool Data<T>::operator==(T data)
{
    return this->data == data;
}

template<typename T>
bool Data<T>::operator==(Data<T>& data_)
{
    return this->data == data_.getData();
}

template<typename T>
bool Data<T>::operator!=(T data)
{
    return this->data != data;
}

template<typename T>
bool Data<T>::operator!=(Data<T>& data_)
{
    return this->data != data_.getData();
}

template<typename T>
T* Data<T>::operator+(int size)
{
    return &data + size;
}

template<typename T>
T* Data<T>::operator-(int size)
{
    return &data - size;
}

