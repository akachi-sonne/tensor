#include<iostream>
#include"array.hpp"
#include"array.cpp"

int main() 
{
    Array a<int> ({15});
    a << 0;
    a.print();
    a << 1;
    a.print();
    return 0;
}
