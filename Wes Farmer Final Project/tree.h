#pragma once
#include <SFML/Graphics.hpp>
class Tree
{
public:
	Tree(int treeHealth, int x, int y);
	void takeDamage(int damage);
	void drawTree(sf::RenderWindow& window);
	void setPosition(int x, int y);
	sf::Vector2f getPosition();
	int getHealth();
	void resetHealth();

	sf::Texture treeTexture;
	sf::Sprite treeSprite;
private:
	int treeHealth;
	int x;
	int y;

};