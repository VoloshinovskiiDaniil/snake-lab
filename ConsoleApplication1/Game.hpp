#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Cell.hpp"
class Game
{
private:
    sf::Clock clock;
    sf::RenderWindow window;
    sf::RectangleShape rect;

    std::vector<Cell> snake;
    Cell apple;

    // SnakeDirection
    enum class sd {
        UP, DOWN, LEFT, RIGHT
    };

    bool playing = true;
    sd direction = sd::UP;
    uint32_t last_changed = 0;
    int getIndex(std::vector<Cell> v, Cell element);
public:
    void run();
    Game(std::string title);
    ~Game();
};

