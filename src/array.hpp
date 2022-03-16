#include<array>

/* 
*/

template<typename T, size_t N>
class Array {

    int dim; // Number of dimensions
    int size; // total number of elements
    std::vector<int> shape; // shape: length of each dimension.
    T container [N]; // linear array containing elements

public:
    // Constructors and destructor
    Array(int dim, int fill, std::vector<int> shape);
    ~Array();
/*
    // General methods
    void print();
    std::array size();
    Array resize();

    // Operations
    // All Math operation return a new matrix
    Array add(Array const &b);
    Array operator + (Array const &b);
    Array subtr(Array const &b);
    Array operator - (Array const &b);
    Array mult(Array const &b); // matrix multiplication
    Array operator * (Array const &b);
    Array mult(int &b); // scalar multiplication
    Array operator * (int &b); 
    Array dot(Array const &b); // dot product
    Array operator @ (Array const &b);
    Array T(); // Transpose
    Array operator ' (); // Transpose
*/
private:
    bool dim_size_validity(int &dim, int &size);
};
#include"array.cpp"
