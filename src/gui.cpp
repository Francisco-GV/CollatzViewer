#include "gui.h"
#include "algorithm.h"

unsigned int width;
unsigned int height;

int graphWidth;
int graphHeight;

sf::Color graphLinesColor(255, 100, 100);
float graphPadding = 50.f;

std::vector<int> data;
int greaterValue;

void manageEvents(sf::RenderWindow& window)
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

            graphHeight = height - (graphPadding * 2);
            graphHeight = width - (graphPadding * 2);

            window.setView(sf::View(sf::FloatRect(0, 0, width, height)));
        }
    }
}

void draw(sf::RenderWindow& window)
{
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

sf::Vector2f calculatePoint(int num, int index)
{
    float yPoint;
    float xPoint;

    float resultY = num * graphHeight / greaterValue;
    yPoint = height - graphPadding - resultY;

    float resultX = index * graphWidth / data.size();
    xPoint = resultX + graphPadding;


    return sf::Vector2f(xPoint, yPoint);
}

void showGraph(std::vector<int>& vectorData)
{
    data = vectorData;
    greaterValue = getGreaterNumber(data);

    sf::RenderWindow window(sf::VideoMode(750, 500), "CollatzViewer");

    sf::Vector2u size = window.getSize();
    width = size.x;
    height = size.y;

    while(window.isOpen())
    {
        manageEvents(window);
        draw(window);
    }
}