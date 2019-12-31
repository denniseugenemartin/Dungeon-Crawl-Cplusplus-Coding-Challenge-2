#pragma once

using namespace std;

class Npc;
class Player;

// class to create a gameBoard object.
class GameBoard 
{
	// holds max row/column count.
	int maxDimension;

	
public:

	// keeps track of max number of npcs that can be present
	int maxNumberOfNpcs;

	// position is pointer to beginning of array.
	char* position = NULL;

	// constructor for GameBoard object takes in dimensionvalue as the dimensions of
	// the grid.
	GameBoard(int dimensionValue);

	// return the size of the dimensions outside of class.
	int getMaxDimension() const;

	// this will print the contents of the 2D array as a game board.
	void print() const;

	// seed the initial starting points of all objects.
	void populate(Npc* npcArray, Player& player1);

};
