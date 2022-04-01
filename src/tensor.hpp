/*
 * -------------------------------------------------------------------------
 * MIT License
 *
 * Copyright (c) 2022 Doug Palmer
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * -------------------------------------------------------------------------
 */

/*
 * -------------------------------------------------------------------------
 * @file array.hpp
 * @author Doug Palmer
 * @version 1.0
 *
 * Description of class Tensor.
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
#include<map>
#include<stdexcept>
#include<cmath>

/* comment out the following line to turn on debugging. */
#define NDEBUG
#include<cassert>

template<typename T>
class Tensor
{   /*******************************
     * Private Member Declarations *
     *******************************/

    // Full size of container. i.e. Number of elements in array
    unsigned int size;

    // Number of dimensions.
    unsigned int rank;

    // Size of each dimension.
    std::vector<unsigned int> shape;

    // Contiguous block of memory for element storage.
    T * container = new T[1];

public:

    /******************************
     * Public Method Declarations *
     ******************************/

    // Constructor that takes an unsigned integer as size.
    // Basically a creates an empty linear array of length 'size'.
    // eg. Tensor x(5); creates linear array of length 5.
    Tensor(unsigned int size);

    // Constructor taking a shape vector as a parameter.
    // Creates any shape N-dimensional array.
    Tensor(std::vector<unsigned int> shape);

    // Copy constructor.
    Tensor(const Tensor &rhs);

    // Destructor.
    ~Tensor();

    // Returns this->size.
    unsigned int get_size() const;

    // Returns this->rank.
    unsigned int get_rank() const;

    // Returns this->shape.
    std::string get_shape() const;

    // Returns 1-dimensional equivalent to n-dimensional
    // indice parameters.
    int get_index(std::vector<unsigned int> coordinates) const;

    // Prints Tensor according to current shape.
    // Passing a truthy parameter invokes verbose printing,
    // which will include size, shape, and rank in the cout 
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
    // bool every(); // Accepts a lambda. Checks if every elements passes a test.
    // void for_each(); // Accepts a lambda. Iterates over array and applies given lambda to each element.
    // Tensor<T> concat(); // deep copy both arrays. Creates new object.
    // Tensor<T> slice();
    // ******************

    // Returns true if sorted in either ascending or descending order; else returns false.
    bool is_sorted();

    // Simple addition of all elements.
    T sum();

    /* Averages */

    // Returns sum()/size()
    T mean();
    // Returns middle most element or average of two middle elements.
    // Tensor must be sorted in either ascending or descending order.
    T median();
    // Returns most common element(s) as vector to account for potential multi-mode scenario.
    std::vector<int> mode();

    // Returns max value in container.
    T max();

    // Returns min value in container.
    T min();

    // Merge sort algorithm
    void sort(bool reverse = false);

    // reverses elements in place
    void reverse();

    // Copy assignment operator.
    //
    // Will assign individual value across every element if passed like:
    // object = value;
    //
    // Will assign value to individual element if passed like:
    // object[index] = value;
    //
    void operator =(T rhs);

    // Tensor index operator
    //
    // Accesses value based on 1-dimensional index.
    // For N-dimensional index access, use () operator.
    //
    // Will return reference to value of index.
    // Can be used for value access or assignment to object.
    //
    T& operator [](int index) const;

    // () Tensor index operator
    //
    // Accesses value based on N-dimensional indice.
    //
    // Will return reference to value of index.
    // Can be used for value access or assignment.
    //
    T& operator ()(std::vector<unsigned int> index) const;

    template<typename T1>
    friend std::ostream& operator<<(std::ostream& out, const Tensor<T1> &arr);

private:
    void sort_worker(T * arr, const int sz, bool reverse = false);

}; // End of Tensor class declarations.


/***********************
 * Tensor Class Methods *
 ***********************/

/* Constructors/destructor */

template<typename T>
Tensor<T>::Tensor(unsigned int size)
{
    this->size = size;
    this->shape = {this->size};
    this->rank = 1;

    T * tmp_ptr = this->container;
    this->container = new T[size];
    delete[] tmp_ptr;
} // End constructor with size as argument

template<typename T>
Tensor<T>::Tensor(std::vector<unsigned int> shape)
{
    this->shape = shape;
    this->rank = shape.size();
    this->size = 1;

    for (int i = 0; i < this->rank; i++)
    {
        this->size *= this->shape[i];
    }

    T * tmp_ptr = this->container;
    this->container = new T[size];
    delete tmp_ptr;
} // End constructor with shape as argument.

template<typename T>
Tensor<T>::Tensor(const Tensor &rhs)
{
    // size, rank, shape, container
    this->size = rhs.size;
    this->rank = rhs.rank;
    this->shape = rhs.shape;

    T * tmp = this->container;
    this->container = new T[this->size];
    delete[] tmp;
    for (int i = 0; i < this->size; i++)
    {
        *(this->container + i) = rhs.container[i];
    }
} // End copy constructor

template<typename T>
Tensor<T>::~Tensor()
{
    delete[] this->container;
}

/* "get_member" methods */
template<typename T>
unsigned int Tensor<T>::get_size() const
{
    return size;
}

template<typename T>
unsigned int Tensor<T>::get_rank() const
{
    return rank;
}

/* Output methods */

template<typename T>
std::string Tensor<T>::get_shape() const
{
    std::string str = "{";
    for (int i = 0; i < this->rank; i++)
    {
        str += std::to_string(this->shape[i]);
        if (i < this->rank - 1)
        {
            str += ", ";
        }
    }
    str += "}";
    return str;
}

template<typename T>
void Tensor<T>::print(bool verbose)
{
    if (verbose)
    {
        std::cout << "Tensor shape: {";
        for (int i = 0; i < this->rank; i++)
        {
            std::cout << this->shape[i];
            if (i < this->rank - 1)
            {
                std::cout << ", ";
            }
            else
            {
                std::cout << "}" << std::endl;
            }
        }
        std::cout << "Number of dimensions: " << this->rank << std::endl;
        std::cout << "Total elements: " << this->size << std::endl;
    }

    int which_dim = this->rank;
    bool new_row = false;
    int tracker[this->rank] = {0};
    std::cout << "[";
    for (int i = 0; i < this->size; i++)
    {
        int spaces = this->rank - which_dim;
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
        for (int j = this->rank-1; j >= 0; j--)
        {
            tracker[j]++;
            which_dim = this->rank - j;
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
void Tensor<T>::print_flat()
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
bool Tensor<T>::is_sorted()
{
    bool ascending = *(this->container) < *(this->container + 1);
    if (ascending)
    {
        for (int i = 0; i < this->size - 1; i++)
        {
            if (*(this->container + i) > *(this->container + i + 1))
            {
                return false;
            }
        }
    }
    else
    {
        for (int i = 0; i < this->size - 1; i++)
        {
            if (*(this->container + i) < *(this->container + i + 1))
            {
                return false;
            }
        }
    }
    return true;
}

template<typename T>
T Tensor<T>::sum()
{
    T total = 0;
    for (int i = 0; i < this->size; i++)
    {
        total += *(this->container + i);
    }
    return total;
}

template<typename T>
T Tensor<T>::mean()
{
    return float(sum() / this->size);
}

template<typename T>
T Tensor<T>::median()
{
    assert(this->is_sorted());

    int mid = floor(this->size/2);
    if (this->size % 2 == 0)
    {
        T l = *(this->container + mid);
        T r = *(this->container + mid + 1);
        return (l + r) / 2;
    }
    else
    {
        return *(this->container + mid);
    }
}

template<typename T>
std::vector<int> Tensor<T>::mode()
{
    std::vector<int> multimode;
    std::map<T, int> totals;
    int max = 0;

    for (int i = 0; i < this->size; i++)
    {
       if (totals.contains(*(this->container + i)))
        {
            totals[*(this->container + i)] = totals[*(this->container + i)] + 1;
        }
        else
        {
            totals[*(this->container + i)] = 1;
        }
        if (totals[*(this->container + i)] > max)
        {
            max = totals[*(this->container + i)];
        }
    }

    for (auto const& [key, val] : totals)
    {
        if (val == max)
        {
            multimode.push_back(key);
        }
    }

    return multimode;

}

template<typename T>
T Tensor<T>::max()
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
T Tensor<T>::min()
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
int Tensor<T>::get_index(std::vector<unsigned int> coordinates) const
{
    assert(coordinates.size() == this->rank);
    int index = 0;
    for (int i = 0; i < this->rank; i++)
    {
        for (int j = this->rank -1; j > i; j--)
        {
            index += coordinates[i] * this->shape[j];
        }
    }
    return index + coordinates[this->rank - 1];
}

/* Modification methods */

template<typename T>
void Tensor<T>::sort(bool reverse)
{
    sort_worker(this->container, this->size, reverse);
    return;
}

template<typename T>
void Tensor<T>::sort_worker(T * arr, const int sz, bool reverse)
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
            if (reverse)
            {
                *(arr + (sz-(index+1))) = *(larr + lindex);
                lindex++;
                index++;
            }
            else
            {
                *(arr + index) = *(larr + lindex);
                lindex++;
                index++;
            }
        }
        else
        {
            if (reverse)
            {
                *(arr + (sz-(index+1))) = *(rarr + rindex);
                rindex++;
                index++;
            }
            else
            {
                *(arr + index) = *(rarr + rindex);
                rindex++;
                index++;
            }
        }
    }

    // Add any remaining elements from either sub-array.
    while (lindex < lsz)
    {
        if (reverse)
        {
            *(arr + (sz-index-1)) = *(larr + lindex);
            lindex++;
            index++;
        }
        else
        {
            *(arr + index) = *(larr + lindex);
            lindex++;
            index++;
        }
    }
    while (rindex < rsz)
    {
        if (reverse)
        {
            *(arr + (sz-index-1)) = *(rarr + rindex);
            rindex++;
            index++;
        }
        else
        {
            *(arr + index) = *(rarr + rindex);
            rindex++;
            index++;
        }
    }

    // free up any memory allocated to subs
    delete[] larr;
    delete[] rarr;

    return;
} // end of sort_worker

template<typename T>
void Tensor<T>::reverse()
{
    int temp;
    for (int i = 0; i < this->size/2; i++)
    {
        temp = *(this->container + i);
        *(this->container + i) = *(this->container + (this->size - i - 1));
        *(this->container + (this->size - i - 1)) = temp;
    }
}

/* Operators */

template<typename T>
void Tensor<T>::operator =(T rhs)
{
    for (int i = 0; i < this->size; i++)
    {
        *(this->container+i) = rhs;
    }
}
template<typename T>
T& Tensor<T>::operator [](int index) const
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
T& Tensor<T>::operator ()(std::vector<unsigned int> index) const
{
    return *(this->container + get_index(index));
}

template<typename T1>
std::ostream& operator<<(std::ostream& out, const Tensor<T1>& arr)
{
    int sz = arr.get_size();
    if (sz == 0)
    {
        out << "empty array";
    }
    else
    {
        out << "[" << std::to_string(arr[0]);
        for (int i = 1; i < sz; i++)
        {
            out << ", " << std::to_string(arr[i]);
        }
        out << "]";
    }
    return out;
}

#endif