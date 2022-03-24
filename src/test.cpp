#include<iostream>
#include "array.hpp"

int main()
{
    Array<int> a(10);
    a.print_flat();
    a = 1;
    a[3] = 5;
    a[9] = 13;
    std::cout << "should be 13: " << a[-1] << std::endl;
    a.print();
    std::cout << a[0] << "\n" << std::endl;
    Array<int> b({3,2,2});
    b.print_flat();
    b.print();
    Array<int> c({3,3,3});
    c = 1;
    c.print();
    Array<int> d({2,2,2,2,2});
    d.print(1);


    std::cout << "coordinate {0,0,0} (should be 0): " << b.get_index({0,0,0}) << std::endl;
    std::cout << "coordinate {0,0,1} (should be 1): " << b.get_index({0,0,1}) << std::endl;
    std::cout << "coordinate {0,1,0} (should be 2): " << b.get_index({0,1,0}) << std::endl;
    std::cout << "coordinate {0,1,1} (should be 3): " << b.get_index({0,1,1}) << std::endl;
    std::cout << "coordinate {2,0,0} (should be 8): " << b.get_index({2,0,0}) << std::endl;
    std::cout << std::endl;
    std::cout << "c.get_size(): " << c.get_size() << std::endl;
    std::cout << "c.get_dims(): " << c.get_dims() << std::endl;
    std::cout << "c.get_shape(): " << c.get_shape() << std::endl;

    return 0;
}
