#pragma once
#include <iostream>			//including iostream library
#include "Grid.h"			//including the grid
#include "Snake.h"			//including the snake
#include "ICS_Sprite.h"		//including the sprite file

using namespace std;		//using the standard namespace

/*
class food which gets eaten by the snake to generate player points and causes
the snake to grow when neccesary
*/
class Food
{
//public access specifier
public:

	//points from the food
	int _points = 0;

	//food image
	ICS_Sprite _food;

	//foods position
	float _XPosition;
	float _YPosition;

	/*
	food constructor which assigns values to 
	@param1 sprite to be used for food]
	@param2 number of points on that food
	*/
	Food(ICS_Sprite name, int points)
		//using an intialization list to set the points and image
		:
		_points(points),
		_food(name)
	{
	}

	/*
	this function of type bool finds out if the snake has hit the food and a
	new position for the food should be found
	@param1 snake
	@param 2 the goat
	*/
	bool placeNewFood(Snake& snake, bool& goatAte, float goatX = 0, float goatY = 0)
	{
		//checking if the snake hit the food
		if ((_XPosition == snake.snake[0].getXPosition()) && (_YPosition == snake.snake[0].getYPosition()))
		{
			goatAte = false;
			//returning true
			return true;
		}
		else if((_XPosition == goatX && _YPosition == goatY))
		{
			goatAte = true;
			//returning true if goat ate it
			return true;
		}
		else
		{
			goatAte = false;
			return false;
		}
	}

	/*
	this function of type void places the food on a random spot on the grid that isnt taken up by a snake
	@param1 the grid the snake is on
	@param2 the snake
	@param3 any other food currently out right now
	*/
	void randomFoodPlace(Grid& grid, Snake& snake, Food* food)
	{
		//bool to say if an appropiate spot was found or not
		bool placed = false;

		//using a while loop to keep searching for an appropiate spot
		while (!placed)
		{
			//generating a random number for the width
			int randomX = rand() % grid.WIDTH;
			int randomY = rand() % grid.HEIGHT;

			//setting that position generated on the grid
			randomX = (randomX * grid.cellXSize) + grid.absoluteLeft();
			randomY = (randomY * grid.cellYSize) + grid.absoluteBottom();

			//setting placed to true
			placed = true;

			//using a for loop to check if the food is in the right place
			for (int i = 0; i < snake.snake.getSize(); i++)
			{
				//checking if the position is valid 
				if ((snake.snake[i].getXPosition() == randomX && snake.snake[i].getYPosition() == randomY) || (food->getXPosition() == randomX && food->getYPosition() == randomY))
				{
					//if the position is invalid setting placed to false
					placed = false;
				}
			}

			//checking is placed is true and a spot has been found
			if (placed == true)
			{
				//setting the new positions
				_XPosition = randomX;
				_YPosition = randomY;
				_food.setPosition(_XPosition, _YPosition);
			}
		}

	}

	/*
	this fucntion of type void renders the food
	*/
	void renderFood()
	{
		//rendering the food
		_food.render();
	}

	/*
	this function of type float returns the foods x position
	*/
	float getXPosition()
	{
		//returning the xpos
		return _XPosition;
	}

	/*
	this function of type float returns the foods position
	*/
	float getYPosition()
	{
		//returning the ypos
		return _YPosition;
	}

	/*
	this function of type void sets the x pos
	@param1 the x pos
	*/
	void setXPosition(float x)
	{
		//setting x pos
		_XPosition = x;
	}

	/*
	this function of type void sets y pos
	@param1 y pos
	*/
	void setYPosition(float y)
	{
		//setting y pos
		_YPosition = y;
	}

	/*
	this function returns the points attained from the food
	*/
	int getPoints()
	{
		//returning points
		return _points;
	}
};