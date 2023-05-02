#include "tree.h"

Tree::Tree(int treeHealth, int x, int y) {
	this->treeHealth = treeHealth;
	this->x = x;
	this->y = y;
	treeTexture.loadFromFile("Graphics/tree.png");
	treeSprite.setTexture(treeTexture);
	treeSprite.setPosition(x, y);
	treeSprite.setScale(3, 3);
}
void Tree::takeDamage(int damage) {
	treeHealth -= damage;
	if (treeHealth <= 0)
	{
		//cry about it lol
	}
}
void Tree::drawTree(sf::RenderWindow& window) {
	window.draw(treeSprite);
}
void Tree::setPosition(int x, int y) {
	treeSprite.setPosition(x, y);
}
sf::Vector2f Tree::getPosition()
{
	return treeSprite.getPosition();
}
int Tree::getHealth()
{
	return treeHealth;
}
void Tree::resetHealth()
{
	treeHealth = 100;
}