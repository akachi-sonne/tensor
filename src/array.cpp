#include<iostream>
#include<vector>
#include"array.hpp"



// outer class constructors and destructor
template<typename T>
Array::Array(std::vector<unsigned int> shape)
{
    this->shape = shape;
    this->dim = shape.size();
    this->size = 1;
    for (int i = 0; i < this->dim; i++)
    {
        this->size *= shape[i];
    }
    Container<T, size> arr;
}

Array::~Array()
{
    delete[] this->container;
    delete this->shape;
    delete this->dim;
    delete this->size;
}

// << operator assigns any single primitive type to every
// component of the array.

void Array::operator << (T x)
{
    this->arr << x;
}

// = operator makes a deep copy of any iterable, including
// objects from this class.
void Array::operator = (T x)
{
    this->arr = x;
}

void Array::print()
{
    this->arr.print();
}

/* Nested class; simple array methods.
* 
* This allows size declaration to remain ambiguous and be calculated via 'shape'
* attribute in the main class' constructor.
*
* We can also simulate a dynamic array by deleting and creating a new object without
* affecting the main object the user directly interacts with.
*
* Note: The resizing aspect of this approach will eat some processing time and is not as 
* fast as an std::vector. This class should not be used if frequent resizing is the main goal
* for what will be an otherwise simple 1-D array.
*/

Array::Container::Container()
{
}
Array::Container::~Container()
{
    delete[] this->container;
}

void Array::Container::operator << (CT x)
{
    for (int i = 0; i < CN; i++)
    {
        this->container[i] = x;
    }
}

void Array::Container::operator = (CT x)
{
    for (int i =0; i< CN; i++)
    {
        this->container[i] = x;
    }
}

void Array::Container::print()
{
    for (int i = 0; i < CN; i++)
    {
        std::cout << this->container[i] << "\n";
    }
}
