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
 * @file tensor.hpp
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
#include<iterator>
#include<cstddef>
#include<vector>
#include<map>
#include<stdexcept>
#include<cmath>
#include<algorithm>

/* comment out the following line to turn on debugging. */
#define NDEBUG
#include<cassert>

template<typename T>
class Tensor
{   /*******************************
     * Private Member Declarations *
     *******************************/

    // Full size of _container. i.e. Number of elements in array
    unsigned int _size;

    // Number of dimensions.
    unsigned int _rank;

    // Length of each dimension.
    std::vector<unsigned int> _shape;

    // Contiguous block of memory for element storage.
    T * _container = new T[1];

public:

    struct Iterator
    {
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        Iterator( pointer p ) : ptr(p) {}

        reference operator*() const
        {
            return *ptr;
        }

        pointer operator->()
        {
            return ptr;
        }

        // Pre increment
        Iterator& operator++()
        {
            ptr++;
            return *this;
        }

        // Post increment
        Iterator operator++( int )
        {
            Iterator temp = *this;
            ++( *this );
            return temp;
        }

        // Pre decrement
        Iterator& operator--()
        {
            ptr--;
            return *this;
        }

        // Post decrement
        Iterator operator--( int )
        {
            Iterator temp = *this;
            --( *this );
            return temp;
        }

        friend bool operator==( const Iterator& x, const Iterator& y )
        {
            return x.ptr == y.ptr;
        };

        friend bool operator!=( const Iterator& x, const Iterator& y )
        {
            return x.ptr != y.ptr;
        };

        friend bool operator<( const Iterator& x, const Iterator& y )
        {
            return x.ptr < y.ptr;
        };

        friend bool operator>( const Iterator& x, const Iterator& y )
        {
            return x.ptr > y.ptr;
        };

        friend bool operator<=( const Iterator& x, const Iterator& y )
        {
            return x.ptr <= y.ptr;
        };

        friend bool operator>=( const Iterator& x, const Iterator& y )
        {
            return x.ptr >= y.ptr;
        };

    private:
        pointer ptr;

    };

    Iterator begin()
    {
        return Iterator( this->_container );
    }

    Iterator end()
    {
        return Iterator( this->_container + this->_size );
    }

    /******************************
     * Public Method Declarations *
     ******************************/

    // Default constructor
    // Assigns everything to 0
    Tensor();

    // Constructor that takes an unsigned integer as size.
    // Creates an empty linear array of length 'size'.
    // eg. Tensor x(5); creates linear array of length 5.
    Tensor( unsigned int size );

    // Constructor taking a shape vector as a parameter.
    // Creates any shape N-dimensional array.
    Tensor( std::vector<unsigned int> shape );

    // Copy constructor.
    Tensor( const Tensor &rhs );

    // Move constructor
    Tensor( Tensor&& other ) noexcept;

    // Destructor.
    ~Tensor();

    // Returns this->_size.
    unsigned int size() const;

    // Returns this->_rank.
    unsigned int rank() const;

    // Returns this->_shape.
    std::vector<unsigned int> shape() const;

    // Returns 1-dimensional equivalent to n-dimensional
    // indice parameters.
    int index( std::vector<unsigned int> coordinates ) const;

    // Prints Tensor according to current shape.
    // Passing a truthy parameter invokes verbose printing,
    // which will include size, shape, and rank in the cout 
    // statement.
    //
    void print( bool verbose = false );

    // Prints array of any dimension as if 1-dimensional.
    //
    // Does *not* include a verbose option.
    //
    void print_flat();

    // ******************
    // * future methods *
    // ******************
    // bool every(); // Accepts a lambda. Checks if every elements passes a test.
    // void for_each(); // Accepts a lambda. Iterates over array and applies given 
    // lambda to each element.
    // Tensor<T> concat(); // deep copy both arrays. Creates new object.
    // Tensor<T> slice();
    // Tensor<T> operator @(T& rhs);
    // Tensor<T> inverse();
    // Tensor<T> T(); // transpose
    // Tensor<T> det(); // returns determinant if nxn square matrix. Returns
    // hyper-determinant if rank >= 3.
    // ******************

    // Returns true if sorted in either ascending or descending order; else returns
    // false.
    bool is_sorted();

    // Simple addition of all elements.
    T sum();

    /* Averages */

    // Returns sum()/size()
    float mean();

    // Returns middle most element or average of two middle elements.
    // Tensor must be sorted in either ascending or descending order.
    float median();

    // Returns most common element(s) as vector to account for potential multi-mode
    // scenario.
    std::vector<T> mode();

    // Returns max value in _container.
    T max();

    // Returns min value in _container.
    T min();

    // Merge sort algorithm
    void sort( bool reverse = false );

    // reverses elements in place
    void reverse();

    // Scalar addition operator
    //
    Tensor<T> operator+( const T rhs );

    // Tensor addition operator
    //
    Tensor<T> operator+( const Tensor<T>& rhs );

    // Scalar addition assignment operator
    //
    void operator+=( const T rhs );

    // Tensor addition assignment operator
    //
    void operator+=( const Tensor<T>& rhs );

    // Scalar subtraction operator
    //
    Tensor<T> operator-( const T rhs );

    // Tensor subtraction operator
    //
    Tensor<T> operator-( const Tensor<T>& rhs );

    // Scalar subtraction assignment operator
    //
    void operator-=( const T rhs );

    // Tensor subtraction assignment operator
    //
    void operator-=( const Tensor<T>& rhs );

    // Scalar multiplication operator
    //
    Tensor<T> operator*( const T rhs );

    // Tensor multiplication operator
    //
    //Tensor<T> operator*( Tensor<T>& rhs );

    // Dot product
    //
    T dot(Tensor<T>& rhs);

    // Fill assignment operator.
    //
    // Will assign individual value across every element if passed like:
    // object = value;
    //
    void operator=( T other );

    // Copy assignment operator
    //
    Tensor<T>& operator=( const Tensor<T>& other );

    // Move assignment operator
    //
    Tensor<T>& operator=( Tensor<T>&& other ) noexcept;

    // Tensor index operator
    //
    // Accesses value based on 1-dimensional index.
    // For N-dimensional index access, use () operator.
    //
    // Will return reference to value of index.
    // Can be used for value access or assignment to object.
    //
    T& operator[]( int index ) const;

    // () Tensor index operator
    //
    // Accesses value based on N-dimensional indice.
    //
    // Will return reference to value of index.
    // Can be used for value access or assignment.
    //
    T& operator()( std::vector<unsigned int> index ) const;

    //template<typename F, typename P>
    //friend F forEach(Tensor<T>& tnsr, F(*func)(P));

    template<typename T1>
    friend std::ostream& operator<<( std::ostream& out, const Tensor<T1> &arr );

private:
    void sort_worker( T * arr, const int sz, bool reverse = false );

}; // End of Tensor class declarations.


/***********************
 * Tensor Class Methods *
 ***********************/

/* Constructors/destructor */

// Default constructor
// initializes everything to zero.
template<typename T>
Tensor<T>::Tensor()
{
    this->_size = 0;
    this->_shape = { 0 };
    this->_rank = 0;
    this->_container = nullptr;
} // end default constructor

// Constructor with size as parameter.
// Defaults to 1 dimensional Tensor.
template<typename T>
Tensor<T>::Tensor( unsigned int size )
{
    this->_size = size;
    this->_shape = { this->_size };
    this->_rank = 1;

    T * tmp_ptr = this->_container;
    this->_container = new T[this->_size]();
    delete[] tmp_ptr;

} // End constructor with size as argument

// Constructor with shape as arg
template<typename T>
Tensor<T>::Tensor( std::vector<unsigned int> shape )
{
    this->_shape = shape;
    this->_rank = shape.size();
    this->_size = 1;

    for ( int i = 0; i < this->_rank; i++ )
    {
        this->_size *= this->_shape[i];
    }

    T * tmp_ptr = this->_container;
    this->_container = new T[this->_size]();
    delete tmp_ptr;
} // End constructor with shape as argument.

// Copy constructor
template<typename T>
Tensor<T>::Tensor( const Tensor<T> &rhs )
{
    // size, rank, shape, _container
    this->_size = rhs._size;
    this->_rank = rhs._rank;
    this->_shape = rhs._shape;

    T * tmp = this->_container;
    this->_container = new T[this->_size];
    delete[] tmp;
    for ( int i = 0; i < this->_size; i++ )
    {
        *( this->_container + i ) = rhs._container[i];
    }
} // End copy constructor

// Move constructor
template<typename T>
Tensor<T>::Tensor( Tensor&& other ) noexcept
{
    // size, rank, shape, _container
    this->_size = other._size;
    this->_rank = other._rank;
    this->_shape = other._shape;
    this->_container = other._container;

    other._size = 0;
    other._rank = 0;
    other._shape.clear();
    other._container = nullptr;
} // End move constructor

// Destructor
template<typename T>
Tensor<T>::~Tensor()
{

    delete[] this->_container;

} // end destructor

/* Get member methods */

// size
// returns total amount of elements in tensor
template<typename T>
unsigned int Tensor<T>::size() const
{
    return _size;
} // size

// rank
// returns number of dimensions in tensor
template<typename T>
unsigned int Tensor<T>::rank() const
{
    return _rank;
} // end rank

// shape
// returns length of each dimension
template<typename T>
std::vector<unsigned int> Tensor<T>::shape() const
{
    return _shape;
} // end shape

/* Output methods */

// print
// prints N-dimensional representation of tensor
// based on shape and rank.
template<typename T>
void Tensor<T>::print( bool verbose )
{
    if ( verbose )
    {
        std::cout << "Shape: {";
        for ( int i = 0; i < this->_rank; i++ )
        {
            std::cout << this->_shape[i];
            if ( i < this->_rank - 1 )
            {
                std::cout << ", ";
            }
            else
            {
                std::cout << "}" << std::endl;
            }
        }
        std::cout << "Rank: " << this->_rank << std::endl;
        std::cout << "Size: " << this->_size << std::endl;
    }

    int which_dim = this->_rank;
    bool new_row = false;
    int tracker[this->_rank] = {0};
    std::cout << "[";
    for ( int i = 0; i < this->_size; i++ )
    {
        int spaces = this->_rank - which_dim;
        if ( new_row )
        {
            for ( int i = 0; i < spaces; i++ )
            {
                std::cout << " ";
            }
        }
        else if ( i != 0 )
        {
            std::cout << ", ";
        }
        new_row = false;
        while ( which_dim > 1 )
        {
            std::cout << "[";
            which_dim--;
        }
        std::cout << *( this->_container + i );
        // update tracker
        for ( int j = this->_rank-1; j >= 0; j-- )
        {
            tracker[j]++;
            which_dim = this->_rank - j;
            if ( tracker[j] >= this->_shape[j] )
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
        if ( new_row && i < this->_size - 1 )
        {
            std::cout << ",\n ";
        }
    }
    std::cout <<"\n" << std::endl;
} // end print

// print_flat
// prints 1-D representation of tensor
// regardless of shape or rank.
template<typename T>
void Tensor<T>::print_flat()
{
    std::cout << "[";
    for ( int i = 0; i < this->_size; i++ )
    {
        std::cout << *( this->_container + i );
        if ( i < this->_size -1 )
        {
            std::cout << ", ";
        } else
        {
            std::cout << "]" << std::endl;
        }
    }
    std::cout << "\n";
} // end print_flat

// is_sorted
// returns true if sorted, else false
template<typename T>
bool Tensor<T>::is_sorted()
{
    bool ascending = *( this->_container ) < *( this->_container + 1 );
    if ( ascending )
    {
        for ( int i = 0; i < this->_size - 1; i++ )
        {
            if ( *( this->_container + i ) > *( this->_container + i + 1 ) )
            {
                return false;
            }
        }
    }
    else
    {
        for ( int i = 0; i < this->_size - 1; i++ )
        {
            if ( *( this->_container + i ) < *( this->_container + i + 1 ) )
            {
                return false;
            }
        }
    }
    return true;
} // end is_sorted

// sum
// total value of all elements added together
template<typename T>
T Tensor<T>::sum()
{
    T total = 0;
    for ( int i = 0; i < this->_size; i++ )
    {
        total += *( this->_container + i );
    }
    return total;
} // end sum

// mean
// simple average
template<typename T>
float Tensor<T>::mean()
{
    return float( sum() / this->_size );
} // end mean

// median
// Tensor must be sorted
template<typename T>
float Tensor<T>::median()
{
    assert( this->is_sorted() );

    int mid = floor( this->_size/2 );
    if ( this->_size % 2 == 0 )
    {
        T l = *( this->_container + mid );
        T r = *( this->_container + mid + 1 );
        return ( l + r ) / 2;
    }
    else
    {
        return *( this->_container + mid );
    }
} // end median

// mode
// returns mode of array (or multimode if appropriate)
template<typename T>
std::vector<T> Tensor<T>::mode()
{
    std::vector<int> multimode;
    std::map<T, int> totals;
    int max = 0;

    for ( int i = 0; i < this->_size; i++ )
    {
       if ( totals.contains( *( this->_container + i ) ) )
        {
            totals[*(this->_container + i)] = totals[*(this->_container + i)] + 1;
        }
        else
        {
            totals[ *( this->_container + i ) ] = 1;
        }
        if ( totals[ *( this->_container + i ) ] > max )
        {
            max = totals[ *( this->_container + i ) ];
        }
    }

    for ( auto const& [key, val] : totals )
    {
        if ( val == max )
        {
            multimode.push_back( key );
        }
    }

    return multimode;

} // mode

// max
// returns max value in tensor
template<typename T>
T Tensor<T>::max()
{
    int max = *( this->_container );
    for ( int i = 1; i < this->_size; i++ )
    {
        if ( max < *( this->_container + i ) )
        {
            max = *( this->_container + i );
        }
    }
    return max;
} // end max

// min
// returns minimum value in tensor
template<typename T>
T Tensor<T>::min()
{
    int min = *( this->_container );
    for ( int i = 1; i < this->_size; i++ )
    {
        if ( min > *( this->_container + i ) )
        {
            min = *( this->_container + i );
        }
    }
    return min;
} // end min

// index method
// returns 1-D index from 3-D coordinates
template<typename T>
int Tensor<T>::index( std::vector<unsigned int> coordinates ) const
{
    assert( coordinates.size() == this->_rank );
    int index = 0;
    for ( int i = 0; i < this->_rank; i++ )
    {
        for ( int j = this->_rank -1; j > i; j-- )
        {
            index += coordinates[i] * this->_shape[j];
        }
    }
    return index + coordinates[this->_rank - 1];
} // end index method


/* Modification methods */

// sort tensor
// calls helper method (sort_worker) to implement
// recursive merge sort
template<typename T>
void Tensor<T>::sort( bool reverse )
{
    sort_worker( this->_container, this->_size, reverse );
    return;
} // end sort

// sort_worker
// sorts recursively using merge sort algorithm
template<typename T>
void Tensor<T>::sort_worker( T * arr, const int sz, bool reverse )
{
    // base case
    if ( sz == 1 )
    {
        return;
    }

    // If size > 1, split in half and make recursive calls
    // until all sub-arrays are of size 1.
    const int lsz = floor( sz / 2 ); // left sub-array size
    const int rsz = sz - lsz; // right sub-array size

    // Heap allocated sub-arrays to avoid stack overflow
    // from recursive calls.
    T * larr = new T[lsz]; // left
    T * rarr = new T[rsz]; // right

    // Assign first half of input array to larr and second
    // half to rarr.
    int count = 0;
    for ( int i = 0; i < lsz; i++ )
    {
        *( larr + i ) = *( arr + count );
        count++;
    }
    for ( int i = 0; i < rsz; i++ )
    {
        *( rarr + i ) = *( arr + count );
        count++;
    }

    // recursive calls
    sort_worker( larr, lsz );
    sort_worker( rarr, rsz );

    // Sub-arrays should now be sorted.
    // Proceed with merging.
    int index = 0;
    int lindex = 0;
    int rindex = 0;
    while ( lindex < lsz && rindex < rsz )
    {
        // Compare next index in larr and rarr
        // to insert the smaller of each as the next
        // element of the input array "arr".
        if ( *( larr + lindex ) < *( rarr + rindex ) )
        {
            if ( reverse )
            {
                *( arr + ( sz - ( index + 1 ) ) ) = *( larr + lindex );
                lindex++;
                index++;
            }
            else
            {
                *( arr + index ) = *( larr + lindex );
                lindex++;
                index++;
            }
        }
        else
        {
            if ( reverse )
            {
                *( arr + ( sz - ( index + 1 ) ) ) = *( rarr + rindex );
                rindex++;
                index++;
            }
            else
            {
                *( arr + index ) = *( rarr + rindex );
                rindex++;
                index++;
            }
        }
    }

    // Add any remaining elements from either sub-array.
    while ( lindex < lsz )
    {
        if ( reverse )
        {
            *( arr + ( sz-index-1 ) ) = *( larr + lindex );
            lindex++;
            index++;
        }
        else
        {
            *( arr + index ) = *( larr + lindex );
            lindex++;
            index++;
        }
    }
    while ( rindex < rsz )
    {
        if ( reverse )
        {
            *( arr + ( sz - index - 1 ) ) = *( rarr + rindex );
            rindex++;
            index++;
        }
        else
        {
            *( arr + index ) = *( rarr + rindex );
            rindex++;
            index++;
        }
    }

    // free up any memory allocated to subs
    delete[] larr;
    delete[] rarr;

    return;
} // end of sort_worker

// Reverse method
template<typename T>
void Tensor<T>::reverse()
{
    int temp;
    for ( int i = 0; i < this->_size / 2; i++ )
    {
        temp = *( this->_container + i );
        *( this->_container + i ) = *( this->_container + ( this->_size - i - 1 ) );
        *( this->_container + ( this->_size - i - 1 ) ) = temp;
    }
} // End reverse method

/* Operators */

// Scalar addition operator
template<typename T>
Tensor<T> Tensor<T>::operator+( const T rhs )
{
    Tensor<T> tmp( this->_shape );

    for ( int i = 0; i < tmp._size; i++ )
    {
        *( tmp._container + i ) = *( this->_container + i ) + rhs;
    }
    return tmp;
} // End scalar addition operator

// Tensor addition operator
template<typename T>
Tensor<T> Tensor<T>::operator+( const Tensor<T>& rhs )
{
    assert ( this->_shape == rhs.shape() );

    Tensor<T> tmp( this->_shape );

    for ( int i = 0; i < this->_size; i++ )
    {
        *(tmp._container + i) = *(this->_container + i) + *(rhs._container + i);
    }
    return tmp;
} // End tensor addition operator

// Scalar addition assignment operator
template<typename T>
void Tensor<T>::operator+=( const T rhs )
{
    for ( int i = 0; i < this->_size; i++ )
    {
        *(this->_container + i) += rhs;
    }
} // end addition assignment operator

// Tensor addition assignment operator
template<typename T>
void Tensor<T>::operator+=( const Tensor<T>& rhs )
{
    assert ( this->_shape == rhs.shape() );

    for ( int i = 0; i < this->_size; i++ )
    {
        *(this->_container + i) += *(rhs._container + i);
    }
}


// Scalar subtraction operator
template<typename T>
Tensor<T> Tensor<T>::operator-( const T rhs )
{
    Tensor<T> tmp( this->_shape );

    for ( int i = 0; i < tmp._size; i++ )
    {
        *( tmp._container + i ) = *( this->_container + i ) - rhs;
    }
    return tmp;
} // End scalar subtraction operator

// Matrix subtraction operator
template<typename T>
Tensor<T> Tensor<T>::operator-( const Tensor<T>& rhs )
{
    assert ( this->_shape == rhs.shape() );

    Tensor<T> tmp( this->_shape );

    for ( int i = 0; i < this->_size; i++ )
    {
        *(tmp._container + i) = *(this->_container + i) - *(rhs._container + i);
    }
    return tmp;
} // End matrix subtraction operator

// Scalar subtraction assignment operator
template<typename T>
void Tensor<T>::operator-=( const T rhs )
{
    for ( int i = 0; i < this->_size; i++ )
    {
        *(this->_container + i) -= rhs;
    }
} // end subtraction assignment operator

// Tensor subtraction assignment operator
template<typename T>
void Tensor<T>::operator-=( const Tensor<T>& rhs )
{
    assert ( this->_shape == rhs.shape() );

    for ( int i = 0; i < this->_size; i++ )
    {
        *(this->_container + i) -= *(rhs._container + i);
    }
} // end subtraction assignment operator

// Scalar multiplication operator
template<typename T>
Tensor<T> Tensor<T>::operator*( const T rhs )
{
    Tensor<T> tmp( this->_shape );

    for ( int i = 0; i < this->_size; i++ )
    {
        *(tmp._container + i) = *(this->_container + i) * rhs;
    }
    return tmp;
} // End scalar multiplication operator

// dot product
// must be equal size rank 1 tensors (vectors) of same type
template<typename T>
T Tensor<T>::dot(Tensor<T>& rhs)
{
    assert(this->_size == rhs._size);
    assert(this->_rank == 1 && rhs._rank == 1);
    T dotProd = 0;

    for ( int i = 0; i < rhs._size; i++ )
    {
        dotProd += *(this->_container + i) * *(rhs._container + i);
    }
    return dotProd;
}

// Fill assignment operator
// Accepts T variable and fills Tensor with that value.
template<typename T>
void Tensor<T>::operator=( T other )
{
    std::fill(this->_container, this->_container + this->_size, other);

} // End fill assignment operator

// Copy assignment operator
template<typename T>
Tensor<T>& Tensor<T>::operator=( const Tensor<T>& other )
{
    if ( this != &other )
    {
        delete[] this->_container;

        this->_size = other._size;
        this->_rank = other._rank;
        this->_shape = other._shape;

        this->_container = new T[this->_size];
        for ( int i = 0; i < this->_size; i++ )
        {
            *( this->_container + i ) = *( other._container + i );
        }
    }
} // End copy assignment operator

// Move assignment operator
template<typename T>
Tensor<T>& Tensor<T>::operator=( Tensor<T>&& other ) noexcept
{
    if ( this != &other )
    {
        delete[] this->_container;

        this->_size = other._size;
        this->_rank = other._rank;
        this->_shape = other._shape;
        this->_container = other._container;

        other._size = 0;
        other._rank = 0;
        other._shape.clear();
        other._container = nullptr;
    }
    return *this;
} // End move assignment operator

// Array index operator
template<typename T>
T& Tensor<T>::operator[]( int index ) const
{
    assert( index < this->_size );
    if ( index >= 0 )
    {
        return *( this->_container + index );
    }
    else
    {
        int neg_index = this->_size - ( index - ( 2 * index ) );
        assert( neg_index < this->_size );
        return *( this->_container + neg_index );
    }
} // End array index operator

// get-index operator
// retrieves relative 1-D index from N-D coordinates
template<typename T>
T& Tensor<T>::operator()( std::vector<unsigned int> index ) const
{
    return *( this->_container + this->index( index ) );
} // end get-index operator

// ostream insertion operator
template<typename T1>
std::ostream& operator<<( std::ostream& out, const Tensor<T1>& arr )
{
    int sz = arr.size();
    if ( sz == 0 )
    {
        out << "empty array";
    }
    else
    {
        out << "[" << std::to_string(arr[0]);
        for ( int i = 1; i < sz; i++ )
        {
            out << ", " << std::to_string( arr[i] );
        }
        out << "]";
    }
    return out;
} // end ostream insertion operator

#endif
