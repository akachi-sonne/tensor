#include<iostream>
#include<stdlib.h>
#include<time.h>
#include "tensor.hpp"

int main()
{
    srand (time(NULL));

    Tensor<int> a(10);
    a.print_flat();
    a = 1;
    a[3] = 5;
    a[9] = 13;
    std::cout << "should be 13: " << a[-1] << std::endl;
    a.print();
    std::cout << "using ostream: " << a << std::endl;
    std::cout << a[0] << "\n" << std::endl;
    Tensor<int> b({3,2});
    b.print_flat();
    b.print();
    Tensor<int> c({3,2,5});
    c = 1;
    c.print();
    Tensor<int> d({2,2,2,2,2});
    d.print(1);
    d({0,0,0,1,0}) = 5;
    d.print();

    Tensor<int> e(25);
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
    std::cout << "e.mean(): " << e.mean() << std::endl;
    std::cout << "e median: " << e.median() << std::endl;
    std::cout << "e mode: ";
    std::vector mode = e.mode();
    for (int i = 0; i < mode.size(); i++)
    {
        std::cout << mode[i];
        if (i < mode.size() - 1)
        {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;

    e.reverse();
    std::cout << "e reversed: ";
    e.print();
    std::cout << std::endl;

    std::cout << "e.max(): " << e.max() << std::endl;
    std::cout << "e.min(): " << e.min() << std::endl;
    std::cout << "e.sum(): " << e.sum() << std::endl;

    Tensor<int> f(25);
    for (int i = 0; i < f.get_size(); i++)
    {
        f[i] = rand() % 100;
    }
    std::cout << "Tensor f: ";
    f.print();
    std::cout << std::endl;

    f.sort(true);
    std::cout << "Tensor f after f.sort(reverse=true): ";
    f.print();
    std::cout << std::endl;

    Tensor<int> h = f;
    std::cout << "h copied from f: ";
    h.print();
    std::cout << std::endl;
    std::cout << "h.get_size: " << h.get_size() << std::endl;
    std::cout << "h.get_rank: " << h.get_rank() << std::endl;
    std::cout << "h.get_shape: " << h.get_shape() << std::endl;
    std::cout << "f.get_size: " << f.get_size() << std::endl;
    std::cout << "f.get_rank: " << f.get_rank() << std::endl;
    std::cout << "f.get_shape: " << f.get_shape() << std::endl;

    std::cout << "\nprinting using iterators:" << std::endl;
    for (auto i : f)
        std::cout << i << " ";
    std::cout << std::endl;

    std::cout << "coordinate {0,0,0} (should be 0): " << b.get_index({0,0,0}) << std::endl;
    std::cout << "coordinate {0,0,1} (should be 1): " << b.get_index({0,0,1}) << std::endl;
    std::cout << "coordinate {0,1,0} (should be 2): " << b.get_index({0,1,0}) << std::endl;
    std::cout << "coordinate {0,1,1} (should be 3): " << b.get_index({0,1,1}) << std::endl;
    std::cout << "coordinate {2,0,0} (should be 8): " << b.get_index({2,0,0}) << std::endl;
    std::cout << std::endl;
    std::cout << "c.get_size(): " << c.get_size() << std::endl;
    std::cout << "c.get_rank(): " << c.get_rank() << std::endl;
    std::cout << "c.get_shape(): " << c.get_shape() << std::endl;

    return 0;
}
