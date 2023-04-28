#include "Enemy.h"
#include <SFML/Graphics.hpp>

class RedSlime : public Enemy {
private:
    float speed = 100;


public:
    RedSlime(int x, int y);
//void update(const sf::Vector2f& treePos); // Add the treePos parameter
    //get global bounds

};
