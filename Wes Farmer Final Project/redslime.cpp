#include "redslime.h"
#include <cmath>

RedSlime::RedSlime(int x, int y) : Enemy(50, x, y, 3,100, "Graphics/slime2.png") {
    speed = 2.0f;
    // Set the texture to the blue slime texture rectangle
    enemySprite.setTextureRect(sf::IntRect(8, 12, 16, 12));
    enemySprite.setScale(5, 5);
}

//void RedSlime::update(const sf::Vector2f& treePos) {
//    // Calculate the direction vector to the tree
//    sf::Vector2f direction(treePos.x - x, treePos.y - y);
//
//    // Normalize the direction vector
//    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
//    direction.x /= length;
//    direction.y /= length;
//
//    // Move the slime
//    x += direction.x * speed;
//    y += direction.y * speed;
//
//    setPosition(x, y);
//}
