#include <iostream>
#include "SFML/Graphics.hpp"

void draw(sf::RenderWindow& window)
{
    sf::CircleShape shape(50.0f);
    shape.setFillColor(sf::Color(200, 50, 50));
    window.draw(shape);
}

int main()
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

        draw(window);

        window.display();
    }

    return 0;
}