#include "Enemy.h"

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
}

void Enemy::decreaseHealth(int damage) {
    health -= damage;
}

void Enemy::drawEnemy(sf::RenderWindow& window) {
    window.draw(enemySprite);
}

void Enemy::setPosition(int x, int y) {
    enemySprite.setPosition(x, y);
}

void Enemy::update(float dt, const sf::Vector2f& treePos){    
    // Calculate the direction vector to the tree
    sf::Vector2f direction(treePos.x - x, treePos.y - y);

    // Normalize the direction vector
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    direction.x /= length;
    direction.y /= length;

    // Move the slime
    //x += direction.x * speed;
    //y += direction.y * speed;
    enemySprite.move(direction * speed * dt);
    //setPosition(x, y);
}
int Enemy::getDamage() {
	return damage;
}
//get enemy bounds
sf::FloatRect Enemy::getGlobalBounds() {
	return enemySprite.getGlobalBounds();
}
void Enemy::takeDamage()
{
    health -= 1;
}
int Enemy::getHealth()
{
    return health;
}