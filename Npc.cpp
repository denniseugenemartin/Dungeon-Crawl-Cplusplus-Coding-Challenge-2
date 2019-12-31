
#include <random>
#include <iostream>
#include <ctime>
#include "GameBoard.h"
#include "Player.h"
#include "Npc.h"

using namespace std;

	// this function carries out the actual movement of the NPC. it returns a bool value
	// to the npcTurn function to let it know whether the movement attempts are still needed.
	// if a true value is returned the moveNpc function will be called again. If the bool value
	// returned is false, the npcTurn function will not be called again.
	bool Npc::moveNpc(int rowMove, int columnMove, GameBoard& gameBoard, Player& player1)
	{
		// check to see if the NPC would move outside the bounds of the array/game
		// board. Also check to see if the value contained in the space the NPC is moving
		// into contains a trap or 'T' or the treasure 'X'. If so, don't move there
		if ((npcRowPosition + rowMove < 0) ||
			(npcRowPosition + rowMove > gameBoard.getMaxDimension()-1) ||
			(npcColumnPosition + columnMove < 0) ||
			(npcColumnPosition + columnMove > gameBoard.getMaxDimension()-1) ||
			(gameBoard.position[(npcColumnPosition + columnMove) + (npcRowPosition + rowMove)
			* gameBoard.getMaxDimension()] == 'X') ||
			(gameBoard.position[(npcColumnPosition + columnMove) + (npcRowPosition + rowMove)
			* gameBoard.getMaxDimension()] == '#') ||
			(gameBoard.position[(npcColumnPosition + columnMove) + (npcRowPosition + rowMove)
			* gameBoard.getMaxDimension()] == 'T'))
		{
			return true;
		}

		// if the space the NPC would move into contains the player or '@' the 
		// player has died and the function will return.
		else if (gameBoard.position[(npcColumnPosition + columnMove) + (npcRowPosition + rowMove)
				* gameBoard.getMaxDimension()] == '@')
		{
			player1.isAlive = false;
			return false;
		}

		// if the player has not died, the spot the NPC left becomes
		// a blank spot or '.' and their representation, a '#' move to the appropriate
		// space.
		else
		{
			gameBoard.position[npcColumnPosition + npcRowPosition * gameBoard.getMaxDimension()] = '.';
			npcRowPosition += rowMove;
			npcColumnPosition += columnMove;
			gameBoard.position[npcColumnPosition + npcRowPosition * gameBoard.getMaxDimension()] = '#';
			return false;
		}
	}
	// called to automate the turns of the NPCs.
	void Npc::npcTurn(GameBoard gameBoard, Player& player1)
	{
		// npcMovesAttempted and maxNpcMoveAttempts will be used during the npc's turn to try and move him around
		// the board. In cases where there is not a valid move, we don't want to attempt
		// moves forever, so the npc will stop attempting at a defined point. stillMoving
		// tracks the status of whether the npc will still attempt moves or not.
		int maxNpcMoveAttempts = 6;
		int npcMovesAttempted = 0;
		bool stillMoving = true;

		// a random direction is given for the NPC to move represented by 0-3. A stillMoving
		// variable keeps track of whether the NPC should stop moving for this turn.
		default_random_engine generator(time(NULL));
		uniform_int_distribution<int> distribution(0, 3);

		// while the NPC still has movement left (i.e. they have not yet made a valid
		// move. They will call the moveNpc function with a 0 or -1 to indicate their
		// movement along a row or column. If they attempt to move and it is not a valid
		// move they will continue the loop until they select a valid move. A max of 5
		// attempted moves will be allowed to prevent situations where there is no valid 
		// move hanging the game.
		while (stillMoving == true && npcMovesAttempted < maxNpcMoveAttempts)
		{
			int movement = distribution(generator);
			switch (movement)
			{

			case 0:
				stillMoving = moveNpc(-1, 0, gameBoard, player1);
				++npcMovesAttempted;
				break;
			case 1:
				stillMoving = moveNpc(1, 0, gameBoard, player1);
				++npcMovesAttempted;
				break;
			case 2:
				stillMoving = moveNpc(0, -1, gameBoard, player1);
				++npcMovesAttempted;
				break;
			case 3:
				stillMoving = moveNpc(0, 1, gameBoard, player1);
				++npcMovesAttempted;
				break;

			}
		}
	}


