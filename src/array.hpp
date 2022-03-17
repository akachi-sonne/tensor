#include<vector>

template<typename T>
class Array {
    template<typename CT, size_t CN>
    class Container {
    public:
        CT container [CN]; // linear array containing elements
        Container();
        ~Container();
        void operator << (CT x);
        void operator = (CT x);
        void print();
    };

    int dim; // Number of dimensions
    int size; // total number of elements
    std::vector<int> shape; // shape: length of each dimension.

public:
    // Constructors and destructor
    Array(std::vector<unsigned int> shape);
    ~Array();
    void print();
    void operator << (T2 x);
    void operator = (T2 x);

};
