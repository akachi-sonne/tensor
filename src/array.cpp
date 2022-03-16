#include<iostream>
#include"array.hpp"

// Constructors and destructor
template <typename T, size_t N>
Array::Array(int dim = 1, int fill = 0, std::vector<int> shape = N)
{
    this->size = N;
    this->dim = dim;
    switch fill {
        case 0:
            // zeros
            for(int i = 0; i < this->size; i++)
            {
                this->container[i] = 0;
            }
            break;
        case 1:
            // ones
            for(int i = 0; i < this->size; i++)
            {
                this->container[i] = 1;
            }
            break;
        case 2:
            // rand
            break;
        case 3:
            // manual - requires input
            break;
        case 4:
            // object - requires input
            break;
        default:
            // invalid input
            try {
                throw fill;
            }
            catch {
                std::cout << "Invalid input on constructor - fill: " << fill << "\n";
                std::cout << "\'fill\' parameter must be int from 0-4\n";
                std::cout << "0: zeros\n1: ones\n2: rand\n3: manual(requires input)\n4: obj(requires input)\n;
                break;
            }
    }

}

Array::~Array()
{

}
/* future
// General methods
void Array::print() 
{

}

std::array Array::size() 
{

}

Array Array::resize() 
{

}

// Operations
// All Math operation return a new matrix
Array Array::add(Array const &b) 
{

}
Array operator + (Array const &b) 
{

}

Array Array::subtr(Array const &b) 
{

}
Array operator - (Array const &b) 
{

}

// matrix multiplication
Array Array::mult(Array const &b) 
{

}
Array operator * (Array const &b) 
{

}

// scalar multiplication
Array Array::mult(int &b) 
{

}
Array operator * (int &b) 
{

}

// dot product
Array Array::dot(Array const &b) 
{

}
// dot product
Array operator @ (Array const &b) 
{

}

// Transpose
Array Array::T() 
{

}
// Transpose
Array operator ' () 
{

}
*/

// Helper methods
bool Array::dim_size_validity(int &dim, int &size, std::vector<int> &shape)
{
    
}
