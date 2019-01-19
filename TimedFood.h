#pragma once
#include "ICS_Sprite.h"			//including the sprite library
#include "Food.h"				//including the food class


/*
class timed food which inherits from food and has its own special functions
*/
class TimedFood : public Food
{
//using a public access specifier
public:

	//const int representing when the next active timed food will be placed
	static const int MAX_COUNT = 8;

	//timer for the food
	float _timer;

	//checking if the timed food is active
	bool _active = false;

	/*
	timed food constructor
	@param1 the image to be used for the food
	@param2 the points the food gives
	@param3 the amount of time the food stays on
	*/
	TimedFood(ICS_Sprite sprite, int points, float timer)
		//using an initialization list to construct the default attribute
		:
		Food(sprite, points),
		_timer(timer),
		_active(false)
	{
	}

	/*
	this function of type bool checks if a timed food should be placed
	@param1 the counter to check if the next food should be placed
	*/
	virtual bool update(int& counter)
	{
		//checking if the counter has reached the max
		if (counter == MAX_COUNT)
		{
			//setting the count to 0
			counter = 0;

			//setting the food active to true
			_active = true;

			//returning true
			return true;
		}

		//returning false
		return false;
	}

	/*
	this function returns the active state of the food
	*/
	bool getActive()
	{
		//returning the active state
		return _active;
	}

	/*
	this fucntion sets the foods active status to false
	*/
	void setActiveFalse()
	{
		_active = false;
	}

	/*
	this function gets the time of the bird
	*/
	float timer()
	{
		//returning the timer
		return _timer;
	}
};