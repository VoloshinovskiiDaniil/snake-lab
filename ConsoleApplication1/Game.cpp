#include "Game.hpp"

int Game::getIndex(std::vector<Cell> v, Cell element)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (v.at(i).getPosition() == element.getPosition())
            return i;
    }
    return -1;
}
void Game::run()
{
    while (window.isOpen() and playing)
    {
        uint64_t elapsedTime = clock.getElapsedTime().asMilliseconds();
        // Input every 50 ms
        if (elapsedTime % 50 == 0)
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                // prevent bug with going thru yourself by pressing two keys instantly
                if (elapsedTime - last_changed < 200)
                    break;
                if (event.type == sf::Event::KeyPressed)
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                        window.close();
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) and direction != sd::DOWN)
                    {
                        direction = sd::UP;
                        last_changed = elapsedTime;
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) and direction != sd::RIGHT)
                    {
                        direction = sd::LEFT;
                        last_changed = elapsedTime;
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) and direction != sd::UP)
                    {
                        direction = sd::DOWN;
                        last_changed = elapsedTime;
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) and direction != sd::LEFT)
                    {
                        direction = sd::RIGHT;
                        last_changed = elapsedTime;
                    }
                }
                else if (event.type == sf::Event::Closed)
                    window.close();
            }
        }
        // Redraw every 200 ms
        if (elapsedTime % 200 == 0)
        {
            window.clear();
            for (uint32_t x = 0; x < window.getSize().x; x += CELL_X + GAP)
            {
                for (uint32_t y = 0; y < window.getSize().y; y += CELL_Y + GAP) {
                    window.draw(rect);
                    rect.setPosition(x, y);
                }
            }
            sf::Vector2f headPos = snake.front().getPosition();
            if (headPos.x >= window.getSize().x) headPos.x = -CELL_X - GAP;
            if (headPos.x == 0 and direction == sd::LEFT) headPos.x = window.getSize().x;
            if (headPos.y >= window.getSize().y) headPos.y = -CELL_X - GAP;
            if (headPos.y == 0 and direction == sd::UP) headPos.y = window.getSize().y;
            switch (direction)
            {
            case sd::UP:
                snake.insert(snake.begin(), Cell(headPos.x, headPos.y - (GAP + CELL_Y)));
                break;
            case sd::LEFT:
                snake.insert(snake.begin(), Cell(headPos.x - (GAP + CELL_X), headPos.y));
                break;
            case sd::DOWN:
                snake.insert(snake.begin(), Cell(headPos.x, headPos.y + (GAP + CELL_Y)));
                break;
            case sd::RIGHT:
                snake.insert(snake.begin(), Cell(headPos.x + (GAP + CELL_X), headPos.y));
                break;
            }
            if (apple.getPosition() != headPos) snake.pop_back();
            else
            {
                srand(clock.getElapsedTime().asMicroseconds());
                sf::Vector2i rnd(1 + rand() % CELLS_X - 1, 1 + rand() % CELLS_Y - 1);
                apple.setPosition((CELL_X + GAP) * rnd.x, (CELL_Y + GAP) * rnd.y);
            }
            apple.setFillColor(sf::Color::Red);
            apple.draw(&window);
            uint16_t collisions_with_head = 0;
            for (Cell cell : snake)
            {
                cell.setFillColor(getIndex(snake, cell) == 0 ? sf::Color(255, 100, 0) : sf::Color(255, 150, 0));
                cell.draw(&window);
                if (cell.getPosition() == headPos) collisions_with_head++;
            }
            if (collisions_with_head > 1) playing = false;
            window.display();
        }
    }

    std::cout << "You lost! Score: " << snake.size() << std::endl;
    window.close();
}

Game::Game(std::string title)
{
    window.create(sf::VideoMode(CELL_X * CELLS_X + (GAP * CELLS_X), CELL_Y * CELLS_Y + (GAP * CELLS_Y)), title, sf::Style::Close);
    rect = sf::RectangleShape(sf::Vector2f(CELL_X, CELL_Y));
    // Back cells color
    rect.setFillColor(sf::Color::White);
    srand(clock.getElapsedTime().asMicroseconds());
    sf::Vector2i rnd(1 + rand() % CELLS_X - 1, 1 + rand() % CELLS_Y - 1);

    apple = Cell((CELL_X + GAP) * rnd.x, (CELL_Y + GAP) * rnd.y);

    snake.push_back(Cell(CELL_X * 10 + (GAP * 10), CELL_Y * 10 + (GAP * 10)));
    snake.push_back(Cell(CELL_X * 10 + (GAP * 10), CELL_Y * 9 + (GAP * 9)));
    snake.push_back(Cell(CELL_X * 10 + (GAP * 10), CELL_Y * 8 + (GAP * 8)));
}
Game::~Game()
{
    delete& snake;
}