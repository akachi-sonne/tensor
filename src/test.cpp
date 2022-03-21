#include<iostream>
#include "array.hpp"

int main()
{
    Array<int> a(10);
    a.print_flat();
    a << 1;
    a.print();
    Array<int> b({3,2,2});
    b.print_flat();
    b.print();
    Array<int> c({3,3,3});
    c << 1;
    c.print();
    Array<int> d({2,2,2,2,2});
    d.print();

    std::cout << "coordinate {0,0,0} (should be 0): " << b.where({0,0,0}) << std::endl;
    std::cout << "coordinate {0,0,1} (should be 1): " << b.where({0,0,1}) << std::endl;
    std::cout << "coordinate {0,1,0} (should be 2): " << b.where({0,1,0}) << std::endl;
    std::cout << "coordinate {0,1,1} (should be 3): " << b.where({0,1,1}) << std::endl;
    std::cout << "coordinate {2,0,0} (should be 8): " << b.where({2,0,0}) << std::endl;
    return 0;
}
