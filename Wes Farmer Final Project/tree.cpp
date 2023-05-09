#include "tree.h"
// Default constructor
Tree::Tree(int treeHealth, int x, int y) {
	this->treeHealth = treeHealth;
	this->x = x;
	this->y = y;
	treeTexture.loadFromFile("Graphics/tree.png");
	treeSprite.setTexture(treeTexture);
	treeSprite.setPosition(x, y);
	treeSprite.setScale(3, 3);
}
// Function to allow the tree to take damage
void Tree::takeDamage(int damage) {
	treeHealth -= damage;
	if (treeHealth <= 0)
	{
		//cry about it lol
	}
}
// Function to draw the tree on to the window
void Tree::drawTree(sf::RenderWindow& window) {
	window.draw(treeSprite);
}
// Function to update the tree's position
void Tree::setPosition(int x, int y) {
	treeSprite.setPosition(x, y);
}
// Function to return the tree's position
sf::Vector2f Tree::getPosition()
{
	return treeSprite.getPosition();
}
// Function to return the tree's health
int Tree::getHealth()
{
	return treeHealth;
}
// Function to reset the tree's health
void Tree::resetHealth()
{
	treeHealth = 100;
}
// Function to heal the tree a given ammount
void Tree::healTree()
{
	treeHealth += 10;
}