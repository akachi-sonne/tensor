#include<iostream>
#include<vector>

template<typename T>
class Array
{
    unsigned int size;
    unsigned int dims;
    std::vector<unsigned int> shape;
    T * container = new T[1];
public:
    Array(unsigned int size);
    Array(std::vector<unsigned int> shape);
    ~Array();
    void print();
    void operator<< (T rhs);
};

template<typename T>
Array<T>::Array(unsigned int size)
{
    this->size = size;
    this->shape = {size};
    this->dims = 1;

    T * tmp_ptr = this->container;
    this->container = new T[size];
    delete[] tmp_ptr;
}
template<typename T>
Array<T>::Array(std::vector<unsigned int> shape)
{
    this->shape = shape;
    this->dims = shape.size();
    this->size = 1;

    for (int i = 0; i < this->dims; i++)
    {
        this->size *= this->shape[i];
    }

    T * tmp_ptr = this->container;
    this->container = new T[size];
    delete tmp_ptr;
}
template<typename T>
Array<T>::~Array()
{
    delete[] this->container;
}
template<typename T>
void Array<T>::print()
{
    for (int i = 0; i < this->size; i++)
    {
        std::cout << *(this->container + i) << " ";
    }
    std::cout << "\n";
}
template<typename T>
void Array<T>::operator <<(T rhs)
{
    for (int i = 0; i < this->size; i++)
    {
        *(this->container+i) = rhs;
    }
}
