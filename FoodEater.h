#pragma once
#include <iostream>
#include "ICS_Sprite.h"

class FoodEater
{
public:

	//directions
	const int UP = 0;
	const int RIGHT = 90;
	const int DOWN = 180;
	const int LEFT = 270;

	//size
	const int SIZE = 32;

	//to represent if the animal is dead or not
	bool _dead = false;

	//to represent the animals x and y position
	float _xPosition = 0;
	float _yPosition = 0;

	//the direction the animal is traveling in
	int _direction = 0;

	/*
	this function moves the snake north
	*/
	void northMove()
	{
		//sets direction to north
		_direction = UP;
	}

	/*
	sets direction to right
	*/
	void eastMove()
	{
		//sets direction to right
		_direction = RIGHT;
	}

	/*
	sets direction to south
	*/
	void southMove()
	{
		//sets direction to south
		_direction = DOWN;
	}

	/*
	sets direction to west
	*/
	void westMove()
	{
		//sets direction to left
		_direction = LEFT;
	}

	/*
	this function of type int returns the direction of the snake
	*/
	int getDirection()
	{
		//returning the direction
		return _direction;
	}

	void forwardMove()
	{
		//checking the direction of the snake//

		if (_direction == UP)
		{
			//moving the snake up
			_yPosition += SIZE;
		}
		if (_direction == RIGHT)
		{
			//moving the snake right
			_xPosition += SIZE;
		}
		if (_direction == DOWN)
		{
			//moving the snake down
			_yPosition -= SIZE;
		}
		if (_direction == LEFT)
		{
			//moving the snake left
			_xPosition -= SIZE;
		}
	}
};