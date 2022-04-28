#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Settings.h"

class Cell
{
private:
    sf::RectangleShape shape;
public:
    void draw(sf::RenderWindow* w);
    void setFillColor(sf::Color c);
    sf::Vector2f getPosition();
    void setPosition(uint32_t x, uint32_t y);
    Cell(uint16_t x = 0, uint16_t y = 0);
};