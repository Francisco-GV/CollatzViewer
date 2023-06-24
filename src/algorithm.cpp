#include "algorithm.h"
#include <algorithm>
#include <cctype>

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

bool isInt(std::string& s)
{
    return !s.empty() 
        && std::find_if(s.begin(), s.end(), [](unsigned char c) {return !std::isdigit(c);}) 
        == s.end();
}

int digits(int n)
{
    int digits = 0;
    while (n) {
        n /= 10;
        digits++;
    }
    return digits;
}