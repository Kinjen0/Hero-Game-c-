/*CREDITS
* 
* I took inspiration from this source to center the paused text
* https://stackoverflow.com/questions/14505571/centering-text-on-the-screen-with-sfml
* //Player spritesheet came from this source although I did modify it a little to make it easier for me to animate
//https://totuslotus.itch.io/characterpack
* the slime spritesheets came from
* https://game-endeavor.itch.io/mystic-woods
* I got the code for the random number setter from
* https://stackoverflow.com/questions/11943525/seeding-a-random-number-generator-c

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
int viewWidth = 2560;
int viewHeight = 1440;

//trying to get the view working
//int viewWidth = sf::VideoMode::getDesktopMode().width;
//int viewHeight = sf::VideoMode::getDesktopMode().height;
//set the view to the desktop size
//sf::View view(sf::FloatRect(0, 0, viewWidth, viewHeight));




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
//second tree health text
sf::Text tree2HealthText;

// vector to store the players current position
sf::Vector2f playerPosition;

//store the players current direction
sf::Vector2f playerDirection;

// Variables to manage the different clocks and timers I use
bool canAttack = true;
sf::Clock attackClock;
sf::Text timerText;
sf::Clock timerClock;

// Text for the players score
sf::Text scoreText;
int score;

//healing cooldown
sf::Clock healClock;
bool canHeal = true;



//render window
sf::RenderWindow window(sf::VideoMode(viewWidth, viewHeight), "SFML works!");


sf::Texture grassTexture;
sf::Sprite grassSprite;
sf::Texture wallTexture;
sf::Sprite wallSprite;


// Initialize the player with starting position and texture file and speed
Player player(viewWidth / 2, viewHeight / 2, "Graphics/player.png", 400.f);
Tree tree(100, viewWidth / 2 - 72, viewHeight / 2 - 96);
//set the tree off in narnia because its hitbox is still there
Tree tree2(100, 10000, 0);

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
	//set the view to the window

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
	//set up the second tree text
	tree2HealthText.setFont(font);


	// Variables to manage the players Score
	//score = 0;
	scoreText.setFont(font);
	scoreText.setPosition(viewWidth / 2 + 200, 25);

	//set up the timer text
	timerText.setFont(font);

	//set the level as one
	//level = 1;



}
//reset the timer clock 
void resetTimer()
{
	timerClock.restart();
	//and reset score
	score = 0;
}
void healTree(sf::Vector2f playerPos)
{
	tree.getPosition();
	tree2.getPosition();
	if (score < 0)
	{
		//find the closest tree to the player
		score -= 0;
		canHeal = false;

	}
}
//title screen function
void titleScreen()
{
	sf::Text titleText1;
	sf::Text titleText2;
	sf::Text titleText3;
	bool endTitle = false;
	//set the title text to the directions for the game
	titleText1.setFont(font);
	titleText1.setString("Welcome to the Protectors of the great tree");
	titleText1.setPosition(viewWidth / 2 - 300, viewHeight / 2 - 200);
	titleText2.setFont(font);
	titleText2.setString("Use the W, A, S, D to move and the space bar to attack");
	titleText2.setPosition(viewWidth / 2 - 300, viewHeight / 2 - 100);
	titleText3.setFont(font);
	titleText3.setString("Press enter to start");
	titleText3.setPosition(viewWidth / 2 - 300, viewHeight / 2);
	//while the title screen is up
	while (!endTitle)
	{
		//draw the title text
		window.draw(titleText1);
		window.draw(titleText2);
		window.draw(titleText3);
		window.display();
		// Reset the timer so that it dosent count the time the title screen is up
		resetTimer();

		//if the enter key is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			//end the title screen
			endTitle = true;
		}
	}

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
void update(float dt)
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
		
		//manage the second tree health text
		tree2HealthText.setString("Tree Health: " + std::to_string(tree2.getHealth()));
		float tree2HealthTextWidth = tree2HealthText.getLocalBounds().width;
		tree2HealthText.setPosition(tree2.getPosition().x - (tree2HealthTextWidth / 6), tree2.getPosition().y - 50);
		window.draw(tree2HealthText);
		
		// Update the timerText with the time since the game started
		timerText.setString("Time: " + std::to_string((int)timerClock.getElapsedTime().asSeconds()));

		

		





}

void spawnRandomEnemy(vector<unique_ptr<Enemy>>& enemies, const sf::Vector2f& treePos, int level) 
{
	int corner = rand() % 2;
	int x, y;

	if (corner == 0) {
		// Top left corner
		x = 50;
		y = 50;
	}
	else {
		// Bottom right corner
		x = viewWidth-100;
		y = viewHeight-100;
	}
	// if the level is 2 spawn both types of enemies at random. else only spawn the blue enemies
	if (level == 2)
	{
		int enemyType = rand() % 2;

		if (enemyType == 0) {
			enemies.push_back(make_unique<BlueSlime>(x, y));
		}
		else {
			enemies.push_back(make_unique<RedSlime>(x, y));
		}
	}
	else
	{
		enemies.push_back(make_unique<BlueSlime>(x, y));
	}
}

void createAttack(std::vector<unique_ptr<Attack>>& attacks, sf::Vector2f playerPosition, sf::Vector2f playerDirection) {
	// Get the player's position and speed
	float attackSpeed = 1000.f;

	// Create a new attack
	//Attack newAttack(playerPosition.x, playerPosition.y, attackSpeed, playerDirection, "Graphics/attack.png");
	attacks.push_back(make_unique<Attack>(playerPosition.x, playerPosition.y, attackSpeed, playerDirection, "Graphics/attack.png"));
}


int main() {

	//window.setView(view);


	//vector to store enemies
	vector<unique_ptr<Enemy>> enemies;
	
	//vector to store attacks.
	vector<unique_ptr<Attack>> attacks;
	//potental vector to allow for multiple trees
	//vector<unique_ptr<Tree>> trees;

	//set the random seed so its actually random
	srand(time(NULL));

	//variable to store the location of the trees
	sf::Vector2f tree1Pos = tree.getPosition();
	sf::Vector2f tree2Pos = tree2.getPosition();

	// Variable to manage game over if the tree drops to or below 0 hp
	bool gameOver = false;
	int level = 1;

	//window.create(sf::VideoMode(viewWidth, viewHeight), "bacon");


	//clock to manage the score
	sf::Clock scoreClock;
	init();
	titleScreen();
	resetTimer();


	sf::Clock clock;
	while (window.isOpen()) {
		float dt = clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//if statement to display the game over window if the game is lost
		if (gameOver)
		{
			//create the text for the game over
			sf::Text gameOverText;
			gameOverText.setCharacterSize(250);
			//gameOverText.setScale(5, 5);
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
				if (spawnClock.getElapsedTime().asSeconds() >= 1.0f) {
					spawnRandomEnemy(enemies, tree1Pos, level);
					spawnClock.restart();
				}

				window.clear(sf::Color::Red);
				//call the function to draw the map
				drawMap();

				//call the update function
				update(dt);
		//score
				if (scoreClock.getElapsedTime().asSeconds() > 1)
				{
					score++;
					scoreClock.restart();
				}
				// Modify and draw the score text
				scoreText.setString("Score: " + std::to_string(score));
				window.draw(scoreText);


				//draw the timer
				window.draw(timerText);
//LEVELS
				//create a change for the level
				if (level == 1 && timerClock.getElapsedTime().asSeconds() >= 3.0f) 
				{
					level = 2;
					timerClock.restart();
					tree.resetHealth();
					tree2.resetHealth();

					enemies.clear();
					attacks.clear();
				}
				//make the changes as required for the second level
				if (level == 2)
				{
					// set the first tree to the left bottom corner
					tree.setPosition(100, viewHeight - 150 - 72);
					// set the second tree to the right top corner
					tree2.setPosition(viewWidth - 100 - 96, 100);
					//get the updated positions
					tree1Pos = tree.getPosition();
					tree2Pos = tree2.getPosition();
				}
//TREE HEALING
				//check if the timer for healing has ran out
				if (healClock.getElapsedTime().asSeconds() >= 5.0f)
				{
					//reset the timer
					healClock.restart();
					canHeal = true;
				}
				// If the player presses E once, heal the closest tree
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && score >= 3 && canHeal == true) {
					tree.healTree();
				}

//Update and draw Enemies
				// Update and draw enemies
				for (auto& enemy : enemies) {
					if (level == 2) {
						enemy->update(dt, tree1Pos, tree2Pos);
					}
					else {
						enemy->update(dt, tree1Pos);
					}
					enemy->drawEnemy(window);
				}
//enemy section
		// Check collisions between enemies and trees
				for (auto enemyIterator = enemies.begin(); enemyIterator != enemies.end();) {
					bool enemyDestroyed = false;
					//check colision with the first tree
					if (tree.treeSprite.getGlobalBounds().intersects((*enemyIterator)->getGlobalBounds())) {
						tree.takeDamage((*enemyIterator)->getDamage());

						if (tree.getHealth() <= 0) {
							// if the tree drops below 0 hp then set the gameOver bool to true
							gameOver = true;
							
							//call update one last time
							update(dt);
							
						}

						enemyDestroyed = true;
					}

					// Check Colision with the second tree
					if (tree2.treeSprite.getGlobalBounds().intersects((*enemyIterator)->getGlobalBounds())) {
						tree2.takeDamage((*enemyIterator)->getDamage());

						if (tree2.getHealth() <= 0) {
							// if the tree drops below 0 hp then set the gameOver bool to true
							gameOver = true;
							
							//call update one last time
							update(dt);
							
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
				float attackCooldown = 0.5f; // cooldown time using seconds
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
				
						//create the second tree if the level is 2
		if (level == 2)
		{
			tree2.drawTree(window);
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
				pauseText.setCharacterSize(250);
				//pauseText.setScale(5, 5);

				pauseText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				pauseText.setPosition(sf::Vector2f(viewWidth / 2.0f, viewHeight / 2.0f));

				//pauseText.setPosition(viewWidth / 2.0f - (pauseText.getCharacterSize() / 2), viewHeight / 2.0f - 100);
				window.draw(pauseText);
			}
		}
		window.display();
	}
}
