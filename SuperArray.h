#pragma once				//to include this header file once
#include "Sort.h"			//including the sorting file

// declaring a constant default size array
const int MAXIMUM_NUMBER_OF_ELEMENTS_DEFAULT = 1;

/*
this templated class represents and array of any type
with multiple functions that can change the array
*/
template <typename T>
class SuperArray
{

//private attributes and functions
private:

	//dynamically allocation an array of type T
	T* _array = NULL;

	//the current number of elements stored in the array
	int _currentNumOfElements = 0;

	//the maximum size of the array
	int _maxNumOfElements;

	//a dummy variable of type T to return in case of errors
	T _dummy;

	/*
	This function of type void doubles the size of the array
	*/
	void grow()
	{
		//doubling the maximum number of elements 
		_maxNumOfElements *= 2;

		//dynamically allocating a new temporary array with double the size of the original
		T* temp = new T[_maxNumOfElements];
		
		//copying the elements from the original array to the new one
		for (int i = 0; i < _currentNumOfElements; i++)
		{
			temp[i] = _array[i];
		}
		
		//deleting the original array
		delete[] _array;

		//pointing the original pointer to the memory address of the new array
		_array = temp;
	}

//public functions
public:

	//default constructor allocating the default max number of elements
	SuperArray()

		//using an initialization list to set values to attributes
		:
		_maxNumOfElements(MAXIMUM_NUMBER_OF_ELEMENTS_DEFAULT),
		_currentNumOfElements(0)
	{
		//allocationg memory for the array 
		_array = new T[_maxNumOfElements];
	}

	//copy constructor which takes an instance of superarray as input
	SuperArray(const SuperArray& instance)

		//using an intialization list to copy max and current attributes
		:
		_maxNumOfElements(instance._maxNumOfElements),
		_currentNumOfElements(instance._currentNumOfElements)
	{
		_array = new T[_maxNumOfElements];

		//using a for loop to cop all elements from the instance array to the current one
		for (int i = 0; i < _currentNumOfElements; i++)
		{
			_array[i] = instance._array[i];
		}
	}

	//destructor
	~SuperArray()
	{
		//setting the num of element to 0
		_currentNumOfElements = 0;

		//deleting the array
		delete[] _array;
		//setting it to a null pointer
		_array = NULL;
	}

	/*
	get size function which returns the current size of the array
	*/
	int getSize() const
	{
		//returning the current size
		return _currentNumOfElements;
	}

	/*
	[] operator function 
	@param1 index to get
	*/
	T& operator[](int index)
	{
		//returning the value at the index if the index is valid
		if (index <= _currentNumOfElements && index >= 0)
		{
			//returning the element address
			return _array[index];
		}
		//otherwise returning a dummy variable
		else
		{
			//returning a dummy variable
			return _dummy;
		}
	}

	/*
	function of type void to insert a value of type T into
	a certain index
	@param1 index to insert at
	@param2 value to insert
	*/
	void insert(int index, T value)
	{
		//checking if the index is within the boundaries of the array
		if (index <= _currentNumOfElements && index >= 0)
		{
			//increasing the current number of values
			_currentNumOfElements++;

			//checking if the array is full and needs to grow
			if (_currentNumOfElements == _maxNumOfElements)
			{
				//calling the grow function to double the size of the array
				grow();
			}

			//checking if the index already has a value stored at it
			if (index < (_currentNumOfElements - 1))
			{
				//using a for loop to mave all the values over to the next one
				for (int i = _currentNumOfElements; i > index; i--)
				{
					_array[i] = _array[i - 1];
				}
			}

			//setting the value to that index
			_array[index] = value;
		}
		//incase the index is not valid
		else
		{
			//printing an Error message
			cout << "Error 40032: invalid index" << endl;
		}
	}

	/*
	function push front of type void moves all values to the next index
	and places a value at the very front of the array
	@param1 the value being inserted
	*/
	void pushFront(T value)
	{
		//calling insert at the first index of the array
		insert(0, value);
	}
	
	/*
	function push back of type void inserts value at end of arrray
	at the maximum + 1 index
	@param1 the value being inserted
	*/
	void pushBack(T value)
	{
		//calling insert at the end of the array
		insert(getSize(), value);
	}

	/*
	function remove of type T remove a value from a specified index
	and returns that value
	@param1 index to be removed
	*/
	T remove(int index)
	{
		//checking if the index is valid
		if (index < _currentNumOfElements && index >= 0)
		{
			//declaring a variable to temporarily store the curretn value
			T temp = _array[index];

			//checking if the index is before the last element
			if (index < (_currentNumOfElements - 1))
			{
				//using a for loop to move every element to the one prior to it
				for (int i = index; i < _currentNumOfElements; i++)
				{
					_array[i] = _array[i + 1];
				}
			}

			//setting the last element to a dummy variable
			_array[_currentNumOfElements - 1] = _dummy;

			//decreasing the number of elemnts in the array
			_currentNumOfElements--;

			//returning the value that got removed
			return temp;

		}
		//in case the index was invalid
		else
		{
			//printing an Error message
			cout << "Error 40032: invalid index" << endl;
			//returing a dummy variable
			return _dummy;
		}
	}

	/*
	function popFront of type T removes the
	first index of the array and returns it
	*/
	T popFront()
	{
		//calling the remove function on the first index of the array
		return remove(0);
	}

	/*
	function popBack of type T removes the
	last index of the array and returns it
	*/
	T popBack()
	{
		return remove(getSize() - 1);
	}

	/*
	function shuffle of type void mixes the order of the values
	*/
	void shuffle()
	{
		//using a for loop to go through each current element
		for (int i = 0; i < _currentNumOfElements; i++)
		{
			//genrerating a random index
			int randomIndex = rand() % _currentNumOfElements;

			//swapping the values from both indexes
			T temp = _array[i];
			_array[i] = _array[randomIndex];
			_array[randomIndex] = temp;
		}
	}

	/*
	function sort of type void sorts te array in
	accending order
	*/
	void sort()
	{
		//calling the sorting function from Sort.h
		divideAndConquer(_array, _maxNumOfElements, 0, (_currentNumOfElements - 1), true);
	}

	/*
	function print of type void prints out each value in the
	array to the console
	*/
	void print() const
	{
		//using a for loop to go through the current number of elements
		for (int i = 0; i < _currentNumOfElements; i++)
		{
			//printing the element from that index
			cout << _array[i] << " ";
		}

		//enging the line
		cout << endl;
	}
};