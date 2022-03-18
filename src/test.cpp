#include<iostream>
#include "array.hpp"

int main()
{
    Array<int> a(10);
    a.print();
    a << 0;
    a.print();
    a << 1;
    a.print();
    return 0;
}
