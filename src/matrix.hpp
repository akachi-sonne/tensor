#include<array>

class Matrix {

    int x_size;
    int y_size;

public:
    // Constructors and destructor
    Matrix(int new_x = 0, int new_y = 0, int new_z = 0);
    ~Matrix();

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

};
