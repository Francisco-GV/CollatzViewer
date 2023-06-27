#include "graph.h"
#include "algorithm.h"
#include <iostream> //Just debug
#include <sstream>
#include <iomanip>
#include <algorithm>

unsigned int width;
unsigned int height;

int graphMaxVertical;
float graphWidth;
float graphHeight;

sf::Font font;
sf::Color graphLinesColor(255, 100, 100);
sf::Color graphPointsColor(100, 255, 100);
float fontLimitSize = 14;
float fontGuideSize = 10;
float graphPadding = 50.f;
float guideLineLength = 4.f;

// TODO: Replace with variable
#define NUM_VERTICAL_GUIDES 4

// TODO: Use types with more bytes
std::vector<int> data;
std::array<float, NUM_VERTICAL_GUIDES> verticalDataGuides;
int greaterValue;

std::vector<std::array<sf::Vertex, 2>> dataLines;
std::array<float, NUM_VERTICAL_GUIDES> verticalGuides;


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

            for (int i = 0; i < verticalDataGuides.size(); i++)
            {
                verticalGuides[i] = calculateYPoint(verticalDataGuides[i], false);
            }

            // TODO: Improve resizing lines without recalculating everything
            dataLines = calculateLines();

            window.setView(sf::View(sf::FloatRect(0, 0, width, height)));
        }
    }
}

void draw(sf::RenderWindow& window)
{
    window.clear();

    // Draw graph
    sf::Vertex graphVerticalLine[] 
    {
        sf::Vertex(sf::Vector2f(graphPadding, height - graphPadding), graphLinesColor),
        sf::Vertex(sf::Vector2f(graphPadding, graphPadding), graphLinesColor)
    };

    sf::Vertex graphHorizontalLine[]
    {
        sf::Vertex(sf::Vector2f(graphPadding, height - graphPadding), graphLinesColor),
        sf::Vertex(sf::Vector2f(width - graphPadding, height - graphPadding), graphLinesColor)
    };

    window.draw(graphVerticalLine, 2, sf::Lines);
    window.draw(graphHorizontalLine, 2, sf::Lines);

    // Draw lines
    for (std::array<sf::Vertex, 2> line : dataLines)
    {
        window.draw(line.data(), 2, sf::Lines);
    }

    // Draw text
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(fontLimitSize);
    text.setFillColor(sf::Color::White);

    sf::Vector2f textSize;
    float textX;
    float textY;

    int textPadding = 8;

    // Top
    std::string topValueText;
    if (digits(graphMaxVertical) > 7)
    {
        std::ostringstream oss;
        oss.precision(1);
        oss << std::scientific << static_cast<float>(graphMaxVertical);
        topValueText = oss.str();
    } else {
        topValueText = std::to_string(graphMaxVertical);
    }

    text.setString(topValueText);
    textSize = text.getLocalBounds().getSize();
    textX = graphPadding - textSize.x - textPadding;
    textY = graphPadding - textSize.y;

    if (textX < 0)
    {
        float scaleFactor = graphPadding / (textSize.x + (textPadding * 2));
        text.setScale(scaleFactor, scaleFactor);

        textSize = text.getGlobalBounds().getSize();
        textX = graphPadding - textSize.x - textPadding;
        textY = graphPadding;
    }

    text.setPosition(sf::Vector2f(textX, textY));
    window.draw(text);

    // Bottom
    text.setScale(1.f, 1.f);
    text.setString("1");
    textSize = text.getLocalBounds().getSize();
    textX = graphPadding - textSize.x - textPadding;
    textY = height - graphPadding - textSize.y;
    text.setPosition(sf::Vector2f(textX, textY));
    window.draw(text);

    // Left
    text.setString("0");
    textSize = text.getLocalBounds().getSize();
    textX = graphPadding - textSize.x / 2;
    textY = height - graphPadding + textPadding / 2;
    text.setPosition(sf::Vector2f(textX, textY));
    window.draw(text);

    // Right
    text.setString(std::to_string(data.size()));
    textSize = text.getLocalBounds().getSize();
    textX = width - graphPadding - textSize.x / 2;
    textY = height - graphPadding + textPadding / 2;
    text.setPosition(sf::Vector2f(textX, textY));
    window.draw(text);

    // Draw Guides

    for (int i = 0; i < verticalGuides.size(); i++)
    {
        float guide = verticalGuides[i];

        float startX = graphPadding;
        float startY = guide;

        sf::Vertex line[]
        {
            sf::Vertex(sf::Vector2f(startX, startY), sf::Color::White),
            sf::Vertex(sf::Vector2f(graphPadding - guideLineLength, guide), sf::Color::White)
        };

        window.draw(line, 2, sf::Lines);

        text.setCharacterSize(fontGuideSize);

        std::ostringstream oss;
        oss.precision(0);
        oss << std::fixed << verticalDataGuides[i];
        text.setString(oss.str());

        textSize = text.getLocalBounds().getSize();
        textX = startX - textSize.x - guideLineLength - 3;
        textY = startY - textSize.y;

        text.setPosition(sf::Vector2f(textX, textY));
        window.draw(text);
        
    }

    window.display();
}

sf::Vector2f calculatePoint(int num, int index)
{
    float yPoint;
    float xPoint;

    float resultX = index * graphWidth / (data.size() - 1);
    xPoint = resultX + graphPadding;

    yPoint = calculateYPoint(num, true);

    return sf::Vector2f(xPoint, yPoint);
}

float calculateYPoint(int num, bool substractOne)
{
    int sub = 0;
    if (substractOne) sub = 1;

    float resultY = (num - sub) * graphHeight / (graphMaxVertical - sub);
    float yPoint = height - graphPadding - resultY;

    return yPoint;
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

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(750, 500), "CollatzViewer", sf::Style::Default, settings);

    font.loadFromFile("resources/font.ttf");

    sf::Vector2u size = window.getSize();
    width = size.x;
    height = size.y;

    graphMaxVertical = roundUp(greaterNumber, 50);

    graphHeight = height - (graphPadding * 2);
    graphWidth = width - (graphPadding * 2);

    dataLines = calculateLines();

    float sep = graphMaxVertical / (verticalDataGuides.size() + 1.0);
    for (int i = 0; i < verticalDataGuides.size(); i++)
    {
        float num = sep * (i + 1);
        verticalDataGuides[i] = num;
        verticalGuides[i] = calculateYPoint(num, false);
    }

    while(window.isOpen())
    {
        manageEvents(window);
        draw(window);
    }
}