#pragma once
#include <iostream>


/*****************************************
templated function of type void that takes
an array of type D, size, the starting
index, the ending index and the bool to check
if its in accending or decending order
to recursively divide and merge sort, the array

@param1 the array being sorted
@param2 the size of the array
@param3 the starting index (focused on)
@param4 the ending index (focused on)
@param5 the bool representing accending or
decsending with a default set to true
*****************************************/
template <class D>
void divideAndConquer(D* data, int size, int p, int r, bool accending = true)
{
	//the base case condition is if p is greater than or equal to r
	//meaning only 0 or 1 element is being looked at which is already sorted
	if (p >= r)
	{
		//returning from the function if the condition is true
		return;
	}
	//in the case there is more than 1 element in the array
	else
	{
		//finding the mid point of the array between p and r
		int q = (p + r) / 2;

		//recursively calling the function on the the first half of values to sort that half first
		divideAndConquer(data, size, p, q, accending);

		//recursively calling the function on the the second half of values to sort that half second
		divideAndConquer(data, size, q + 1, r, accending);

		//merging all the values together
		//the size of the array is the last index + 1 (r + 1)
		//the first index of the first sorted half (p)
		//the first index of the second sorted half (q + 1)
		mergeArray(data, r + 1, p, q + 1, accending);
	}

}


/*****************************************
templated function of type void that
takes an array a size, 2 indexes and a bool
representing is it has to be sorted in accending
or decending order to merge sorted halves
together by inserting the second half values
into the proper spot among the entire data set

@param1 the array of data
@param2 the size of the array
@param3 the index being compared
@param4 the start of the unsorted half
@param5 the bool representing accending or
decsending with a default set to true
*****************************************/
template <class T>

void mergeArray(T* data, int size, int i, int j, bool accending = true)
{


	/*using a while loop to complete comparisons as long as the index j doesnt go out
	of bounds and it doesnt equal the starting index i, in that case the data set is completely sorted*/
	while (j < size && j != i)
	{
		//checking if the value at j is less than the value at i if its supposed to be in accending order
		//OR, checking if the value at j is larger than the value at i if its supposed to be in descending order
		if ((accending && data[j] < data[i]) || (!accending && data[j] > data[i]))
		{
			//setting a temporary variable with the value at index j
			T temp = data[j];

			//using a for loop to move each element to the next index
			for (int move = j; move > i; move--)
			{
				//setting the current index value to the previous index value
				data[move] = data[move - 1];
			}

			//setting the value at the right index to the temp variable
			data[i] = temp;

			//increasing the index of i
			i++;

			//increasing the index of j
			j++;
		}
		else
		{
			//increasing the index of i
			i++;
		}

	}
}