#include <iostream>
#include "graph.h"
#include "algorithm.h"

int main(int argc, char* argv[])
{   
    std::string inputNumber;
    if (argc <= 1)
    {
        std::cout << "Enter a positive integer: ";
        std::cin >> inputNumber;
    }
    else inputNumber = std::string(argv[1]);
    if (!isInt(inputNumber)) return 1;

    int n = std::stoi(inputNumber);
    if (n == 0) return 1;

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
    std::cout << "Iterations: " << (numbers.size() - 1) << "\n";
    std::cout << "Greater Value: " << greaterValue << "\n";

    showGraph(numbers, greaterValue);

    return 0;
}