#pragma once
#include "GameBoard.h"

using namespace std;

class Player
{
public:

	// creates player object.  rowPosition and columnPosition keep track of where the player is
	// in the array.  isAlive and hasWon are bool types that can trigger exits of the function/loops
	// if the player wins or dies.  
	int playerRowPosition;
	int playerColumnPosition;
	bool isAlive;
	bool hasWon;

	// this will be called to execute the player's turn.
	void playerTurn(GameBoard& gameBoard1);
	
	// gets called when player character moves. variables  are passed in corresponding to
	// row moves (up being a -1 in terms of moving up a row, down being a +1....etc)
	// and column moves.
	void movePlayer(int rowMove, int columnMove, GameBoard& gameBoard);
	
};