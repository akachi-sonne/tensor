#include<iostream>
#include<stdlib.h>
#include<time.h>
#include "array.hpp"

int main()
{
    srand (time(NULL));

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
    d({0,0,0,1,0}) = 5;
    d.print();

    Array<int> e(25);
    for (int i = 0; i < e.get_size(); i++)
    {
        e[i] = rand() % 100;
    }
    std::cout << "e with random init: " << std::endl;
    e.print();
    std::cout << "sorted? " << e.is_sorted() << std::endl;
    std::cout << "e after sort(): " << std::endl;
    e.sort();
    e.print();
    std::cout << "sorted? " << e.is_sorted() << std::endl;
    std::cout << "e median: " << e.median() << std::endl;

    std::cout << "e.max(): " << e.max() << std::endl;
    std::cout << "e.min(): " << e.min() << std::endl;
    std::cout << "e.sum(): " << e.sum() << std::endl;
    std::cout << "e.mean(): " << e.mean() << std::endl;

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
