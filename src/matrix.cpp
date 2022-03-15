#include<iostream>
#include"matrix.hpp"

// Constructors and destructor
template <typename T, size_t N>
Matrix::Matrix(int dim = 1, int fill = 0)
{
    switch fill {
        case 0:
            // zeros
            break;
        case 1:
            // ones
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

Matrix::~Matrix()
{

}
/* future
// General methods
void Matrix::print() 
{

}

std::array Matrix::size() 
{

}

Matrix Matrix::resize() 
{

}

// Operations
// All Math operation return a new matrix
Matrix Matrix::add(Matrix const &b) 
{

}
Matrix operator + (Matrix const &b) 
{

}

Matrix Matrix::subtr(Matrix const &b) 
{

}
Matrix operator - (Matrix const &b) 
{

}

// matrix multiplication
Matrix Matrix::mult(Matrix const &b) 
{

}
Matrix operator * (Matrix const &b) 
{

}

// scalar multiplication
Matrix Matrix::mult(int &b) 
{

}
Matrix operator * (int &b) 
{

}

// dot product
Matrix Matrix::dot(Matrix const &b) 
{

}
// dot product
Matrix operator @ (Matrix const &b) 
{

}

// Transpose
Matrix Matrix::T() 
{

}
// Transpose
Matrix operator ' () 
{

}
*/

// Helper methods
bool Matrix::dim_size_validity(int &dim, int &size, std::vector<int> &shape)
{
    
}
