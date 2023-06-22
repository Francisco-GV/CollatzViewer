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

int getGreaterNumber(std::vector<int> v)
{
    int greater = v[0];

    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] > greater)
        {
            greater = v[i];
        } 
    }

    return greater;
}