#include "graph.h"
#include "algorithm.h"
#include <iostream> //Just debug
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cmath>

unsigned int width;
unsigned int height;

int graphMaxVertical;
int graphMaxHorizontal;
float graphWidth;
float graphHeight;

sf::Font font;
sf::Color graphLinesColor(255, 100, 100);
sf::Color graphPointsColor(100, 255, 100);
float fontLimitSize = 14;
float fontGuideSize = 10;
float graphPadding = 50.f;
float guideLineLength = 4.f;
float guideVerticalSpacingMin = 80.f;
float guideHorizontalSpacingMin = 40.f;

int numVerticalGuides;
int numHorizontalGuides;

// TODO: Use types with more bytes
std::vector<int> data;
std::vector<float> verticalDataGuides;
std::vector<float> horizontalDataGuides;
int greaterValue;

std::vector<std::array<sf::Vertex, 2>> dataLines;
std::vector<float> verticalVisualGuides;
std::vector<float> horizontalVisualGuides;


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

            calculateGuides();

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
    text.setString(std::to_string(graphMaxHorizontal));
    textSize = text.getLocalBounds().getSize();
    textX = width - graphPadding - textSize.x / 2;
    textY = height - graphPadding + textPadding / 2;
    text.setPosition(sf::Vector2f(textX, textY));
    window.draw(text);

    // Draw vertical Guides

    for (int i = 0; i < verticalVisualGuides.size(); i++)
    {
        float guide = verticalVisualGuides[i];

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
        textX = startX - textSize.x - guideLineLength - 7;
        textY = startY - textSize.y;

        text.setPosition(sf::Vector2f(textX, textY));
        window.draw(text);
        
    }

    // Draw horizontal Guides

    for (int i = 0; i < horizontalVisualGuides.size(); i++)
    {
        float guide = horizontalVisualGuides[i];

        float startX = guide;
        float startY = height - graphPadding;

        sf::Vertex line[]
        {
            sf::Vertex(sf::Vector2f(startX, startY), sf::Color::White),
            sf::Vertex(sf::Vector2f(guide, height - graphPadding + guideLineLength), sf::Color::White)
        };

        window.draw(line, 2, sf::Lines);

        text.setCharacterSize(fontGuideSize);

        std::ostringstream oss;
        oss.precision(0);
        oss << std::fixed << horizontalDataGuides[i];
        text.setString(oss.str());

        textSize = text.getLocalBounds().getSize();
        textX = startX - textSize.x;
        textY = startY + textSize.y + guideLineLength;

        text.setPosition(sf::Vector2f(textX, textY));
        window.draw(text);
        
    }

    window.display();
}

sf::Vector2f calculatePoint(int num, int index)
{
    float yPoint;
    float xPoint;

    xPoint = calculateXPoint(index);
    yPoint = calculateYPoint(num, true);

    return sf::Vector2f(xPoint, yPoint);
}

float calculateYPoint(float num, bool substractOne)
{
    int sub = 0;
    if (substractOne) sub = 1;

    float resultY = (num - sub) * graphHeight / (graphMaxVertical - sub);
    float yPoint = height - graphPadding - resultY;

    return yPoint;
}

float calculateXPoint(float num)
{
    float resultX = num * graphWidth / graphMaxHorizontal;
    float xPoint = resultX + graphPadding;

    return xPoint;
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

void calculateGuides()
{
    calculateGuides(verticalDataGuides, verticalVisualGuides, numVerticalGuides, 
        graphHeight, graphMaxVertical, guideVerticalSpacingMin, [](float n){return calculateYPoint(n, false);});

    calculateGuides(horizontalDataGuides, horizontalVisualGuides, numHorizontalGuides,
        graphWidth, graphMaxHorizontal, guideHorizontalSpacingMin, calculateXPoint);
}

void calculateGuides(std::vector<float>& dataGuides, std::vector<float>& visualGuides, int& currentNumGuides, 
    float graphMeasure, float maxValue, float spacingMin, float (*calculateAxis)(float))
{
    visualGuides.clear();
    int numGuides = std::floor(std::abs(graphMeasure) / spacingMin) - 1;

    if (numGuides > maxValue)
    {
        numGuides = maxValue;
    }

    if (currentNumGuides == numGuides)  
    {
        for (int i = 0; i < numGuides; i++)
        {
            visualGuides.push_back(calculateAxis(dataGuides[i]));
        }
        return;
    }
    currentNumGuides = numGuides;

    dataGuides.clear();

    float spacing = maxValue / (numGuides + 1);

    for (int i = 0; i < numGuides; i++)
    {
        float num = spacing * (i + 1);
        dataGuides.push_back(num);
        visualGuides.push_back(calculateAxis(num));
    }
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
    graphMaxHorizontal = data.size() - 1;

    graphHeight = height - (graphPadding * 2);
    graphWidth = width - (graphPadding * 2);

    dataLines = calculateLines();

    calculateGuides();

    while(window.isOpen())
    {
        manageEvents(window);
        draw(window);
    }
}