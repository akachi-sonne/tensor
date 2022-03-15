#include<array>

/* 
*/

template<typename T, size_t N>
class Matrix {

    int dim; // Number of dimensions
    int size; // total number of elements
    std::vector<int> shape; // shape: length of each dimension.
    template <typename T, size_t N>
    T container [N]; // linear array containing elements

public:
    // Constructors and destructor
    template <typename T, size_t N>
    Matrix(int dim, int fill);
    ~Matrix();
/*
    // General methods
    void print();
    std::array size();
    Matrix resize();

    // Operations
    // All Math operation return a new matrix
    Matrix add(Matrix const &b);
    Matrix operator + (Matrix const &b);
    Matrix subtr(Matrix const &b);
    Matrix operator - (Matrix const &b);
    Matrix mult(Matrix const &b); // matrix multiplication
    Matrix operator * (Matrix const &b);
    Matrix mult(int &b); // scalar multiplication
    Matrix operator * (int &b); 
    Matrix dot(Matrix const &b); // dot product
    Matrix operator @ (Matrix const &b);
    Matrix T(); // Transpose
    Matrix operator ' (); // Transpose
*/
private:
    bool dim_size_validity(int &dim, int &size);
};
#include"matrix.cpp"
