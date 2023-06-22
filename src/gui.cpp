#include "gui.h"

void createAndDisplayWindow()
{
    sf::RenderWindow window(sf::VideoMode(750, 500), "CollatzViewer");

    sf::Vector2u size = window.getSize();
    unsigned int width = size.x;
    unsigned int height = size.y;

    while(window.isOpen())
    {
        sf::Event event;

        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::Resized)
            {
                width = event.size.width;
                height = event.size.height;
                window.setView(sf::View(sf::FloatRect(0, 0, width, height)));
            }
        }

        window.clear();

        sf::Vertex line[] 
        {
            sf::Vertex(sf::Vector2f(10.f, 10.f)),
            sf::Vertex(sf::Vector2f(150.5, 150.f))
        };

        window.draw(line, 2, sf::Lines);

        window.display();
    }
}