#include "SFML/Graphics.hpp"
#include <vector>
#include <array>

void showGraph(std::vector<int>& vectorData, int greaterNumber);
void manageEvents(sf::RenderWindow& window);
void draw(sf::RenderWindow& window);
sf::Vector2f calculatePoint(int num, int index);
// TODO: Rename to more appropriate function names
float calculateYPoint(float num, bool substractOne);
float calculateXPoint(float num);
std::vector<std::array<sf::Vertex, 2>> calculateLines();
void calculateGuides();
void calculateGuides(std::vector<float>& dataGuides, std::vector<float>& visualGuides, int& currentNumGuides, 
    float graphMeasure, float maxValue, float spacingMin, float (*calculateAxis)(float));