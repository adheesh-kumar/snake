#pragma once
#include <iostream>			//including the iostream lib
#include <time.h>			//including time.h
#include "SuperArray.h"		//including superarray
#include "ICS_Sprite.h"		//including sprite file
#include "Grid.h"			//including grid
#include "FoodEater.h"

using namespace std;		//using standard namespace

/*
class called snake which represents the snake in the game
*/
class Snake: public FoodEater
{

//using a public access specifier
public:

	//starting num of snake
	const int STARTING_NUM_OF_SNAKE = 4;

	//an array of sprites for the snake
	SuperArray<ICS_Sprite> snake;

	/*
	snake constructor wich intializes the snake at a certain point on the screen
	@param1 the starting direction of the snake
	@param2 the grid the snake is moving on
	*/
	Snake(int startDirection, Grid grid)
	{
		//calling the intialize and reset function
		intializeAndReset(startDirection, grid);
	}

	/*
	this fucntion of type void intializes the snake when neccesary
	@param1 the starting direction
	@param2 the grid the snake is moving on
	*/
	void intializeAndReset(int startDirection, Grid& grid)
	{
		//index to remove all existing snake pieces
		int index = snake.getSize() - 1;

		//uing a while loop to remove each part of the snake
		while (index >= 0)
		{
			//removeing the snake
			snake.remove(index);
			
			//decreasing the index
			index--;
		}

		//setting the x and y coordinates of the first snake part to the corner of the grid
		_xPosition = grid.absoluteLeft() + (SIZE * STARTING_NUM_OF_SNAKE);
		_yPosition = grid.absoluteBottom();

		//setting the direction
		_direction = startDirection;

		//making a snakebody sprite
		ICS_Sprite snakeBody("data/snakebody.png", SIZE, SIZE);

		//adding a snake part into the body 4 times
		for (int i = 0; i < STARTING_NUM_OF_SNAKE; i++)
		{
			//adding a snake into the array
			snake.pushBack(snakeBody);

			//setting each snake next to the first one
			snake[i].setPosition(_xPosition - (SIZE * i), _yPosition);
		}

		//setting the snake to alive
		_dead = false;
	}

	/*
	this function renders each snake part
	*/
	void renderSnake()
	{
		//using a for loop to go through each snake part
		for (int i = 0; i < snake.getSize(); i++)
		{
			//rendering the snake part
			snake[i].render();
		}
	}

	/*
	this function of type bool checks if the snake has done something to be die
	@param1 the grid on the snake is supposed to stay in
	*/
	bool deadCheck(Grid& grid)
	{
		//checking if the snake is in boundaries
		if (_xPosition < grid.absoluteLeft() || _xPosition > grid.absoluteRight() || _yPosition < grid.absoluteBottom() || _yPosition > grid.absoluteTop())
		{
			//setting dead to true
			_dead = true;

			//returning the snakes death status
			return _dead;
		}

		//using a for loop to check is the first snake body part hits any of the other body parts
		for (int i = 1; i < snake.getSize(); i++)
		{
			//checking snake on snake collision
			if (snake[0].getXPosition() == snake[i].getXPosition() && snake[0].getYPosition() == snake[i].getYPosition())
			{
				//setting dead to true
				_dead = true;

				//returning snakes dead status
				return _dead;
			}
		}

		//if neither of these scenarios killed the snake, keeping the snake alive
		_dead = false;

		//returning snakes death status
		return _dead;

	}

	/*
	this function of type void moves the snake forward
	*/
	void forwardMove()
	{
		
		FoodEater::forwardMove(); 

		//moving the snake to the position of the one before it
		for (int i = snake.getSize() - 1; i > 0; i--)
		{
			//setting each snake position to the one before it
			snake[i].setPosition(snake[i - 1].getXPosition(), snake[i - 1].getYPosition());
		}

		//setting the head of the snake to the new position
		snake[0].setPosition(_xPosition, _yPosition);
	}

	/*
	this function of type bool returns if the snake is supposed to grow or not
	@param1 the x position of the food
	@param2 the y position of the food
	*/
	bool growSnake(float XPosition, float YPosition)
	{
		//checking if the last part of the snake is on the food
		if (XPosition == snake[snake.getSize() - 1].getXPosition() && YPosition == snake[snake.getSize() - 1].getYPosition())
		{
			//creating a new sprite for the snake
			ICS_Sprite snakeBody("data/snakebody.png", SIZE, SIZE);

			//adding a snake to the end of the body
			snake.pushBack(snakeBody);

			//setting the new snake to the position of the previous one
			snake[snake.getSize() - 1].setPosition(snake[snake.getSize() - 2].getXPosition(), snake[snake.getSize() - 2].getYPosition());

			//returning true
			return true;
		}

		//returning false if no food found
		return false;

	}

	//snake destructor
	~Snake()
	{
		//starting the index at the last element of the array
		int index = snake.getSize() - 1;

		//using a while loop to remove the snake at the index
		while (index >= 0)
		{
			//removing the snake part
			snake.remove(index);

			//lowering the index
			index--;
		}
	}
};