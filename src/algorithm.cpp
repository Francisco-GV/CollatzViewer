#include "algorithm.h"

std::vector<int> collatz(int n)
{
    std::vector<int> numbers;

    numbers.push_back(n);

    while (n != 1)
    {
        if (n % 2 == 0)
        {
            n /= 2;
        }
        else
        {
            n = (n * 3) + 1;
        }

        numbers.push_back(n);
    }

    return numbers;
}