//Player spritesheet came from
//https://totuslotus.itch.io/characterpack
#include "player.h"

Player::Player(float startX, float startY, const std::string& textureFile, int playerSpeed) {
    playerTexture.loadFromFile(textureFile);
    
    playerSprite.setTexture(playerTexture);
    playerSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
    playerSprite.setPosition(startX, startY);
    playerSprite.setScale(5, 5);
    this->playerSpeed = playerSpeed;
    
    //variables to manage player animation
    currentFrame = 0;
    currentDirection = 0;
    frameTime = 0;
    // Time between the frames of the animation
    timePerFrame = 0.1f; 
    frameWidth = 16; 
    frameHeight = 16; 

    rows = 4;
    columns = 4;
}

void Player::update(float dt) {
    //handel movement
    sf::Vector2f movement(0.0f, 0.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        movement.y -= playerSpeed;

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        movement.y += playerSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        movement.x -= playerSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        movement.x += playerSpeed;
    }


    //change direction for player animation
    if (movement.x < 0) {
        currentDirection = 3;
    }
    else if (movement.x > 0) {
        currentDirection = 2;
    }
    else if (movement.y > 0) {
        currentDirection = 0;
    }
    else if (movement.y < 0) {
        currentDirection = 1;
    }
    playerSprite.move(movement * dt);

    updateAnimation(dt);
}
// Function to draw the player on to the screen
void Player::draw(sf::RenderWindow& window) {
    window.draw(playerSprite);
}
// Return the players current position
sf::Vector2f Player::getPosition() {
    return playerSprite.getPosition();
}
// Update the players animation
void Player::updateAnimation(float dt) {
    frameTime += dt;

    if (frameTime >= timePerFrame) {
        frameTime = 0;
        currentFrame++;

        // IF the current frame is greater than 3 reset it to frame zero
        if (currentFrame >= 3) {
            currentFrame = 0;
        }

        // figure out the x and y cordinants of the current frame
        int x = currentDirection * frameWidth;
        int y = currentFrame * frameHeight;
        

        // Update the texture rect to display the current frame
        playerSprite.setTextureRect(sf::IntRect(x, y, frameWidth, frameHeight));

    }
}
// Return the direction the player is currently facing
sf::Vector2f Player::getFacingDirection()
{
    sf::Vector2f direction;

    switch (currentDirection)
    {
    case 0: // Down
        direction = sf::Vector2f(0, 1);
        break;
    case 1: // Up
        direction = sf::Vector2f(0, -1);
        break;
    case 2: // Right
        direction = sf::Vector2f(1, 0);
        break;
    case 3: // Left
        direction = sf::Vector2f(-1, 0);
        break;
    default:
        direction = sf::Vector2f(0, 0);
        break;
    }

    return direction;
}
