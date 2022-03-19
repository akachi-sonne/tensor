#include<iostream>
#include<array>
#include<vector>
#include<stdexcept>

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
    void print_flat();
//    void print();
    void operator<< (T rhs);
    int where(std::vector<unsigned int> coords);
private:
//    void print_helper();

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
void Array<T>::print_flat()
{
    std::cout << "[";
    for (int i = 0; i < this->size; i++)
    {
        std::cout << *(this->container + i);
        if (i < this->size -1)
        {
            std::cout << ", ";
        } else 
        {
            std::cout << "]" << std::endl;
        }
    }
    std::cout << "\n";
}
/*
template<typename T>
void Array<T>::print_helper(std::array<unsigned int> this->dims> &tracker, unsigned int &row_counter)
{
    
}
template<typename T>
void Array<T>::print()
{
    std::array<unsigned int> this->dims> tracker;
    unsigned int row_counter = this->dims;
}
*/
template<typename T>
void Array<T>::operator <<(T rhs)
{
    for (int i = 0; i < this->size; i++)
    {
        *(this->container+i) = rhs;
    }
}
template<typename T>
int Array<T>::where(std::vector<unsigned int> coords)
{
    if (coords.size() != this->dims)
    {
        throw std::invalid_argument("coordinate vector input must match num dimensions");
    }
    int index = 0;
    for (int i = 0; i < this->dims; i++)
    {
        for (int j = this->dims -1; j > i; j--)
        {
            index += coords[i] * this->shape[j];
        }
    }
    return index + coords[this->dims - 1];
}
