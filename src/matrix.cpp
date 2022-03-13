#include"matrix.hpp"

// Constructors and destructor
Matrix::Matrix() {

}

Matrix::Matrix(int new_x = 0, int new_y = 0, int new_z = 0) {

}

Matrix::~Matrix() {

}

// General methods
void Matrix::print() {

}

std::array Matrix::size() {

}

Matrix Matrix::resize() {

}

// Operations
// All Math operation return a new matrix
Matrix Matrix::add(Matrix const &b) {

}
Matrix operator + (Matrix const &b) {

}

Matrix Matrix::subtr(Matrix const &b) {

}
Matrix operator - (Matrix const &b) {

}

// matrix multiplication
Matrix Matrix::mult(Matrix const &b) { 

}
Matrix operator * (Matrix const &b) {

}

// scalar multiplication
Matrix Matrix::mult(int &b) {

}
Matrix operator * (int &b) {

}

// dot product
Matrix Matrix::dot(Matrix const &b) {

}
// dot product
Matrix operator @ (Matrix const &b) {

}

// Transpose
Matrix Matrix::T() {

}
// Transpose
Matrix operator ' () {

}

