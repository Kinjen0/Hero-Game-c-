#include "BlueSlime.h"
#include <cmath>
//change speed later to 100
BlueSlime::BlueSlime(int x, int y) : Enemy(100, x, y, 50, 500, "Graphics/slime.png") {
    speed = 1.5;
    // Set the texture to the blue slime texture rectangle
    enemySprite.setTextureRect(sf::IntRect(8, 12, 16, 12));
    enemySprite.setScale(5, 5);
    
}

//void BlueSlime::update( const sf::Vector2f& treePos) {

