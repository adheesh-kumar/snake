#pragma once
#include <iostream>				//including the iostream library
#include "SuperArray.h"			//including the super array file
#include "ICS_Sprite.h"			//including the sprite library

/*
class grid which represent the map the snake is supposed to travel on
*/
class Grid
{
//public access specifier
public:

	//const height and width of the grid
	static const int WIDTH = 12;
	static const int HEIGHT = 12;

	//size of grid cell
	float cellXSize = 32;
	float cellYSize = 32;

	//the x and y displacement
	float XDisplacement = 0;
	float YDisplacement = 0;

	//the grid being displayed
	ICS_Sprite displayGrid[HEIGHT][12];

	/*
	constructor for the grid
	*/
	Grid(float x, float y)
		//using an intialization list to set the grid characteristics
		:
		XDisplacement(x),
		YDisplacement(y)
	{
		//creating a grid piece 
		ICS_Sprite gridPiece = "data/grid.png";

		//new line starts at the xdisplacement
		int newLineDisplacement = XDisplacement;

		//using a for loop to go through each column of the grid
		for (int i = 0; i < HEIGHT; i++)
		{
			//new row displacement starts at the y displacement
			int rowCountDisplacement = YDisplacement;

			//using a for loop to go through each row of the grid
			for (int j = 0; j < WIDTH; j++)
			{
				//setting the grid piece to the row
				displayGrid[i][j] = gridPiece;

				//setting its position to the proper position
				displayGrid[i][j].setPosition(newLineDisplacement, rowCountDisplacement);

				//setting the x position to the next cell
				rowCountDisplacement += cellXSize;
			}

			//moving the line up
			newLineDisplacement += cellYSize;

		}
	}

	/*
	this function of type void renders the grid
	*/
	void gridRender()
	{
		//using a for loop to go through each column
		for (int i = 0; i < HEIGHT; i++)
		{
			//using a for loop to go through each row
			for (int j = 0; j < WIDTH; j++)
			{
				//rendering each cell
				displayGrid[i][j].render();
			}
		}
	}

	/*
	this function returns the absolute left of the grid
	*/
	float absoluteLeft()
	{
		//returning the xDisplacement
		return XDisplacement;
	}

	/*
	this function returns the absolute right of the grid
	*/
	float absoluteRight()
	{
		//returning the right of the grid
		return (XDisplacement + (WIDTH * cellXSize) - cellXSize);
	}

	/*
	this function returns the absolute bottom of the grid
	*/
	float absoluteBottom()
	{
		//returning the y displacement
		return YDisplacement;
	}

	/*
	this function returns the top of the grid
	*/
	float absoluteTop()
	{
		//returning the top of the grid
		return (YDisplacement + (HEIGHT * cellYSize) - cellYSize);
	}
};