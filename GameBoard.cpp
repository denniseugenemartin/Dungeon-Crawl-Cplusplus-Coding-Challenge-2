#include <random>
#include <iostream>
#include <ctime>
#include <exception>
#include "Npc.h"
#include "Player.h"
#include "GameBoard.h"

using namespace std;

// constructor for object gameBoard.  dimensionValue is the size of the rows and columns.
// maxDimension will be used elsewhere in the program to check bounds of array. position
// is a pointer to the beginning of an array that will be created that is (x by x) ie (20 x 20) grid.
GameBoard::GameBoard(int dimensionValue) 
{
	maxNumberOfNpcs = 5;
	maxDimension = dimensionValue-1;
	position = new char[dimensionValue * dimensionValue];
}

// return the size of the dimensions of the grid outside of class.
int GameBoard::getMaxDimension() const
{
	return maxDimension;
}

// this will print the contents of the 2D array as a game board.
void GameBoard::print() const
{
	for (int row = 0; row < maxDimension; ++row)
	{
		for (int column = 0; column < maxDimension; ++column)
		{
			cout << position[column + row * maxDimension];
		}
		cout << endl;
	}
	for (int i = 0; i < maxDimension; ++i)
	{
		cout << "=";
	}
	cout << endl;
}

// when the game first starts this function will be called to place elements randomly 
// around the board (and in the array)
void GameBoard::populate(Npc* npcArray, Player& player1)
{
	// numberOfTraps contain the number of traps present on the board, and row and column
	// positions that will be used to place the traps. maxNumberOfTraps holds the max 
	// number of traps that will be present.
	int numberOfTraps = 0;
	int maxNumberOfTraps = 5;
	int rowPosition = 0;
	int columnPosition = 0;

	// declare random number generator for later use in seeding random starting positions.
	default_random_engine generator(time(NULL));
	uniform_int_distribution<int> distribution(0, maxDimension);

	// first the array is seeded with blank spaces or '.' using this loop.
	for (int row = 0; row < maxDimension; ++row)
	{
		for (int column = 0; column < maxDimension; ++column)
		{
			position[column + row * maxDimension] = '.';
		}
	}

	// the player is placed in their starting position. playerRowPosition and 
	// playerColumnPosition track the location of the player in the
	// grid in terms of row/column.  isAlive tracks whether the player has died (lost) the 
	// game.  hasWon tracks whether the player has won the game or not.
	position[10] = '@';
	player1.playerRowPosition = 0;
	player1.playerColumnPosition = 10;
	player1.isAlive = true;
	player1.hasWon = false;

	// loop to place the NPCs. it will continue until the required number of NPCs
	// have been placed onto the board.
	for (int i = 0; i < maxNumberOfNpcs; ++i)
	{
		// get a random starting position
		rowPosition = distribution(generator);
		columnPosition = distribution(generator);

		// if that position contains the player or a trap or another NPC already, don't 
		// place it and instead go through the loop again.
		if (position[columnPosition + rowPosition * maxDimension] == '@' ||
			position[columnPosition + rowPosition * maxDimension] == 'T')
		{
			--i;
			continue;
		}

		// if the space is blank change the value there to a '#' or NPC. Increase the
		// number of NPCs, and if there are enough NPCs out break from the loop.
		else
		{
			position[columnPosition + rowPosition * maxDimension] = '#';
			npcArray[i].npcRowPosition = rowPosition;
			npcArray[i].npcColumnPosition = columnPosition;
		}
	}

	// loop used to place traps onto the board. it will continue until the required
	// number of traps have been placed.
	while (numberOfTraps < maxNumberOfTraps)
	{
		// get a random starting position
		rowPosition = distribution(generator);
		columnPosition = distribution(generator);

		// if that position contains the player, NPC, or a trap already, don't place it
		// and instead go through the loop again.
		if (position[columnPosition + rowPosition * maxDimension] == '@' ||
			position[columnPosition + rowPosition * maxDimension] == '#' ||
			position[columnPosition + rowPosition * maxDimension] == 'T')
		{
			continue;
		}

		// if the space is blank change the value there to a 'T' or trap. Increase the
		// number of traps, and if there are enough traps out break from the loop.
		else
		{
			position[columnPosition + rowPosition * maxDimension] = 'T';
			++numberOfTraps;
			continue;
		}
	}

	// this loop will place the treasure on the board. only one treasure will be placed
	// at which the loop will exit. if random position already contains an object,
	// the loop will run again to try and find an empty space.
	while (true)
	{
		// get a random starting location.
		rowPosition = distribution(generator);
		columnPosition = distribution(generator);

		// if this position already contains a player, NPC or trap, don't place it.
		// instead start the loop again.
		if (position[columnPosition + rowPosition * maxDimension] == '@' ||
			position[columnPosition + rowPosition * maxDimension] == '#' ||
			position[columnPosition + rowPosition * maxDimension] == 'T')
		{
			continue;
		}

		// if the spot is blank, then place the treasure or 'X' and break from the loop.
		else
		{
			position[columnPosition + rowPosition * maxDimension] = 'X';
			break;
		}
	}
}

