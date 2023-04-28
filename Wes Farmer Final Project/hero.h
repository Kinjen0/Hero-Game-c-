#pragma once
#include <SFML/Graphics.hpp>

class Hero {
public:
    Hero();
    Hero(float tileScaleX, float tileScaleY);

    void update(float dt);
    void draw(sf::RenderWindow& window);
    void handleInput();

    sf::Vector2f getPosition() const;

private:
    void updateAnimation(float dt);

    sf::Texture playerTexture;
    sf::Sprite playerSprite;

    float speed;
    float tileScaleX;
    float tileScaleY;

    int animationDirection;
    int animationFrame;
    float elapsedTime;
    float animationDuration;
};
