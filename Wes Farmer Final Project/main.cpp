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
*/


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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

// Trying to get the view working to scale with the window size
//int viewWidth = sf::VideoMode::getDesktopMode().width;
//int viewHeight = sf::VideoMode::getDesktopMode().height;
//set the view to the desktop size
//sf::View view(sf::FloatRect(0, 0, viewWidth, viewHeight));




// Values to scale the tiles based on the window size
float tileScaleX = viewWidth / (15.0f * 16) + 0.02f;
float tileScaleY = viewHeight / (15.0f * 16) + 0.02f;

// Boolean to pause the game
bool paused = false;

// Font to use for text
sf::Font font;
// Text to display when the game is paused
sf::Text pauseText;
// Rectangle to store the demensions of the pause text box
sf::FloatRect textRect;

// Shape to display on the screen when the game is paused
sf::RectangleShape blackRectangle(sf::Vector2f(viewWidth, viewHeight));

// Text for the trees health
sf::Text treeHealthText;
// Second tree health text
sf::Text tree2HealthText;

//  Vector to store the players current position
sf::Vector2f playerPosition;

// Store the players current direction
sf::Vector2f playerDirection;

// Variables to manage the different clocks and timers I use
bool canAttack = true;
sf::Clock attackClock;
sf::Text timerText;
sf::Clock timerClock;

// Text for the players score
sf::Text scoreText;
int score;

// Healing cooldown
sf::Clock healClock;
bool canHeal = true;



// Primary render window
sf::RenderWindow window(sf::VideoMode(viewWidth, viewHeight), "SFML works!");

// Textures and sprites for the background
sf::Texture grassTexture;
sf::Sprite grassSprite;
sf::Texture wallTexture;
sf::Sprite wallSprite;


// Music objects
sf::Music gameMusic;


// Initialize the player with starting position and texture file and speed
Player player(viewWidth / 2, viewHeight / 2, "Graphics/player.png", 400.f);
Tree tree(100, viewWidth / 2 - 72, viewHeight / 2 - 96);
// Set the tree off in narnia because its hitbox is still there
Tree tree2(100, 10000, 0);


// 15 x 15 array to hold values to create a tilemap
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
	//handle music input
	//I got the music from https://pixabay.com/music/future-bass-my-universe-147152/
	gameMusic.openFromFile("my-universe-147152.wav");
	// Load the 16 x 16 grass texture
	grassTexture.loadFromFile("Graphics/grass.png");
	grassSprite.setTexture(grassTexture);

	// Load the wall texture
	wallTexture.loadFromFile("Graphics/wall.png");
	wallSprite.setTexture(wallTexture);

	// Initialize the font
	font.loadFromFile("Alkatra-VariableFont_wght.ttf");

	// Initialize the pause text
	pauseText.setFont(font);
	pauseText.setString("Paused");

	// Set the pause rectangle to black
	blackRectangle.setFillColor(sf::Color::Black);

	// Set the tree health
	treeHealthText.setFont(font);
	// Set up the second tree text
	tree2HealthText.setFont(font);
	
	// Set up the score text
	scoreText.setFont(font);
	scoreText.setPosition(viewWidth - 200, 25);
	scoreText.setCharacterSize(50);

	// Set up the timer text
	timerText.setFont(font);
	timerText.setPosition(25, 25);
	timerText.setCharacterSize(50);
}
// Function to reset the timer and score
void resetTimer()
{
	timerClock.restart();
	score = 0;
}
// Title screen function
void titleScreen()
{
	// Create the title text objects, 
	sf::Text titleText1;
	sf::Text titleText2;
	sf::Text titleText3;
	bool endTitle = false;
	// Set up the title text to the directions for the game
	titleText1.setFont(font);
	titleText1.setString("Welcome to the Protectors of the great tree\nYour goal is to protect the tree from the evil slimes for as long as you can. \nAfter 45 seconds you shall begin level 2");
	titleText1.setPosition(viewWidth / 2 - 300, viewHeight / 2 - 300);
	// Set up the second title text
	titleText2.setFont(font);
	titleText2.setString("Use the W, A, S, D to move \nSpace bar to attack\n And E to spend 30 points to heal the trees, This can only be done every 30 seconds.");
	titleText2.setPosition(viewWidth / 2 - 300, viewHeight / 2 - 100);
	// Set up the third title text
	titleText3.setFont(font);
	titleText3.setString("Press enter to start");
	titleText3.setPosition(viewWidth / 2 - 300, viewHeight / 2 + 100);
	// While the title screen is up
	while (!endTitle)
	{
		// Draw the title text
		window.draw(titleText1);
		window.draw(titleText2);
		window.draw(titleText3);
		window.display();
		// Reset the timer so that it dosen't count the time the title screen is up
		resetTimer();

		//if the enter key is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			// End the title screen
			endTitle = true;
		}
	}

}
// Function to create the tilemap
void drawMap()
{
	// Loop through the 2d array 
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			// If the value is 0, create a grass tile
			if (mapArray[i][j] == 0)
			{
				// Set the position of the grass tile to where it should be on the screen, and then scale it and draw it
				grassSprite.setPosition(i * 16 * tileScaleX, j * 16 * tileScaleY);
				grassSprite.setScale(tileScaleX, tileScaleY);
				window.draw(grassSprite);
			}
			// If the value is not 1, create a wall tile
			// Note, if you add additional tiles change this to reflect that
			else if (mapArray[i][j] == 1)
			{
				// Set the position of the wall tile to where it should be on the screen, and then scale it and draw it
				wallSprite.setPosition(i * 16 * tileScaleX, j * 16 * tileScaleY);
				wallSprite.setScale(tileScaleX, tileScaleY);
				window.draw(wallSprite);
			}
		}
	}
}
// Function to update the game
void update(float dt)
{
		//update and draw the player and tree
		player.update(dt);
		player.draw(window); 
		tree.drawTree(window);


		// Display the trees health above it
		treeHealthText.setString("Tree Health: " + std::to_string(tree.getHealth()));
		// Get the width of the text so that it can be centered
		float treeHealthTextWidth = treeHealthText.getLocalBounds().width;
		// Set the position of the text to be above the tree
		treeHealthText.setPosition(tree.getPosition().x - (treeHealthTextWidth / 6), tree.getPosition().y - 50);
		window.draw(treeHealthText);
		
		// Manage and display the second tree health text
		tree2HealthText.setString("Tree Health: " + std::to_string(tree2.getHealth()));
		float tree2HealthTextWidth = tree2HealthText.getLocalBounds().width;
		tree2HealthText.setPosition(tree2.getPosition().x - (tree2HealthTextWidth / 6), tree2.getPosition().y - 50);
		window.draw(tree2HealthText);
		
		// Update the timerText with the time since the game started
		timerText.setString("Time: " + std::to_string((int)timerClock.getElapsedTime().asSeconds()));
}
// Function to spawn enemies
void spawnEnemy(vector<unique_ptr<Enemy>>& enemies, const sf::Vector2f& treePos, int level) 
{
	// Get a random number to determine which corner to spawn the enemy in
	int corner = rand() % 2;
	int x, y;
	// If the corner is 0, spawn the enemy in the top left corner
	if (corner == 0) {
		x = 50;
		y = 50;
	}
	// Else spawn the enemy in the bottom right corner
	else {
		x = viewWidth-100;
		y = viewHeight-100;
	}
	// If the level is 2 spawn both types of enemies at random. else only spawn the blue enemies
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
// Function to create an attack when given the vector of attacks, the players position and the players direction
void createAttack(std::vector<unique_ptr<Attack>>& attacks, sf::Vector2f playerPosition, sf::Vector2f playerDirection) {
	// Set the speed of the attack
	float attackSpeed = 1000.f;

	// Create a new attack and add it to the vector
	//Attack newAttack(playerPosition.x, playerPosition.y, attackSpeed, playerDirection, "Graphics/attack.png");
	attacks.push_back(make_unique<Attack>(playerPosition.x, playerPosition.y, attackSpeed, playerDirection, "Graphics/attack.png"));
}

// Function to heal the trees at the cost of score.
void healTrees(sf::Vector2f tree1Pos, sf::Vector2f tree2Pos, sf::Vector2f playerPos)
{
	tree.healTree();
	tree2.healTree();
}


int main() {


	// Vector to store enemies
	vector<unique_ptr<Enemy>> enemies;
	
	// Vector to store attacks.
	vector<unique_ptr<Attack>> attacks;
	// Potental vector to allow for multiple trees
	//vector<unique_ptr<Tree>> trees;

	// Set the random seed so its actually random
	srand(time(NULL));

	// Variable to store the location of the trees
	sf::Vector2f tree1Pos = tree.getPosition();
	sf::Vector2f tree2Pos = tree2.getPosition();

	// Variable to manage game over if the tree drops to or below 0 hp
	bool gameOver = false;
	int level = 1;



	// Clock to manage the score
	sf::Clock scoreClock;
	// Initialize the game
	init();

	// Play the music
	gameMusic.play();

	// create the title screen
	titleScreen();

	// Reset the timer
	resetTimer();

	// Create a clock to manage dt
	sf::Clock clock;
	// Main game loop
	while (window.isOpen()) {
		// restart dt every frame to get the time since the last frame
		float dt = clock.restart().asSeconds();
		// Event, and check if the window is to be closed
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// If statement to display the game over window if the game is lost
		if (gameOver)
		{
			// Create the text for the game over
			sf::Text gameOverText;
			gameOverText.setCharacterSize(250);
			gameOverText.setFont(font);
			gameOverText.setString("Game Over");
			gameOverText.setFillColor(sf::Color::Red);
			textRect = gameOverText.getLocalBounds();
			// Set the game over text to the center of the screen
			gameOverText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
			gameOverText.setPosition(sf::Vector2f(viewWidth / 2.0f, viewHeight / 2.0f));
			// Draw a black rectangle behind the text to make it easier to read and to hide the game
			window.draw(blackRectangle);
			window.draw(gameOverText);
		}

		// If statement to check if the game is not yet lost
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

				// Code to prevent the escape key from being spammed and the window from flickering
				sf::sleep(sf::milliseconds(400));

			}
			// If the game is not paused, keep running the game
			if (paused != true)
			{
				// Spawn enemies every few seconds using a clock variable
				static sf::Clock spawnClock;
				if (spawnClock.getElapsedTime().asSeconds() >= 1.5f) {
					spawnEnemy(enemies, tree1Pos, level);
					spawnClock.restart();
				}
				// Clear the last frame from the window
				window.clear(sf::Color::Red);
				// Call the function to draw the map
				drawMap();

				// Call the update function
				update(dt);
		//score
				// Increase the score every second
				if (scoreClock.getElapsedTime().asSeconds() > 1)
				{
					score++;
					scoreClock.restart();
				}
				// Modify and draw the score text
				scoreText.setString("Score: " + std::to_string(score));
				window.draw(scoreText);


// Manage tree healing
				if (healClock.getElapsedTime().asSeconds() >= 30)
				{
					canHeal = true;
					healClock.restart();
				}
				// If the E button is pressed
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
				{
					// And if canHeal is true and the score is greater than 30
					if (canHeal && score >=30)
					{

							canHeal = false;
							healTrees(tree1Pos, tree2Pos, playerPosition);
							score -= 30;
						
					}
				}









				// Draw the timer
				window.draw(timerText);

				// if the level is two then draw the second tree
				if (level == 2)
				{
					tree2.drawTree(window);
				}


//LEVELS
				// If statement to check if the timer has reached a given time and to change the level
				if (level == 1 && timerClock.getElapsedTime().asSeconds() >= 45.0f) 
				{
					level = 2;
					// Reset the trees health
					tree.resetHealth();
					tree2.resetHealth();
					
					//clear the old enemies and attacks
					enemies.clear();
					attacks.clear();
				}
				// Make the changes as required for the second level
				if (level == 2)
				{
					// Set the first tree to the left bottom corner
					tree.setPosition(100, viewHeight - 150 - 72);
					// Set the second tree to the right top corner
					tree2.setPosition(viewWidth - 100 - 96, 100);
					// Get the updated positions
					tree1Pos = tree.getPosition();
					tree2Pos = tree2.getPosition();
				}
//Update and draw Enemies
				// Update and draw enemies
				for (auto& enemy : enemies) {
					// If the level is 2 then update the enemies with the positions of both trees in the overload update function for enemies
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
				// Itterate through the enemies vector
				for (auto enemyIterator = enemies.begin(); enemyIterator != enemies.end();) {
					bool enemyDestroyed = false;
					// Check colision with the first tree
					if (tree.treeSprite.getGlobalBounds().intersects((*enemyIterator)->getGlobalBounds())) {
						tree.takeDamage((*enemyIterator)->getDamage());

						if (tree.getHealth() <= 0) {
							// If the tree drops below 0 hp then set the gameOver bool to true
							gameOver = true;
							
							// Call update one last time
							update(dt);
							
						}
						// Set the bool to true to remove the enemy later in the code
						enemyDestroyed = true;
					}

					// Check Colision with the second tree
					if (tree2.treeSprite.getGlobalBounds().intersects((*enemyIterator)->getGlobalBounds())) {
						tree2.takeDamage((*enemyIterator)->getDamage());
						// If the tree drops below 0 hp then set the gameOver bool to true
						if (tree2.getHealth() <= 0) {
							// if the tree drops below 0 hp then set the gameOver bool to true
							gameOver = true;
							
							// Call update one last time
							update(dt);
							
						}

						enemyDestroyed = true;
					}
					
					// If the enemy is destroyed then remove it from the vector
					if (enemyDestroyed) {
						enemyIterator = enemies.erase(enemyIterator); // Remove the enemy
					}
					// If the enemy is not destroyed then increment the iterator and move on
					else {
						++enemyIterator;
					}
				}

//attack section
// 				// Attack cooldown in seconds
				float attackCooldown = 0.5f; 
				// if the player cannot attack and the cooldown has passed then set canAttack to true and restart the clock
				if (!canAttack && attackClock.getElapsedTime().asSeconds() >= attackCooldown)
				{
					canAttack = true;
					attackClock.restart();
				}

				// If the spacebar is pressed make an attack
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canAttack) 
				{
					// Get the players position and direction
					sf::Vector2f playerPos = player.getPosition();
					sf::Vector2f attackDirection = player.getFacingDirection();
					// feed the attack vector, player position and direction into the createAttack function
					createAttack(attacks, playerPos, attackDirection);
					// Set the can attack to false
					canAttack = false;
				}

				
				// Update and draw attacks
	// Vector 2f to store attack positions
				sf::Vector2f attackPosition;
				for (auto& attack : attacks)
				{
					attack->update(dt);
					attack->draw(window);

				}




				// manage player attack and its collision with enemies
				// Iterate through the attacks vector
				for (auto attackIterator = attacks.begin(); attackIterator != attacks.end();) {
					bool attackHit = false;
			
					for (auto enemyIterator = enemies.begin(); enemyIterator != enemies.end();) {
						bool enemyDestroyed = false;
						// Check if the attack has hit an enemy
						if ((*enemyIterator)->getGlobalBounds().intersects((*attackIterator)->attackSprite.getGlobalBounds())) {
							(*enemyIterator)->takeDamage();
							// if the enemy has dropped below 0 hp then set the enemyDestroyed bool to true
							// This is only for if I want to make some enemies have more than 1 hp
							if ((*enemyIterator)->getHealth() <= 0) {
								enemyDestroyed = true;
							}
							attackHit = true;
						}
						// If the enemy is destroyed then remove it from the vector
						if (enemyDestroyed) {
							enemyIterator = enemies.erase(enemyIterator);
						}
						else {
							++enemyIterator;
						}
					}
					// Check if the attack is out of bounds and delete it
					attackPosition = (*attackIterator)->getPosition();
					if (attackPosition.x >= viewWidth || attackPosition.y >= viewHeight || attackPosition.x <= 0 || attackPosition.y <= 0)
					{
						attackHit = true;
					}
					// If the attack has hit an enemy then remove it from the vector
					if (attackHit) {
						attackIterator = attacks.erase(attackIterator);
					}
					else {
						++attackIterator;
					}

				}




			}
			// This is for if the game is paused
			else
			{
				//display the paused text
				/*
				* Note. I took the inspiration for centering the text from this link
				* https://stackoverflow.com/questions/14505571/centering-text-on-the-screen-with-sfml
				*/
				// get the local bounds of the text
				textRect = pauseText.getLocalBounds();
				// Draw the black rectangle
				window.draw(blackRectangle);
				// Set the size of the text
				pauseText.setCharacterSize(250);
				// Set the origin of the text to the center of the text
				pauseText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				pauseText.setPosition(sf::Vector2f(viewWidth / 2.0f, viewHeight / 2.0f));

				//draw the text
				window.draw(pauseText);
			}
		}
		// display the window
		window.display();
	}
}
