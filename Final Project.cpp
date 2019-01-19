#include <iostream>				// for string, cin, cout and endl
#include <glut.h>				// the library for glut (OpenGL)
#include "Snake.h"				//including the snake file
#include "Grid.h"				//including the grid file
#include "Peach.h"				//including the peachfile
#include "TimedFood.h"			//including the timed food
#include "Goat.h"				//including the goat file
#include "ICS_Game.h"			// for the simple game framework
#include "ICS_Sprite.h"			//including the sprite file
#include "ICS_TextRenderer.h"	//including the text renderer file
#include "ICS_Helpers.h"		//including the ics helper file
#include <fstream>

//////////////////////constants//////////////////////////////

const int WINDOW_WIDTH = 800;	// the width of the game window (in pixels)
const int WINDOW_HEIGHT = 600;	// the height of the game window (in pixels)

//x and y displacement for grid
const float GRID_X_DISPLACEMENT = 200;
const float GRID_Y_DISPLACEMENT = 130;

//snake directions
const int SNAKE_UP_DIRECTION = 0;
const int SNAKE_RIGHT_DIRECTION = 90;
const int SNAKE_DOWN_DIRECTION = 180;
const int SNAKE_LEFT_DIRECTION = 270;

//start direction of snake
const int START_DIRECTION = SNAKE_RIGHT_DIRECTION;

//size of text on screen
const int POINTS_SIZE = 18;
const int GAME_OVER_SIZE = 50;

//points text displacement
const float POINTS_TEXT_X_DISPLACEMENT = 12;
const float POINTS_TEXT_Y_DISPLACEMENT = 12;

//highscore text displacement
const float HIGHSCORE_TEXT_X_DISPLACEMENT = 12;
const float HIGHSCORE_TEXT_Y_DISPLACEMENT = 30;

//game over text displacement
const float GAMEOVER_TEXT_X_DISPLACEMENT = 275;
const float GAMEOVER_TEXT_Y_DISPLACEMENT = 300;

//offset for game over background
const float GAMEOVER_BACKGROUND_OFFSET = 45;

//background height and width
const float GAMEOVER_BACKGROUND_HEIGHT = 134;
const float GAMEOVER_BACKGROUND_WIDTH = 333;

//points for each piece of food
const int PEACH_POINTS = 25;
const int TIMED_FOOD_POINTS = 75;
const int GOAT_POINTS = 500;

//time that timed food lasts
const float TIMED_FOOD_TIME = 1.5;

//////////////////////variables/////////////////////////////

//checking if a key press
bool keyPress = true;

//creating the grid
Grid grid(GRID_X_DISPLACEMENT, GRID_Y_DISPLACEMENT);

//creating the snake
Snake snake(START_DIRECTION, grid);

//decalring all images
ICS_Sprite peach = "data/peach.png";
ICS_Sprite bird = "data/bird.png";
ICS_Sprite mouse = "data/mouse.png";
ICS_Sprite goatMan = "data/goat.png";
ICS_Sprite gameOverBackground = "data/gameover.png";

//declaring text prints
ICS_TextRenderer points(POINTS_SIZE, "consolas");
ICS_TextRenderer highScore(POINTS_SIZE, "consolas");
ICS_TextRenderer gameOverPrint(GAME_OVER_SIZE, "consolas");

//declaring all foods
Peach* food = new Peach(peach, PEACH_POINTS);

//array of timed foods
SuperArray<TimedFood*> timedFood;

//timed foods
TimedFood* birdFood = new TimedFood(bird, TIMED_FOOD_POINTS, TIMED_FOOD_TIME);
TimedFood* mouseFood = new TimedFood(mouse, TIMED_FOOD_POINTS, TIMED_FOOD_TIME);

//goat character
Goat goat(goatMan, GOAT_POINTS);

//to switch indexes in timed food array
int timeFoodSwitch = 0;

//current highscore
int currentHighScore = 0;

//to store x and y pos of eaten foods
SuperArray<float> XPositionOfEaten;
SuperArray<float> YPositionOfEaten;

//update timer
float timer = 0;

//timed food timer
float timedFoodTimer = 0;

//goat timer
float goatTimer = 0;

//players score
int playerScore = 0;

//count for timed food
int counter = 0;

//count for goat
int goatCount = 0;

//bool to represent if game is over
bool gameOver = false;

//bool to represent goat if ate food
bool goatAte = false;

/*
this function of type void handles a peach food turn making sure 
that all possibilities are accounted for
*/
void handlePeachFoodTurn()
{
	//checking if a new food should be place
	if (food->placeNewFood(snake, goatAte, goat.getXPosition(), goat.getYPosition()))
	{
		//as long as goat didnt eat it
		if (!goatAte)
		{
			//storing x and y position to grow later
			XPositionOfEaten.pushBack(food->getXPosition());
			YPositionOfEaten.pushBack(food->getYPosition());

			//adding points
			playerScore += food->_points;
		}
		
		//setting goatAte back to default false
		goatAte = false;

		//randomly placing a new peach
		food->randomFoodPlace(grid, snake, timedFood[timeFoodSwitch]);

		//increasing counters
		counter++;
		goatCount++;
	}
}

/*
this function of type void handles all timed food turns, acccounting for
all possible occurences with a timed food
*/
void handleTimedFoodTurn()
{
	//checking if the timed food has run out of time
	if (timedFood[timeFoodSwitch]->getActive() && timedFoodTimer >= timedFood[timeFoodSwitch]->timer())
	{
		//setting it to not active
		timedFood[timeFoodSwitch]->setActiveFalse();

		//setting x and y to default pos
		timedFood[timeFoodSwitch]->setXPosition(0);
		timedFood[timeFoodSwitch]->setYPosition(0);

		//setting timer back to 0
		timedFoodTimer = 0;

		//switching index for timed food
		if (timeFoodSwitch == 0)
		{
			//moving to next index
			timeFoodSwitch = 1;
		}
		else
		{
			//moving back to 0
			timeFoodSwitch = 0;
		}
	}

	// checking if a timed food should be place
	if (timedFood[timeFoodSwitch]->update(counter))
	{
		//randomly placing a new timed food
		timedFood[timeFoodSwitch]->randomFoodPlace(grid, snake, food);
	}

	//checking if a timed food is active and has been eaten
	if ((timedFood[timeFoodSwitch]->getActive() && timedFood[timeFoodSwitch]->placeNewFood(snake, goatAte, goat.getXPosition(), goat.getYPosition())))
	{
		//as long as goat hasnt eaten it
		if (!goatAte)
		{
			//storing x and y pos
			XPositionOfEaten.pushBack(timedFood[timeFoodSwitch]->getXPosition());
			YPositionOfEaten.pushBack(timedFood[timeFoodSwitch]->getYPosition());

			//adding to player score
			playerScore += timedFood[timeFoodSwitch]->getPoints();
		}

		//setting goatAte to false
		goatAte = false;

		//setting timedfood to inactive
		timedFood[timeFoodSwitch]->setActiveFalse();

		//setting default position
		timedFood[timeFoodSwitch]->setXPosition(0);
		timedFood[timeFoodSwitch]->setYPosition(0);

		//reseting timed food timer
		timedFoodTimer = 0; 

		//switcing to next index
		if (timeFoodSwitch == 0)
		{
			//switching to 2nd index
			timeFoodSwitch = 1;
		}
		else
		{
			//switiching to first index
			timeFoodSwitch = 0;
		}
	}
}

/*
this function of type void handles a goat turn accounting for all possible outcomes
*/
void handleGoatTurn()
{
	//checking if the goat is ready to be active
	if (goat.update(goatCount))
	{
		//placing the goat on a random place
		goat.goatRandomPlace(grid, snake, food);
	}

	//checking if the goat timer is expired
	if (goatTimer >= goat.getTimer())
	{
		//setting goat to false
		goat.setActive(false);

		//setting pos to default
		goat.setXPosition(0);
		goat.setYPosition(0);

		//resetting the goat timer
		goatTimer = 0;
	}

	//checking if goat should move
	if (goat.getActive())
	{
		//moving the goat
		goat.goatMove(grid, snake);
	}

	//chekcing if the goat has been eaten
	if (goat.placeNewFood(snake, goatAte))
	{
		//as long as its not on the same spot
		if(!goatAte)
		{
			//storing goat info
			XPositionOfEaten.pushBack(goat.getXPosition());
			YPositionOfEaten.pushBack(goat.getYPosition());

			//adding to player score
			playerScore += goat.getPoints();
		}

		//setting default goat pos
		goat.setXPosition(0);
		goat.setYPosition(0);

		//setting active to false
		goat.setActive(false);
	}
}

/**
 * This initializes the program.
 */
void handleInitializeEvent()
{
	//inserting timed foods into array of timed foods
	timedFood.pushBack(birdFood);
	timedFood.pushBack(mouseFood);

	//setting text for the screen
	points.setText("Points: " + intToString(playerScore));

	//setting points position to bottom corner
	points.setXPosition(POINTS_TEXT_X_DISPLACEMENT);
	points.setYPosition(POINTS_TEXT_Y_DISPLACEMENT);

	//setting highscore to poistion right above points
	highScore.setXPosition(HIGHSCORE_TEXT_X_DISPLACEMENT);
	highScore.setYPosition(HIGHSCORE_TEXT_Y_DISPLACEMENT);

	//checking if a highscore is present
	ifstream inFile("data.txt");
	if (inFile.is_open())
	{
		//delcaring a string to read the highscore amount
		string highScoreAmount = "";

		//checking if there is a highscore
		if (getline(inFile, highScoreAmount))
		{
			//setting the current highscore to the file highscore
			currentHighScore = atoi(highScoreAmount.c_str());

			//setting the text for the highscore
			highScore.setText("High Score: " + highScoreAmount);
		}
	}

	//setting defaults for the goat
	goat.setActive(false);
	goat.setXPosition(0);
	goat.setYPosition(0);

	//setting game over text box
	gameOverPrint.setPosition(GAMEOVER_TEXT_X_DISPLACEMENT, GAMEOVER_TEXT_Y_DISPLACEMENT);

	//setting text
	gameOverPrint.setText("GAME OVER");

	//setting background pos
	gameOverBackground.setPosition(gameOverPrint.getXPosition() - GAMEOVER_BACKGROUND_OFFSET, gameOverPrint.getYPosition() - GAMEOVER_BACKGROUND_OFFSET);

	//setting height and length of background
	gameOverBackground.setWidth(GAMEOVER_BACKGROUND_WIDTH);
	gameOverBackground.setHeight(GAMEOVER_BACKGROUND_HEIGHT);

	//randomly placing a food on the grid
	food->randomFoodPlace(grid, snake, timedFood[timeFoodSwitch]);
}

/**
 * This updates the game logic.
 *
 * @param elapsed	The number of seconds that have elapsed since the last update.
 */
void handleUpdateEvent(float elapsed)
{
	//checking if the snake is still alive
	if (!snake.deadCheck(grid))
	{
		//checking if an update should occur
		if (timer >= 0.15)
		{
			//moving the snake forward
			snake.forwardMove();

			//handling a goat turn
			handleGoatTurn();

			//handling a timed food turn
			handleTimedFoodTurn();

			//handling a peach food turn
			handlePeachFoodTurn();

			//checking for foods that were eaten by the snake
			for (int i = 0; i < XPositionOfEaten.getSize(); i++)
			{
				//checking if the snake should grow at this time
				if (snake.growSnake(XPositionOfEaten[i], YPositionOfEaten[i]))
				{
					//removing the x and y pos from the array
					XPositionOfEaten.remove(i);
					YPositionOfEaten.remove(i);

					//moving down an index to check for the next x y pos
					i--;
				}
			}

			//setting key press to true
			keyPress = true;

			//retsetting the timer
			timer = 0;
		}

		//adding to the timer
		timer += elapsed;

		//adding to the timed food timer
		if (timedFood[timeFoodSwitch]->getActive())
		{
			//adding
			timedFoodTimer += elapsed;
		}

		//adding to the goat timer
		if (goat.getActive())
		{
			//adding the timer
			goatTimer += elapsed;
		}

		//resetting the updated point count
		points.setText("Points: " + intToString(playerScore));
	}
	//incase the snake is dead
	else if(snake.deadCheck(grid))
	{
		//setting any tied foods or goats to inactive
		timedFood[timeFoodSwitch]->setActiveFalse();
		goat.setActive(false);

		//checking if the new score is larger than the previous
		if (playerScore > currentHighScore)
		{
			//setting a new highscore
			currentHighScore = playerScore;

			//setting the text for the new highscore
			highScore.setText("High Score: " + intToString(currentHighScore));
		}

		//setting game over to true
		gameOver = true;
	}
}

/**
 * This renders 2D game element
 s.
 */
void handleRender2DEvent()
{
	//redering highscore
	highScore.render();

	//rendering points
	points.render();

	//rendering the grid
	grid.gridRender();

	//rendering the food
	food->renderFood();

	//if the goat is actove
	if (goat.getActive())
	{
		//render the goat
		goat.renderFood();
	}

	//if the timed food is active
	if (timedFood[timeFoodSwitch]->getActive())
	{
		//render the food
		timedFood[timeFoodSwitch]->renderFood();
	}

	//is the snake is alive
	if (!snake.deadCheck(grid))
	{
		//render the snake
		snake.renderSnake();
	}

	//if the game is over
	if (gameOver)
	{
		//render the background
		gameOverBackground.render();

		//render the text
		gameOverPrint.render();
	}
}

/**
* This renders 3D game elements.
*/
void handleRender3DEvent()
{
}

/**
 * This handles mouse move events.
 *
 * @param x		The x position of the mouse cursor.
 * @param y		The y position of the mouse cursor.
 */
void handleMouseMoveEvent(int x, int y)
{
}

/**
 * This handles mouse left click events.
 *
 * @param x		The x position of the mouse cursor.
 * @param y		The y position of the mouse cursor.
 * @param down	true if the mouse button went down, false it it was released.
 */
void handleMouseLeftClickEvent(int x, int y, bool down)
{
}

/**
* This handles mouse right click events.
*
* @param x		The x position of the mouse cursor.
* @param y		The y position of the mouse cursor.
* @param down	true if the mouse button went down, false it it was released.
*/
void handleMouseRightClickEvent(int x, int y, bool down)
{
}

/**
 * This handles mouse wheel events.
 *
 * @param x			The x position of the mouse cursor.
 * @param y			The y position of the mouse cursor.
 * @param rotation	The wheel rotation value.  A positive value indicates that the wheel was rotated forward, away
 *					from the user; a negative value indicates that the wheel was rotated backward, toward the user. 
 */
void handleMouseWheelEvent(int x, int y, int rotation)
{
}

/**
 * This handles keyboard events.
 *
 * @param key	The id of the key that was pressed / released.
 *				Windows virtual key codes can found here:
 *				https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
 * @param down	Indicates the key was pressed (if down is true) or the key was released (if down is false)
 */
void handleKeyboardEvent(int key, bool down)
{
	//checking if a key was pressed
	if (down)
	{
		//checking if a key press is allowed to be made and the snake isnt dead
		if (keyPress == true && !snake.deadCheck(grid))
		{
			//checking the up key
			if (key == VK_UP)
			{
				//making sure it doesnt go back on itself
				if (snake.getDirection() != SNAKE_DOWN_DIRECTION)
				{
					//moving north
					snake.northMove();

					//setting a key press to false
					keyPress = false;
				}
			}

			//checking the right key
			if (key == VK_RIGHT)
			{
				//making sure it doesnt go back on itself
				if (snake.getDirection() != SNAKE_LEFT_DIRECTION)
				{
					//moving east
					snake.eastMove();

					//setting keypress to false
					keyPress = false;
				}
			}

			//chekcing if down key was pressed
			if (key == VK_DOWN)
			{
				//making sure it doesnt go back on itself
				if (snake.getDirection() != SNAKE_UP_DIRECTION)
				{
					//moving snake south
					snake.southMove();

					//setting key press to false
					keyPress = false;
				}
			}

			//checking if left key was pressed
			if (key == VK_LEFT)
			{
				//making sure it doesnt go back on itself
				if (snake.getDirection() != SNAKE_RIGHT_DIRECTION)
				{
					//moving west
					snake.westMove();

					//setting key press to false
					keyPress = false;
				}
			}
		}

		//checking if the snake is dead
		if (snake.deadCheck(grid))
		{
			//checking if space bar was pressed
			if (key == VK_SPACE)
			{
				//resetting all game elements//

				//score
				playerScore = 0;

				//game restart
				gameOver = false;

				//counters
				counter = 0;
				goatCount = 0;

				//reintializing snake
				snake.intializeAndReset(START_DIRECTION, grid);
			}
		}

	}
}
/**
* The callback for handling exiting the program.
*/
void handleExitEvent()
{
	//declaring an ofstream outfile
	ofstream outFile("data.txt");

	//checking if it is open
	if (outFile.is_open())
	{
		//printing out the current highscore
		outFile << currentHighScore << endl;
	}
}

/**
 * This is the entry point to the program.
 *
 * @param hInstance			A handle to the current instance of the application.
 * @param hPrevInstance		A handle to the previous instance of the application.
 * @param lpCmdLine			The command line for the application, excluding the program name.
 * @param nCmdShow			Controls how the window will be shown.
 *
 * @returns					If the function succeeds, terminating when it receives a WM_QUIT message, it should return the exit value contained
 *							in that message's wParam parameter.  If the function terminates before entering the message loop, it should return zero.
 */
#ifdef _DEBUG
int main()


#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif
{
	//seeding the random number genorator
	srand((unsigned)time(NULL));

	// create the game and set the callbacks
	ICS_Game::getInstance().setInitializeEventCallback(handleInitializeEvent);				// set the callback for initializing the program
	ICS_Game::getInstance().setUpdateEventCallback(handleUpdateEvent);						// set the callback for updating game logic
	ICS_Game::getInstance().setRender2DEventCallback(handleRender2DEvent);					// set the callback for rendering 2D game elements
	ICS_Game::getInstance().setRender3DEventCallback(handleRender3DEvent);					// set the callback for rendering 3D game elements
	ICS_Game::getInstance().setMouseMoveEventCallback(handleMouseMoveEvent);				// set the callback for handling mouse move events
	ICS_Game::getInstance().setMouseLeftClickEventCallback(handleMouseLeftClickEvent);		// set the callback for handling mouse left click events
	ICS_Game::getInstance().setMouseRightClickEventCallback(handleMouseRightClickEvent);	// set the callback for handling mouse right click events
	ICS_Game::getInstance().setMouseWheelEventCallback(handleMouseWheelEvent);				// set the callback for handling mouse wheel events
	ICS_Game::getInstance().setKeyboardEventCallback(handleKeyboardEvent);					// set the callback for handling keyboard events
	ICS_Game::getInstance().setExitEventCallback(handleExitEvent);							// set the callback for exiting the program

	// start the game... the program ends when this function returns (when the game loop ends)
	return ICS_Game::getInstance().go("Final Project", WINDOW_WIDTH, WINDOW_HEIGHT);
}
