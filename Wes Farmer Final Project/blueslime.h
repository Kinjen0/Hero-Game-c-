#pragma once
#include "enemy.h"

class BlueSlime : public Enemy
{
public:
    BlueSlime(int x, int y);
    //void update(const sf::Vector2f& treePos);
private:
	float speed;
};
