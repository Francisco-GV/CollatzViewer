#include "gui.h"
#include "algorithm.h"
#include <iostream> //Just debug
#include <algorithm>

unsigned int width;
unsigned int height;

int graphWidth;
int graphHeight;

sf::Color graphLinesColor(255, 100, 100);
sf::Color graphPointsColor(100, 255, 100);
float graphPadding = 50.f;

std::vector<int> data;
int greaterValue;
std::vector<std::array<sf::Vertex, 2>> dataLines;


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
            graphWidth = width - (graphPadding * 2);

            // TODO: Improve resizing lines without recalculating everything
            dataLines = calculateLines();

            window.setView(sf::View(sf::FloatRect(0, 0, width, height)));
        }
    }
}

void draw(sf::RenderWindow& window)
{
    window.clear();

    // Draw lines
    for (std::array<sf::Vertex, 2> line : dataLines)
    {
        window.draw(line.data(), 2, sf::Lines);
    }

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

    float resultX = index * graphWidth / (data.size() - 1);
    xPoint = resultX + graphPadding;

    float resultY = (num - 1) * graphHeight / (greaterValue - 1);
    yPoint = height - graphPadding - resultY;

    return sf::Vector2f(xPoint, yPoint);
}

std::vector<std::array<sf::Vertex, 2>> calculateLines()
{
    std::vector<std::array<sf::Vertex, 2>> lines;

    sf::Vector2f lastPoint = calculatePoint(data[0], 0);
    for (int i = 1; i < data.size(); i++)
    {
        sf::Vector2f currentPoint = calculatePoint(data[i], i);

        std::array<sf::Vertex, 2> stdArray {
            sf::Vertex(lastPoint, graphPointsColor),
            sf::Vertex(currentPoint, graphPointsColor)
        };

        lines.push_back(stdArray);

        lastPoint = sf::Vector2f(currentPoint);
    }

    return lines;
}

void showGraph(std::vector<int>& vectorData, int greaterNumber)
{
    data = vectorData;
    greaterValue = greaterNumber;

    sf::RenderWindow window(sf::VideoMode(750, 500), "CollatzViewer");

    sf::Vector2u size = window.getSize();
    width = size.x;
    height = size.y;
    
    graphHeight = height - (graphPadding * 2);
    graphWidth = width - (graphPadding * 2);

    dataLines = calculateLines();

    while(window.isOpen())
    {
        manageEvents(window);
        draw(window);
    }
}