/*CREDITS
* 
* I took inspiration from this source to center the paused text
* https://stackoverflow.com/questions/14505571/centering-text-on-the-screen-with-sfml
* //Player spritesheet came from this source although I did modify it a little to make it easier for me to animate
//https://totuslotus.itch.io/characterpack
* the slime spritesheets came from
* https://game-endeavor.itch.io/mystic-woods

* 
* 
* 
* 


*/


#include <SFML/Graphics.hpp>
#include "player.h"
#include "tree.h"
#include "enemy.h"
#include "blueslime.h"
#include "redslime.h"
#include "attack.h"
using namespace std;	

//view size
int viewWidth = 1920;
int viewHeight = 1080;



//values to scale the tiles based on the window size
float tileScaleX = viewWidth / (15.0f * 16) + 0.02f;
float tileScaleY = viewHeight / (15.0f * 16) + 0.02f;

// Boolean to pause the game
bool paused = false;

// Font to use for text
sf::Font font;
// Text to display when the game is paused
sf::Text pauseText;
//rectangle to store the demensions of the pause text box
sf::FloatRect textRect;

//shape to display on the screen when the game is paused
sf::RectangleShape blackRectangle(sf::Vector2f(viewWidth, viewHeight));

//text for the trees health
sf::Text treeHealthText;

// vector to store the players current position
sf::Vector2f playerPosition;

//store the players current direction
sf::Vector2f playerDirection;

// Variables to manage the attack cooldowns
bool canAttack = true;
sf::Clock attackClock;




//render window
sf::RenderWindow window(sf::VideoMode(viewWidth, viewHeight), "SFML works!");
sf::Texture grassTexture;
sf::Sprite grassSprite;
sf::Texture wallTexture;
sf::Sprite wallSprite;


// Initialize the player with starting position and texture file and speed
Player player(50, 50, "Graphics/player.png", 250.f);
Tree tree(100, viewWidth / 2 - 72, viewHeight / 2 - 96);

//code for the second tree to be added
// 
//code for the third tree to be added

//15 x 15 array to hold values to create a tilemap
int mapArray[15][15] = {
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
};
// Initializing function
void init()
{
	//load the 16 x 16 grass texture
	grassTexture.loadFromFile("Graphics/grass.png");
	grassSprite.setTexture(grassTexture);

	//load the wall texture
	wallTexture.loadFromFile("Graphics/wall.png");
	wallSprite.setTexture(wallTexture);

	//initialize the font
	font.loadFromFile("Alkatra-VariableFont_wght.ttf");

	//initialize the pause text
	pauseText.setFont(font);
	pauseText.setString("Paused");

	//set the pause rectangle to black
	blackRectangle.setFillColor(sf::Color::Black);

	//set the tree health
	treeHealthText.setFont(font);



}
// Function to create the tilemap
void drawMap()
{
	//loop through the array
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			// If the value is 0, create a grass tile
			if (mapArray[i][j] == 0)
			{
				grassSprite.setPosition(i * 16 * tileScaleX, j * 16 * tileScaleY);
				grassSprite.setScale(tileScaleX, tileScaleY);
				window.draw(grassSprite);
			}
			else if (mapArray[i][j] == 1)
			{
				wallSprite.setPosition(i * 16 * tileScaleX, j * 16 * tileScaleY);
				wallSprite.setScale(tileScaleX, tileScaleY);
				window.draw(wallSprite);
			}
		}
	}
}
void update(float dt, const sf::Vector2f& treePos)
{
	player.update(dt); // Update player
		player.draw(window); // Draw player
		tree.drawTree(window);

		//display the trees health above it
		treeHealthText.setString("Tree Health: " + std::to_string(tree.getHealth()));
		//treeHealthText.setOrigin(tree.getPosition().x, tree.getPosition().y - 50);
		float treeHealthTextWidth = treeHealthText.getLocalBounds().width;
		treeHealthText.setPosition(tree.getPosition().x - (treeHealthTextWidth / 6), tree.getPosition().y - 50);
		window.draw(treeHealthText);


}

void spawnRandomEnemy(vector<unique_ptr<Enemy>>& enemies, const sf::Vector2f& treePos) {
	int corner = rand() % 2;
	int x, y;

	if (corner == 0) {
		// Top left corner
		x = 0 - 100;
		y = 0 - 100;
	}
	else {
		// Bottom right corner
		x = viewWidth;
		y = viewHeight;
	}

	int enemyType = rand() % 2;

	if (enemyType == 0) {
		enemies.push_back(make_unique<BlueSlime>(x, y));
	}
	else {
		enemies.push_back(make_unique<RedSlime>(x, y));
	}
}

void createAttack(std::vector<unique_ptr<Attack>>& attacks, sf::Vector2f playerPosition, sf::Vector2f playerDirection) {
	// Get the player's position and speed
	float attackSpeed = 1000.f;

	// Create a new attack
	Attack newAttack(playerPosition.x, playerPosition.y, attackSpeed, playerDirection, "Graphics/attack.png");
	attacks.push_back(make_unique<Attack>(playerPosition.x, playerPosition.y, attackSpeed, playerDirection, "Graphics/attack.png"));
}


int main() {
	//vector to store enemies
	vector<unique_ptr<Enemy>> enemies;
	
	//vector to store attacks.
	vector<unique_ptr<Attack>> attacks;
	//potental vector to allow for multiple trees
	//vector<unique_ptr<Tree>> trees;

	//variable to store the location of the tree
	sf::Vector2f treePos = tree.getPosition();

	// Variable to manage game over if the tree drops to or below 0 hp
	bool gameOver = false;



	sf::Clock clock;
	while (window.isOpen()) {
		float dt = clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		init();

		//if statement to display the game over window if the game is lost
		if (gameOver)
		{
			//create the text for the game over
			sf::Text gameOverText;
			gameOverText.setScale(5, 5);
			gameOverText.setFont(font);
			gameOverText.setString("Game Over");
			gameOverText.setFillColor(sf::Color::Red);
			textRect = gameOverText.getLocalBounds();
			// set the game over text to the center of the screen
			gameOverText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
			gameOverText.setPosition(sf::Vector2f(viewWidth / 2.0f, viewHeight / 2.0f));

			window.draw(blackRectangle);
			window.draw(gameOverText);
		}

		//if statement to check if the game is not yet lost
		if (!gameOver)
		{

			// If statement to check if escape is pressed and pause the game

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				if (paused == true)
				{
					paused = false;
				}
				else
				{
					paused = true;
				}

				// Code to prevent the escape key from being spammed
				sf::sleep(sf::milliseconds(400));

			}
			//i If the game is not paused, keep running the game
			if (paused != true)
			{
				// Spawn enemies every few seconds using a clock variable
				static sf::Clock spawnClock;
				if (spawnClock.getElapsedTime().asSeconds() >= 2.0f) {
					spawnRandomEnemy(enemies, treePos);
					spawnClock.restart();
				}

				window.clear(sf::Color::Red);
				//call the funciton to draw the map
				drawMap();

				//call the update function
				update(dt, treePos);

				// Update and draw enemies
				for (auto& enemy : enemies) {
					enemy->update(dt, treePos);
					enemy->drawEnemy(window);
				}

				// Check collisions between enemies and trees
	//for(auto enemyCount = enemies.begin(); enemyCount != enemies.end();)
				for (auto enemyIterator = enemies.begin(); enemyIterator != enemies.end();) {
					bool enemyDestroyed = false;

					if (tree.treeSprite.getGlobalBounds().intersects((*enemyIterator)->getGlobalBounds())) {
						tree.takeDamage((*enemyIterator)->getDamage());

						if (tree.getHealth() <= 0) {
							//insert code for the game over
							// if the tree drops below 0 hp then set the gameOver bool to true
							gameOver = true;
							
							//call update one last time
							update(dt, treePos);
							
						}

						enemyDestroyed = true;
					}


					if (enemyDestroyed) {
						enemyIterator = enemies.erase(enemyIterator); // Remove the enemy
					}
					else {
						++enemyIterator;
					}
				}

//attack section
// 				//manage attack cooldown
				float attackCooldown = 0.2f; // cooldown time using seconds
				if (!canAttack && attackClock.getElapsedTime().asSeconds() >= attackCooldown)
				{
					canAttack = true;
					attackClock.restart();
				}

				//if the spacebar is created make an attack
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canAttack) 
				{
					sf::Vector2f playerPos = player.getPosition();
					sf::Vector2f attackDirection = player.getFacingDirection();
					createAttack(attacks, playerPos, attackDirection);
					canAttack = false;
				}

				
				// Update and draw attacks
				for (auto& attack : attacks)
				{
					attack->update(dt);
					attack->draw(window);
				}



				// manage player attack and its collision with enemies
				for (auto attackIterator = attacks.begin(); attackIterator != attacks.end();) {
					bool attackHit = false;

					for (auto enemyIterator = enemies.begin(); enemyIterator != enemies.end();) {
						bool enemyDestroyed = false;

						if ((*enemyIterator)->getGlobalBounds().intersects((*attackIterator)->attackSprite.getGlobalBounds())) {
							(*enemyIterator)->takeDamage();

							if ((*enemyIterator)->getHealth() <= 0) {
								enemyDestroyed = true;
							}

							attackHit = true;
						}

						if (enemyDestroyed) {
							enemyIterator = enemies.erase(enemyIterator);
						}
						else {
							++enemyIterator;
						}
					}

					if (attackHit) {
						attackIterator = attacks.erase(attackIterator);
					}
					else {
						++attackIterator;
					}
				}





			}
			else
			{
				//display the paused text
				/*
				* Note. I took the inspiration for centering the text from this link
				* https://stackoverflow.com/questions/14505571/centering-text-on-the-screen-with-sfml

				*/
				//show the rectangle 
				textRect = pauseText.getLocalBounds();
				window.draw(blackRectangle);
				pauseText.setScale(5, 5);

				pauseText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				pauseText.setPosition(sf::Vector2f(viewWidth / 2.0f, viewHeight / 2.0f));

				//pauseText.setPosition(viewWidth / 2.0f - (pauseText.getCharacterSize() / 2), viewHeight / 2.0f - 100);
				window.draw(pauseText);
			}
		}
		window.display();
	}
}
