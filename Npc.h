#pragma once
#include <random>
#include <iostream>
#include <ctime>
#include <exception>
#include "GameBoard.h"
#include "Player.h"

using namespace std;


// class to create NPC enemies.  Moves around the board like the player but is unable
// to move onto spaces containing the treasure or a trap or off the edge of the board.
class Npc
{
public:

	// rowPosition and columnPosition will be used to keep track of where an NPC is
	// located on the board in terms of row/column of the array. 
	// npcMovesAttempted and maxNpcMoveAttempts will be used during the npc's turn to try and move him around
	// the board. In cases where there is not a valid move, we don't want to attempt
	// moves forever, so the npc will stop attempting at a defined point. stillMoving
	// tracks the status of whether the npc will still attempt moves or not.
	int npcRowPosition;
	int npcColumnPosition;
	int maxNpcMoveAttempts;
	int movesAttempted;
	bool stillMoving;

	// this function carries out the actual movement of the NPC. it returns a bool value
	// to the npcTurn function to let it know whether the movement attempts are still needed.
	// if a true value is returned the moveNpc function will be called again. If the bool value
	// returned is false, the npcTurn function will not be called again.
	bool moveNpc(int rowMove, int columnMove, GameBoard& gameBoard, Player& player1);
	
	// called to automate the turns of the NPCs.
	void npcTurn(GameBoard gameBoard, Player& player1);
	
};

