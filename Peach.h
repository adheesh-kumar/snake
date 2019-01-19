#pragma once
#include "ICS_Sprite.h"			//including the sprite file
#include "Food.h"				//including food.h

/*
class peach which represents the regular food eaten by the snake which inherits from class food
*/
class Peach : public Food
{
//using a public access specifier
public:

	/*
	peach constructor
	@param1 the image of the peach
	@param2 the points a peach has
	*/
	Peach(ICS_Sprite sprite, int points)
		//intizalizing the food
		:
		Food(sprite, points)
	{
	}
};