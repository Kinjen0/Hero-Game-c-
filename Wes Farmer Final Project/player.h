#pragma once
#include <SFML/Graphics.hpp>

class Player {
public:
    Player(float startX, float startY, const std::string& textureFile, int playerSpeed);

    void update(float dt);
    void draw(sf::RenderWindow& window);

    sf::Vector2f getPosition();
    void setPosition(float x, float y);

    void handleInput();

private:
    void updateAnimation(float dt);

    sf::Texture playerTexture;
    sf::Sprite playerSprite;
    int playerSpeed;

    int currentFrame;
    int currentDirection; // 0: down, 1: left, 2: right, 3: up
    float frameTime;
    float timePerFrame;
    int frameWidth;
    int frameHeight;

    int rows;
    int columns;
};
