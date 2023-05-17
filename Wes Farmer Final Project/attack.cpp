#include <SFML/Graphics.hpp>
#include "attack.h"
// Default constructor
Attack::Attack(float x, float y, float speed, const sf::Vector2f& direction, const std::string& attackTexturePng)
{
	this->x = x;
	this->y = y;
	this->speed = speed;
	this->direction = direction;
	damage = 1;
	attackTexture.loadFromFile(attackTexturePng);
	attackSprite.setTexture(attackTexture);
	attackSprite.setPosition(x, y);
	attackSprite.setScale(2,2);
	
}
// Function to move the attack in the direction it was fired
void Attack::update(float dt)
{
	x += direction.x * speed * dt;
	y += direction.y * speed * dt;
	attackSprite.setPosition(x, y);
}
// Function to draw the attack on to the screen
void Attack::draw(sf::RenderWindow& window)
{
	window.draw(attackSprite);
}
sf::Vector2f Attack::getPosition()
{
	return attackSprite.getPosition();
}
