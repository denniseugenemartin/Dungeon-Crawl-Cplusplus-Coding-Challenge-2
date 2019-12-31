#include <iostream>
#include "Player.h"

using namespace std;

class GameBoard;

// gets called when player character moves. variables  are passed in corresponding to
// row moves (up being a -1 in terms of moving up a row, down being a +1....etc)
// and column moves.
void Player::movePlayer(int rowMove, int columnMove, GameBoard& gameBoard)
{
	// check to see if the player would move outside the bounds of the array/game
	// board. Also check to see if the value contained in the space the player is moving
	// into contains a trap or 'T' or a npc '#'. If so, the player has died and function 
	// will return.
	if ((playerRowPosition + rowMove < 0) ||
		(playerRowPosition + rowMove > gameBoard.getMaxDimension()-1) ||
		(playerColumnPosition + columnMove < 0) ||
		(playerColumnPosition + columnMove > gameBoard.getMaxDimension()-1) ||
		(gameBoard.position[(playerColumnPosition + columnMove) +
		(playerRowPosition + rowMove) * gameBoard.getMaxDimension()] == 'T') ||
			(gameBoard.position[(playerColumnPosition + columnMove) +
		(playerRowPosition + rowMove) * gameBoard.getMaxDimension()] == '#'))
	{
		isAlive = false;
		return;
	}

	// if the space the player would move into contains the treasure or 'X' the 
	// player has won and the function will return.
	else if (gameBoard.position[(playerColumnPosition + columnMove) + (playerRowPosition + rowMove)
			* gameBoard.getMaxDimension()] == 'X')
	{
		hasWon = true;
		return;
	}

	// if the player has not died or won in their move, the spot they left becomes
	// a blank spot or '.' and their representation, a '@' move to the appropriate
	// space.
	else
	{
		gameBoard.position[playerColumnPosition + playerRowPosition * gameBoard.getMaxDimension()] = '.';
		playerRowPosition += rowMove;
		playerColumnPosition += columnMove;
		gameBoard.position[playerColumnPosition + playerRowPosition * gameBoard.getMaxDimension()] = '@';
	}

}

// this will be called to execute the player's turn.
void Player::playerTurn(GameBoard& gameBoard)
{
	// ask the user for a  direction and store that in a char variable, movement.
	cout << "Enter your movement: (w,a,s,d)\n";
	char movement = 0;
	cin >> movement;

	// switch depending on the direction the player has chosen. the values being passed
	// correspond to row moves (-1 or +1) and column moves (-1 or +1) with w and s moving
	// the player up or down a row and a or d moving the player left or right a column.
	// if the user inputs something unexpected, tell them so and ask again.
	switch (movement)
	{
	case 'w':
		movePlayer(-1, 0, gameBoard);
		break;
	case 's':
		movePlayer(1, 0, gameBoard);
		break;
	case 'a':
		movePlayer(0, -1, gameBoard);
		break;
	case 'd':
		movePlayer(0, 1, gameBoard);
		break;
	default:
		cout << "Invalid input.\n";
		cout << "Enter your movement: (w,a,s,d)\n";
		cin >> movement;
	}
}

