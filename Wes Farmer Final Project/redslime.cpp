#include "redslime.h"
#include <cmath>
RedSlime::RedSlime(int x, int y) : Enemy(1, x, y, 5,300, "Graphics/slime2.png") {
    // set the speed of the red slime
    speed = 2.0f;
    // Set the texture to the blue slime texture rectangle
    enemySprite.setTextureRect(sf::IntRect(8, 12, 16, 12));
    enemySprite.setScale(5, 5);
}

