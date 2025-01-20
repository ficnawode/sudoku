#include <iostream>
#include "dummy/dummy.hpp"

int main()
{
    const int a = 5;
    const int b = 3;
    std::cout << "HELLO, WORLD! 5+3 = " << dummy::add(a, b) << std::endl;
    return 0;
}