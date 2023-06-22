#include "gui.h"

void createAndDisplayWindow()
{
    sf::RenderWindow window(sf::VideoMode(750, 500), "CollatzViewer");

    sf::Vector2u size = window.getSize();
    unsigned int width = size.x;
    unsigned int height = size.y;

    sf::Color graphLinesColor(255, 100, 100);
    float graphPadding = 50.f;

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

        // Draw graph
        sf::Vertex graphLine1[] 
        {
            sf::Vertex(sf::Vector2f(graphPadding, graphPadding), graphLinesColor),
            sf::Vertex(sf::Vector2f(graphPadding, height - graphPadding), graphLinesColor)
        };

        sf::Vertex graphLine2[]
        {
            sf::Vertex(sf::Vector2f(graphPadding, height - graphPadding), graphLinesColor),
            sf::Vertex(sf::Vector2f(width - graphPadding, height - graphPadding), graphLinesColor)
        };

        window.draw(graphLine1, 2, sf::Lines);
        window.draw(graphLine2, 2, sf::Lines); 

        window.display();
    }
}