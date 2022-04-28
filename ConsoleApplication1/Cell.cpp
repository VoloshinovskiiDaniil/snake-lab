#include "Cell.hpp"
void Cell::draw(sf::RenderWindow* w)
{
    w->draw(shape);
}
void Cell::setFillColor(sf::Color c)
{
    shape.setFillColor(c);
}
sf::Vector2f Cell::getPosition()
{
    return shape.getPosition();
}
void Cell::setPosition(uint32_t x, uint32_t y)
{
    shape.setPosition(sf::Vector2f(x, y));
}
Cell::Cell(uint16_t x, uint16_t y)
{
    shape.setSize(sf::Vector2f(CELL_X, CELL_Y));
    shape.setPosition(x, y);
}