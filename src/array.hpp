#include<iostream>
#include<vector>
#include<stdexcept>

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
    void operator =(T rhs);
    int index(std::vector<unsigned int> coords);
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
int Array<T>::index(std::vector<unsigned int> coords)
{
    if (coords.size() != this->dims)
    {
        throw std::invalid_argument("Invalid input: coordinate vector input must match num dimensions.");
    }
    int index = 0;
    for (int i = 0; i < this->dims; i++)
    {
        for (int j = this->dims -1; j > i; j--)
        {
            index += coords[i] * this->shape[j];
        }
    }
    return index + coords[this->dims - 1];
}
