#pragma once
#include <iostream>
#include "FoodEater.h"			//including the food eater library
#include "Food.h"				//including the food header file

/*
class goat which inherits from food eater and food, the goat can eat other foods
but the snake can eat the goat hence, it also is a food
*/
class Goat : public FoodEater, public Food
{
//using a private access specifier
private:

	//const int the round where the goat appears
	const int ACTIVE_COUNT = 15;

	//the time the goat stays for
	const float TIME_PERIOD = 15;

	//the active status of the goat
	bool _active = false;

	//the random move directions
	const int RANDOM_MOVE = 4;

//using a public access specifier 
public:

	/*
	goat constructor which intializes the goat
	@param1 the image used for the goat
	@param2 the points a goat has
	*/
	Goat(ICS_Sprite name, int points)
		:
		//constructing the food aspect
		Food(name, points),
		//setting active to false
		_active(false)
	{
	}

	/*
	the goats random place
	@param1 the grid
	@param2 the snake
	@param3 the food
	*/
	void goatRandomPlace(Grid& grid, Snake& snake, Food* food)
	{
		//calling the random food place
		Food::randomFoodPlace(grid, snake, food);
	}

	/*
	the goats move function which moves the goat in any direction however
	not out of bounds and not into the snake
	@param1 the grid
	@param2 the snake
	*/
	void goatMove(Grid& grid, Snake& snake)
	{
		//a bool to represent if there is space or not
		bool space = false;

		//a bool to represent if the goat can move or not
		bool moveAble = true;

		//setting the goats food x and y position to the food eater x and y
		_xPosition = _XPosition;
		_yPosition = _YPosition;

		//setting 2 new variables to represent the x and y position
		int moveX = _xPosition;
		int moveY = _yPosition;

		//using a while loop to find a place for the goat while a space wasnt found, and the goat is still able to move
		while (!space && moveAble)
		{
			//random move direction
			int randomMove = rand() % RANDOM_MOVE;

			//checking each direction
			float moveUp = moveY + SIZE;
			float moveRight = moveX + SIZE;
			float moveDown = moveY - SIZE;
			float moveLeft = moveX - SIZE;

			//checking if each space is available, setting it true unless proven otherwise
			bool canMoveUp = true;
			bool canMoveRight = true;
			bool canMoveDown = true;
			bool canMoveLeft = true;

			//using a for loop to check if the goat can move, or is its trapped by the snake
			for (int i = 0; i < snake.snake.getSize(); i++)
			{
				//chceking is the snake can move up
				if (moveX == snake.snake[i].getXPosition() && moveUp == snake.snake[i].getYPosition())
				{
					//if a snake is there setting move up to false
					canMoveUp = false;
				}
				//chceking is the snake can move right
				if (moveRight == snake.snake[i].getXPosition() && moveY == snake.snake[i].getYPosition())
				{
					//if a snake is there setting move right to false
					canMoveRight = false;
				}
				//chceking is the snake can move down
				if (moveX == snake.snake[i].getXPosition() && moveDown == snake.snake[i].getYPosition())
				{
					//if a snake is there setting move down to false
					canMoveDown = false;
				}
				//chceking is the snake can move left
				if (moveLeft == snake.snake[i].getXPosition() && moveY == snake.snake[i].getYPosition())
				{
					//if a snake is there setting move down to false
					canMoveLeft = false;
				}
			}

			// checking if the position would be out of bounds for the top of grid
			if (moveUp == grid.absoluteTop() + SIZE)
			{
				//setting move up to false
				canMoveUp = false;
			}
			// checking if the position would be out of bounds for the right of grid
			if (moveRight == grid.absoluteRight() + SIZE)
			{
				//setting move right to false
				canMoveRight = false;
			}
			// checking if the position would be out of bounds for the bottom of grid
			if (moveDown == grid.absoluteBottom() - SIZE)
			{
				//setting move down to false
				canMoveDown = false;
			}
			// checking if the position would be out of bounds for the left of grid
			if (moveLeft == grid.absoluteLeft() - SIZE)
			{
				//setting move left to false
				canMoveLeft = false;
			}

			//checking if the goat can move at all
			if (!canMoveUp && !canMoveRight && !canMoveDown && !canMoveLeft)
			{
				//if it cannot move at all, setting moveable to false
				moveAble = false;
			}

			//checking if the random move is up and it can move up
			if (randomMove == 0 && canMoveUp)
			{
				//setting space to true
				space = true;
				//setting the direction to up
				_direction = UP;
			}
			//checking if the random move is right and it can move right
			if (randomMove == 1 && canMoveRight)
			{
				//setting space to true
				space = true;
				//setting the direction to right
				_direction = RIGHT;
			}
			//checking if the random move is down and it can move down
			if (randomMove == 2 && canMoveDown)
			{
				//setting space to true
				space = true;
				//setting the direction to down
				_direction = DOWN;
			}
			//checking if the random move is left and it can move left
			if (randomMove == 3 && canMoveLeft)
			{
				//setting space to true
				space = true;
				//setting the direction to left
				_direction = LEFT;
			}

			//checking if there is space and it is moveable
			if (space && moveAble)
			{
				//moving forward by calling the forward move function
				FoodEater::forwardMove();

				//changing the food goat position to the foodeater goat position
				_XPosition = _xPosition;
				_YPosition = _yPosition;

				//setting the foods position
				_food.setPosition(_XPosition, _YPosition);
			}
			
		}
	}

	/*
	this function of type bool checks if the goat is ready to become active
	@param1 the turn count of the player
	*/
	bool update(int& count)
	{
		//checking if the goat is ready is to be set active
		if (count == ACTIVE_COUNT)
		{
			//setting active to true
			_active = true;

			//setting the player count to 0
			count = 0;

			//returning true
			return true;
		}

		//otherwise returning false
		return false;

	}

	/*
	this function of type bool gets the goats, active status
	*/
	bool getActive()
	{
		//returning active
		return _active;
	}

	/*
	this function sets the goats active status
	*/
	void setActive(bool active)
	{
		//setting active to the bool variable
		_active = active;
	}

	/*
	this function of type float returns the goat timer
	*/
	float getTimer()
	{
		//returning the timer
		return TIME_PERIOD;
	}
};