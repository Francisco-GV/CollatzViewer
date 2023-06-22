#include <iostream>
#include "SFML/Graphics.hpp"
#include "algorithm.h"

void drawGraphics(sf::RenderWindow& window)
{
    sf::CircleShape shape(50.0f);
    shape.setFillColor(sf::Color(200, 50, 50));
    window.draw(shape);
}

void testWindow()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My Window");

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        drawGraphics(window);

        window.display();
    }
}

void printCollatz(int n)
{
    std::vector<int> numbers = collatz(n);

    for (int& n : numbers)
    {
        std::cout << n;
        if (n != 1) std::cout << " - ";
    }
}