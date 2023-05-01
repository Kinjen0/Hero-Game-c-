#pragma once
#include <SFML/Graphics.hpp>
class Attack
{
public:
	Attack(float x, float y, float speed, const sf::Vector2f& direction, const std::string& attackTexture);
	void update(float dt);
	void draw(sf::RenderWindow& window);	
	sf::Texture attackTexture;
	sf::Sprite attackSprite;
	float x;
	float y;
	float speed;
	int damage;
	sf::Vector2f direction;

};