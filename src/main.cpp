#include <iostream>
#include "gui.h"
#include "algorithm.h"

int main()
{
    std::vector<int> numbers = collatz(115);

    showGraph(numbers);

    return 0;
}