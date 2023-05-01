#pragma once
#include <SFML/Graphics.hpp>

class Player {
public:
    Player(float startX, float startY, const std::string& textureFile, int playerSpeed);

    void update(float dt);
    void draw(sf::RenderWindow& window);

    sf::Vector2f getPosition();
    float getPositionX();
    float getPositionY();
    void setPosition(float x, float y);
    sf::Vector2f getFacingDirection();


    void handleInput();

private:
    void updateAnimation(float dt);

    sf::Texture playerTexture;
    sf::Sprite playerSprite;
    int playerSpeed;

    //player position storage
    float x;
    float y;

    // Variable to store where the player is facing in degrees
    float faceDirection;

    int currentFrame;
    int currentDirection; // 0: down, 1: left, 2: right, 3: up
    float frameTime;
    float timePerFrame;
    int frameWidth;
    int frameHeight;

    int rows;
    int columns;
};
