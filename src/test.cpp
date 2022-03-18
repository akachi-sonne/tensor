#include<iostream>
#include "array.hpp"

int main()
{
    Array<int> a(10);
    a.print();
    a << 1;
    a.print();
    Array<int> b({2,2,3});
    b.print();
    return 0;
}
