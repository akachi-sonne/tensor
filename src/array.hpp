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

/* 
 * -------------------------------------------------------------------------
 * @file array.hpp
 * @author Doug Palmer
 * @version 1.0
 *
 * Description of class Array.
 *
 * Multidimensional array class template stored in contiguous memory on
 * the heap.
 *
 * For full usage, see the README.md file at:
 * https://github.com/akachi-sonne/clin/blob/main/README.md
 * -------------------------------------------------------------------------
 */

#ifndef ARRAY_H
#define ARRAY_H

#include<iostream>
#include<vector>
#include<stdexcept>
#include<cmath>

/* comment out the following line to turn on debugging. */
#define NDEBUG
#include<cassert>

template<typename T>
class Array
{   /*******************************
     * Private Member Declarations *
     *******************************/

    // Full size of container. i.e. Number of elements in array
    unsigned int size;

    // Number of dimensions.
    unsigned int dims;

    // Size of each dimension.
    std::vector<unsigned int> shape;

    // Contiguous block of memory for element storage.
    T * container = new T[1];

    /******************************
     * Public Method Declarations *
     ******************************/

public:

    // Constructor that takes an unsigned integer as size.
    // Basically a creates an empty linear array of length 'size'.
    // eg. Array x(5); creates linear array of length 5.
    Array(unsigned int size);

    // Constructor taking a shape vector as a parameter.
    // Creates any shape N-dimensional array.
    Array(std::vector<unsigned int> shape);

    // Destructor.
    ~Array();

    // Returns this->size.
    unsigned int get_size() const;

    // Returns this->dims.
    unsigned int get_dims() const;

    // Returns this->shape.
    std::string get_shape() const;


    // Prints Array according to current shape.
    // Passing a truthy parameter invokes verbose printing,
    // which will include size, shape, and dims in the cout 
    // statement.
    //
    void print(bool verbose = false);


    // Prints array of any dimension as if 1-dimensional.
    //
    // Does *not* include a verbose option.
    //
    void print_flat();

    // ******************
    // * future methods *
    // ******************
    // void reverse();
    // bool every(); // Accepts a lambda. Checks if every elements passes a test.
    // void for_each(); // Accepts a lambda. Iterates over array and applies given lambda to each element.
    // Array<T> concat(); // deep concatenation. Creates new object.
    // Array<T> slice();
    // ******************

    // Merge sort algorithm
    void sort();
    bool is_sorted();

    T sum();

    // Averages
    T mean();
    //T median();
    //T mode();

    // Returns max value in container.
    T max();

    // Returns min value in container.
    T min();

    // Copy assignment operator.
    //
    // Will assign individual value across every element if passed like:
    // object = value;
    //
    // Will assign value to individual element if passed like:
    // object[index] = value;
    //
    void operator =(T rhs);

    // Array index operator
    //
    // Accesses value based on 1-dimensional index.
    // For N-dimensional index access, use () operator.
    //
    // Will return reference to value of index.
    // Can be used for value access or assignment to object.
    //
    T& operator [](int index);

    // () Array index operator
    //
    // Accesses value based on N-dimensional indice.
    //
    // Will return reference to value of index.
    // Can be used for value access or assignment.
    //
    T& operator ()(std::vector<unsigned int> index);

    // Returns 1-dimensional equivalent to n-dimensional
    // indice parameters.
    int get_index(std::vector<unsigned int> coordinates);

private:
    void sort_worker(T * arr, const int sz);

}; // End of Array class declarations.


/***********************
 * Array Class Methods *
 ***********************/

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
unsigned int Array<T>::get_size() const
{
    return size;
}
template<typename T>
unsigned int Array<T>::get_dims() const
{
    return dims;
}
template<typename T>
std::string Array<T>::get_shape() const
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
void Array<T>::sort_worker(T * arr, const int sz)
{
    // base case
    if (sz == 1)
    {
        return;
    }

    // If size > 1, split in half and make recursive calls
    // until all sub-arrays are of size 1.
    const int lsz = floor(sz / 2); // left sub-array size
    const int rsz = sz - lsz; // right sub-array size

    // Heap allocated sub-arrays to avoid stack overflow
    // from recursive calls.
    T * larr = new T[lsz]; // left
    T * rarr = new T[rsz]; // right

    // Assign first half of input array to larr and second
    // half to rarr.
    int count = 0;
    for (int i = 0; i < lsz; i++)
    {
        *(larr + i) = *(arr + count);
        count++;
    }
    for (int i = 0; i < rsz; i++)
    {
        *(rarr + i) = *(arr + count);
        count++;
    }

    // recursive calls
    sort_worker(larr, lsz);
    sort_worker(rarr, rsz);

    // Sub-arrays should now be sorted.
    // Proceed with merging.
    int index = 0;
    int lindex = 0;
    int rindex = 0;
    while (lindex < lsz && rindex < rsz)
    {
        // Compare next index in larr and rarr
        // to insert the smaller of each as the next
        // element of the input array "arr".
        if (*(larr + lindex) < *(rarr + rindex))
        {
            *(arr + index) = *(larr + lindex);
            lindex++;
            index++;
        }
        else
        {
            *(arr + index) = *(rarr + rindex);
            rindex++;
            index++;
        }
    }

    // Add any remaining elements from either sub-array.
    while (lindex < lsz)
    {
        *(arr + index) = *(larr + lindex);
        lindex++;
        index++;
    }
    while (rindex < rsz)
    {
        *(arr + index) = *(rarr + rindex);
        rindex++;
        index++;
    }

    // free up any memory allocated to subs
    delete[] larr;
    delete[] rarr;

    return;
} // end of sort_worker

template<typename T>
void Array<T>::sort()
{
    sort_worker(this->container, this->size);
    return;
}

template<typename T>
bool Array<T>::is_sorted()
{
    for (int i = 0; i < this->size - 1; i++)
    {
        if (*(this->container + i) > *(this->container + i + 1))
        {
            return false;
        }
    }
    return true;
}

template<typename T>
T Array<T>::sum()
{
    T total = 0;
    for (int i = 0; i < this->size; i++)
    {
        total += *(this->container + i);
    }
    return total;
}

template<typename T>
T Array<T>::mean()
{
    return float(sum() / this->size);
}

/* need to write sort() first
 *
template<typename T>
T Array<T>::median()
{

}
 *
 */
/*
template<typename T>
T Array<T>::mode()
{

}
*/
template<typename T>
T Array<T>::max()
{
    int max = *(this->container);
    for (int i = 1; i < this->size; i++)
    {
        if (max < *(this->container + i))
        {
            max = *(this->container + i);
        }
    }
    return max;
}

template<typename T>
T Array<T>::min()
{
    int min = *(this->container);
    for (int i = 1; i < this->size; i++)
    {
        if (min > *(this->container + i))
        {
            min = *(this->container + i);
        }
    }
    return min;
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

#endif
