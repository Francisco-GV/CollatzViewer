#include <iostream>
#include "gui.h"
#include "algorithm.h"

int main(int argc, char* argv[])
{
    if (argc <= 1 || !isInt(argv[1]))
    {
        std::cout << "Enter a positive integer.\n";
        return 1;
    }

    int n = atoi(argv[1]);

    std::vector<int> numbers = collatz(n);
    int greaterValue = getGreaterNumber(numbers);

    std::cout << "Number: " << n << "\n";
    std::cout << "Result: ";
    
    // Print vector
    for (int& n : numbers)
    {
        std::cout << n;
        if (n != 1) std::cout << ", ";
    }
    std::cout << "\n";

    std::cout << "Greater Value: " << greaterValue << "\n";

    showGraph(numbers, greaterValue);

    return 0;
}