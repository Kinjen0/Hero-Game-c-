#include "blueslime.h"
#include <cmath>

// Default constructor, 
BlueSlime::BlueSlime(int x, int y) : Enemy(1, x, y, 5, 200, "Graphics/slime.png") {
    speed = 1.5;
    // Set the texture to the blue slime texture rectangle
    enemySprite.setTextureRect(sf::IntRect(8, 12, 16, 12));
    enemySprite.setScale(5, 5);
    
}

