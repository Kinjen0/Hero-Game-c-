#pragma once
#include <SFML/Graphics.hpp>
class Enemy
{
public:
	Enemy(int health, int x, int y, int damage, float speed, const std::string& textureFile);
	void decreaseHealth(int damage);
	void drawEnemy(sf::RenderWindow& window);
	void setPosition(int x, int y);
	void update(float dt,const sf::Vector2f& treePos);
	void update(float dt, const sf::Vector2f& tree1Pos, const sf::Vector2f& tree2Pos);
	int getDamage();
	void takeDamage();
	int getHealth();
	//get global bounds
	sf::FloatRect getGlobalBounds();
	sf::Texture enemyTexture;
	sf::Sprite enemySprite;
	int health;
	int x;
	int y;
	int damage;
	float speed;
	int target;


};
