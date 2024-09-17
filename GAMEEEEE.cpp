#include "SFML/Graphics.hpp"
#include <iostream>
#include <random>
#define size 25
using namespace std;
using namespace sf;

struct Apple
{
    int x, y;
} apple;

struct snake
{
    int x, y;
} s[100];

int snakesize = 1, snakespeed = 1;
bool gameOver = false;
enum SnakeDirection {
    UP, DOWN, LEFT, RIGHT 
};

SnakeDirection dir = SnakeDirection::RIGHT;

void move()
{
    for (int i = snakesize; i > 0; i--)
    {
        s[i].x = s[i - 1].x;
        s[i].y = s[i - 1].y;
    }

    switch (dir) {
    case SnakeDirection::UP:
        s[0].y -= 1;
        break;
    case SnakeDirection::DOWN:
        s[0].y += 1;
        break;
    case SnakeDirection::LEFT:
        s[0].x -= 1;
        break;
    case SnakeDirection::RIGHT:
        s[0].x += 1;
        break;
    }

    for (int i = 1; i < snakesize; i++)
    {
        if ((s[0].x == s[i].x) && (s[0].y == s[i].y))
        {
            // Collision detected
            gameOver = true;
            break;
        }
    }

    if (s[0].x == apple.x && s[0].y == apple.y)
    {
        snakesize++;
        snakespeed++;
        apple.x = rand() % size;
        apple.y = rand() % size;
    }

    // Borders
    if (s[0].x > size || s[0].y > size || s[0].x < 0 || s[0].y < 0)
    {
        gameOver = true;
    }
    //borders
    /*  
    if (s[0].x > size)s[0].x = 0;
    if (s[0].y > size)s[0].y = 0;
    if (s[0].x < 0)s[0].x = size;
    if (s[0].y < 0)s[0].y = size;
    */
  
}

int main()
{
    RenderWindow window(VideoMode((int)pow(size, 2), (int)pow(size, 2)), "Snake game");
    RectangleShape appleShape(Vector2f(size, size));
    appleShape.setFillColor(Color::Red);
    RectangleShape snakeShape(Vector2f(size, size));
    snakeShape.setFillColor(Color::Yellow);

    apple.x = rand() % size;
    apple.y = rand() % size;

    Clock clock;
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                case Keyboard::Up:
                    dir = SnakeDirection::UP;
                    break;
                case Keyboard::Down:
                    dir = SnakeDirection::DOWN;
                    break;
                case Keyboard::Left:
                    dir = SnakeDirection::LEFT;
                    break;
                case Keyboard::Right:
                    dir = SnakeDirection::RIGHT;
                    break;
                }
            }
        }

        window.clear();
        appleShape.setPosition(apple.x * size, apple.y * size);
        window.draw(appleShape);

        if (clock.getElapsedTime().asMilliseconds() > 100)
        {
            move();
            clock.restart();
        }

        if (gameOver) {
            // Game over
            cout << "Game over" << endl;
            return 0;
        }

        for (int i = 0; i < snakesize; i++)
        {
            snakeShape.setPosition(s[i].x * size, s[i].y * size);
            window.draw(snakeShape);
        }

        window.display();
    }

    return 0;
}