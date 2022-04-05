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

    Tensor<int> a1 = a;
    std::cout << "a1: " << std::endl;
    for (auto val : a1)
        std::cout << val << std::endl;

    Tensor<int> a2;
    a2 = a1 + 7;
    std::cout << "a2 = a1 + 7: " << std::endl;
    for ( auto val : a2 )
        std::cout << val << std::endl;

    a1 = a + a2;
    std::cout << "a1 = a + a2: " << std::endl;
    for ( auto val : a1 )
        std::cout << val << std::endl;

    a1 = a2-3;
    std::cout << "a1 = a2 - 3: " << std::endl;
    for ( auto val : a1 )
        std::cout << val << std::endl;

    a1 = a2 - a;
    std::cout << "a1 = a2 - a: " << std::endl;
    for ( auto val : a1 )
        std::cout << val << std::endl;

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
    for (int i = 0; i < e.size(); i++)
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
    for (int i = 0; i < f.size(); i++)
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
    std::cout << "h.size: " << h.size() << std::endl;
    std::cout << "h.rank: " << h.rank() << std::endl;
    std::cout << "h.shape: " << h.shape() << std::endl;
    std::cout << "f.size: " << f.size() << std::endl;
    std::cout << "f.rank: " << f.rank() << std::endl;
    std::cout << "f.shape: " << f.shape() << std::endl;

    std::cout << "\nprinting using iterators:" << std::endl;
    for (auto i : f)
        std::cout << i << " ";
    std::cout << std::endl;

/*    Tensor<int> z(25);
//    z = h + f;
    std::cout << "z = h + f" << std::endl;
    for (auto i : z)
        std::cout << i << " ";
    std::cout << std::endl;
    z = z + 5;
    std::cout << "z = z + 5" << std::endl;
    for (auto i : z)
        std::cout << i << " ";
    std::cout << std::endl;
*/
    std::cout << "coordinate {0,0,0} (should be 0): " << b.index({0,0,0}) << std::endl;
    std::cout << "coordinate {0,0,1} (should be 1): " << b.index({0,0,1}) << std::endl;
    std::cout << "coordinate {0,1,0} (should be 2): " << b.index({0,1,0}) << std::endl;
    std::cout << "coordinate {0,1,1} (should be 3): " << b.index({0,1,1}) << std::endl;
    std::cout << "coordinate {2,0,0} (should be 8): " << b.index({2,0,0}) << std::endl;
    std::cout << std::endl;
    std::cout << "c.size(): " << c.size() << std::endl;
    std::cout << "c.rank(): " << c.rank() << std::endl;
    std::cout << "c.shape(): " << c.shape() << std::endl;

    return 0;
}
