#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "return_values.h"
#include "inout.h"
#include "game.h"
#include "gamedata.h"
#include "structures.h"


int main(int argc, char * argv[])
{
	// Playing for the first time (initializing game)
	if(argc == 2 && !strcmp(argv[1], "new_game"))
	{
		generateBoard();
		//struct Gamedata gamedata = loadGameData();
		//printBoard(gamedata);
		//showGameData(gamedata);
		//placeThePenguins(gamedata);
		// struct Gamedata gamedata = loadGameData();
		// printBoard(gamedata);
	}
	// Loading data from a file
	/*
	if(!isEmpty())
	{
		// struct Gamedata gamedata = loadGameData();
		// showAllPlayersData(gamedata);
		// printBoard(gamedata);
	}
	else
	{
		printMessage(EMPTY_FILE);
	}	
	*/
	// saveTheGameState(gamedata);

	// Code for random board is needed before loading game data

	// Command line parameters handling must be added

	else if( (strcmp(argv[1],"phase=placement") == 0) && (argc == 4))	
	{
		int nPenguins = atoi(argv[2]);
	 	if(numberOfPenguins(nPenguins)) 
	 	{
			struct Gamedata gamedata = loadGameData();
			printBoard(gamedata);
			placeThePenguins(gamedata, nPenguins); 
			//saveTheGameState(gamedata); 
			showAllPlayersData(gamedata);
			printMessage(CAN_NOT_MAKE_ANY_MOVE);
			printf("All penguins are placed.\n");
			return CAN_NOT_MAKE_ANY_MOVE; 
		}
			
		else
		{
	       	    printMessage(INTERNAL_PROGRAM_ERROR);
	            return INTERNAL_PROGRAM_ERROR; 
		}
			
	 }
	 else if(strcmp(argv[1], "id") == 0 && argc == 2)		/*  Player ID as another parameter (?) */
	 {	
		//struct Player P;				/* Needs to be specified */	

		//displayPlayersData(P);
		printMessage(CORRECT_MOVE);
	 	return CORRECT_MOVE; 
	// 	}
	// 	else if(argv[1] == "phase=movement" && argc == 3)
	// 	{
	// 		if(canPenguinsMove()) //check whether penguin can move, bool type function
	// 		{
	// 			moveThePenguin(); //move the penguin using coordinates
	// 			changeTheScore(); //change the score of player
	// 			saveTheGameState(); //save changes of the game
	// 			printMessage(CORRECT_MOVE);
	// 			return CORRECT_MOVE; //return 0
	// 		}	
	// 		else
	// 		{
	// 			printMessage(CAN_NOT_MAKE_ANY_MOVE);
	// 		    return CAN_NOT_MAKE_ANY_MOVE; //return 1
	// 		}
				
	 } 
	 else 
	 {
	 	printMessage(INTERNAL_PROGRAM_ERROR);
		return INTERNAL_PROGRAM_ERROR;  //return 3
	 }
}
