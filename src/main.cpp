#include <iostream>
#include "algorithm.h"

int main()
{
    std::vector<int> numbers = collatz(19);

    for (int& n : numbers)
    {
        std::cout << n;
        if (n != 1) std::cout << " - ";
    }

    return 0;
}