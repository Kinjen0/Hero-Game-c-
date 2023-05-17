#include "enemy.h"
#include <math.h>
// Default constructor for the enemy, taking in its health, position, damage, speed, and texture file
Enemy::Enemy(int health, int x, int y, int damage, float speed, const std::string& textureFile) {
    this->health = health;
    this->x = x;
    this->y = y;
    this->damage = damage;
    this->speed = speed;
    enemyTexture.loadFromFile(textureFile);
    enemySprite.setTexture(enemyTexture);
    enemySprite.setPosition(x, y);
    enemySprite.setScale(1, 1);
    target = -1;
}
// Function to decrease the enemy's health according to a given damage value
void Enemy::decreaseHealth(int damage) {
    health -= damage;
}
// Function to draw the enemy on the window
void Enemy::drawEnemy(sf::RenderWindow& window) {
    window.draw(enemySprite);
}
// Function to set the enemy's position
void Enemy::setPosition(int x, int y) {
    enemySprite.setPosition(x, y);
}
// Function to update the enemy based on its position relative to the tree
void Enemy::update(float dt, const sf::Vector2f& treePos){    
    // Calculate the direction vector to the tree
    sf::Vector2f direction(treePos.x - x, treePos.y - y);

    // Normalize the direction vector
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    direction.x /= length;
    direction.y /= length;

    // Move the slime
    enemySprite.move(direction * speed * dt);
}
// Overloaded enemy update for level 2
void Enemy::update(float dt, const sf::Vector2f& tree1Pos, const sf::Vector2f& tree2Pos)
{
    sf::Vector2f targetTreePos;

    if (target == -1)
    {
        target = rand() % 2;
    }
    if (target == 1)
    {
		targetTreePos = tree1Pos;
	}
    else
    {
		targetTreePos = tree2Pos;
	}

    // Calculate the movement direction
    sf::Vector2f movementDirection = targetTreePos - enemySprite.getPosition();
    float length = std::sqrt(std::pow(movementDirection.x, 2) + std::pow(movementDirection.y, 2));
    movementDirection /= length;

    // Move the enemy towards the tree
    enemySprite.move(movementDirection * speed * dt);
}
// Function to return the enemy's damage
int Enemy::getDamage() {
	return damage;
}
// Get the global bounds of the enemy
sf::FloatRect Enemy::getGlobalBounds() {
	return enemySprite.getGlobalBounds();
}
// Function to deal damage to the enemy
void Enemy::takeDamage()
{
    health -= 1;
}
// Function to return the enemy's health
int Enemy::getHealth()
{
    return health;
}
