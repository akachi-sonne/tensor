/*
 * -------------------------------------------------------------------------
 * Copyright 2022 Douglas W. Palmer
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * -------------------------------------------------------------------------
 */

/* @file array.hpp
 * @author Doug Palmer
 * @version 1.0
 *
 * Description of class Array.
 *
 * Multidimensional array class template stored in contiguous memory on
 * the heap.
 *
 * For usage, see the README.md file at: https://github.com/akachi-sonne/clin/blob/main/README.md
 *
 */


#define NDEBUG // Uncomment to turn on debugging

#include<iostream>
#include<vector>
#include<stdexcept>
#include<cassert>

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
    unsigned int get_size();
    unsigned int get_dims();
    std::string get_shape();
    void print(bool verbose = false);
    void print_flat();
    // void sort();
    // void reverse();
    // T mean();
    // T median();
    // T mode();
    // T max();
    // T min();
    // bool every(); // Accepts a lambda. Checks if every elements passes a test.
    // void for_each(); // Accepts a lambda. Iterates over array and applies given lambda to each element.
    // Array<T> concat();
    // Array<T> slice();
    void operator =(T rhs);
    T& operator [](int index);
    T& operator ()(std::vector<unsigned int> index);
    int get_index(std::vector<unsigned int> coordinates);
private:
    void print_helper();

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
unsigned int Array<T>::get_size()
{
    return size;
}
template<typename T>
unsigned int Array<T>::get_dims()
{
    return dims;
}
template<typename T>
std::string Array<T>::get_shape()
{
    std::string str = "{";
    for (int i = 0; i < this->dims; i++)
    {
        str += std::to_string(this->shape[i]);
        if (i < this->dims - 1)
        {
            str += ", ";
        }
    }
    str += "}";
    return str;
}
template<typename T>
void Array<T>::print(bool verbose)
{
    if (verbose)
    {
        std::cout << "Array shape: {";
        for (int i = 0; i < this->dims; i++)
        {
            std::cout << this->shape[i];
            if (i < this->dims - 1)
            {
                std::cout << ", ";
            }
            else
            {
                std::cout << "}" << std::endl;
            }
        }
        std::cout << "Number of dimensions: " << this->dims << std::endl;
        std::cout << "Total elements: " << this->size << std::endl;
    }

    int which_dim = this->dims;
    bool new_row = false;
    int tracker[this->dims] = {0};
    std::cout << "[";
    for (int i = 0; i < this->size; i++)
    {
        int spaces = this->dims - which_dim;
        if (new_row)
        {
            for (int i = 0; i < spaces; i++)
            {
                std::cout << " ";
            }
        }
        else if (i != 0)
        {
            std::cout << ", ";
        }
        new_row = false;
        while (which_dim > 1)
        {
            std::cout << "[";
            which_dim--;
        }
        std::cout << *(this->container + i);
        // update tracker
        for (int j = this->dims-1; j >= 0; j--)
        {
            tracker[j]++;
            which_dim = this->dims - j;
            if (tracker[j] >= this->shape[j])
            {
                which_dim++;
                tracker[j] = 0;
                new_row = true;
                std::cout << "]";
            }
            else
            {
                break;
            }
        }
        if (new_row && i < this->size - 1)
        {
            std::cout << ",\n ";
        }
    }
    std::cout <<"\n" << std::endl;
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
template<typename T>
void Array<T>::operator =(T rhs)
{
    for (int i = 0; i < this->size; i++)
    {
        *(this->container+i) = rhs;
    }
}
template<typename T>
T& Array<T>::operator [](int index)
{
    assert(index < this->size);
    if (index >= 0)
    {
        return *(this->container + index);
    }
    else
    {
        int neg_index = this->size - (index - (2 * index));
        assert(neg_index < this->size);
        return *(this->container + neg_index);
    }
}

template<typename T>
T& Array<T>::operator ()(std::vector<unsigned int> index)
{
    return *(this->container + get_index(index));
}

template<typename T>
int Array<T>::get_index(std::vector<unsigned int> coordinates)
{
    assert(coordinates.size() == this->dims);
    int index = 0;
    for (int i = 0; i < this->dims; i++)
    {
        for (int j = this->dims -1; j > i; j--)
        {
            index += coordinates[i] * this->shape[j];
        }
    }
    return index + coordinates[this->dims - 1];
}
