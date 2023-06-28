#include "SFML/Graphics.hpp"
#include <vector>
#include <array>

void showGraph(std::vector<int>& vectorData, int greaterNumber);
void manageEvents(sf::RenderWindow& window);
void draw(sf::RenderWindow& window);
sf::Vector2f calculatePoint(int num, int index);
float calculateYPoint(int num, bool substractOne);
std::vector<std::array<sf::Vertex, 2>> calculateLines();
void calculateGuides();