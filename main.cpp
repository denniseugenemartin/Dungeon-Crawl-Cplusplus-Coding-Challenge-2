#include <iostream>
#include "Npc.h"
#include "Player.h"
#include "GameBoard.h"

using namespace std;

int main()
{
	// print intro to user.
	cout << "You are an adventurer, \'@\', in search of treasure!\n";
	cout << "This treasure will be represented by an \'X\'.\n";
	cout << "Watch out for traps represented by a \'T\' ";
	cout << "and evil NPCs represented by a \'#\'\n";

	// create gameboard, npcs, player objects.
	GameBoard gameBoard1(20);
	Npc* npcArray = new Npc[5];
	Player player1;

	// stillPlaying will be checked at end of loop (when player wins or dies) to determine
	// whether to continue with another loop of the game.
	bool stillPlaying = true;
	while (stillPlaying ==true)
	{
		// seed the starting locations of everything.
		gameBoard1.populate(npcArray, player1);
		while (true)
		{
			gameBoard1.print();

			// the player will take a turn and after that the program checks to see if
			// they have died or found the treasure. If they have they get a victory or
			// death message and the program exits. If not, the game board is printed 
			//to the user and then NPCs take a turn.
			player1.playerTurn(gameBoard1);
			if (player1.isAlive == false)
			{
				cout << "You have perished. None will mourn your passing.\n";
				break;
			}
			else if (player1.hasWon == true)
			{
				cout << "Congratulations! You have found the treasure!\n";
				break;
			}
			gameBoard1.print();

			// loop goes through the array of NPC's and each one takes a turn moving. When
			// complete check to see if the player has died. If so, print losing message and
			// break. If not print map and player takes a turn.
			cout << "NPC turn:\n";
			for (int i = 0; i < gameBoard1.maxNumberOfNpcs; ++i)
			{
				npcArray[i].npcTurn(gameBoard1, player1);
			}
			if (player1.isAlive == false)
			{
				cout << "You have perished. None will mourn your passing!\n";
				break;
			}
			gameBoard1.print();
		}

		// ask user input if they want to play again. Take input and store in variable
		// playAgain. check to see if y, if so then repeat gameplay loop. Otherwise exit.
		cout << "Play again? (y/n)\n";
		char playAgain;
		cin >> playAgain;
	
		if (playAgain == 'y')
		{
			continue;
		}
		else
		{
			break;
		}

	}
}
		




