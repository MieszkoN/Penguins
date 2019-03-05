#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "return_values.h"
#include "inout.h"
#include "game.h"
#include "gamedata.h"
#include "structures.h"


int main(int argc, char * argv[])
{	
	// Checking number of command line parameters
	if(argc < 2 && argc > 5)
	{
		printMessage(WRONG_CMD_PARAMETERS);
		return WRONG_CMD_PARAMETERS; 
	}

	// Playing for the first time (initializing game)
	if(argc == 3 && !strcmp(argv[1], "generate_board"))
	{
		struct Gamedata gamedata;
		strcpy(gamedata.outputFile, argv[2]);
		generateBoard(gamedata.outputFile);
		if(!isEmpty(gamedata.outputFile))
		{
			printMessage(GENERATING_BOARD_SUCCESS);
			return GENERATING_BOARD_SUCCESS;
		}
		else
		{
			printMessage(GENERATING_BOARD_FAILURE);
			return GENERATING_BOARD_FAILURE;
		}
	}

	// // Loading data after board is generated
	// struct Gamedata gamedata = loadGameData();
	// if(!gamedata.isDataLoaded)
	// {
	// 	printMessage(LOADING_DATA_FAILURE);
	// 	return LOADING_DATA_FAILURE;
	// }

	//Start placement phase (second parameter is a number of penguins to place)
	if(argc == 5 && !strcmp(argv[1], "place_all") && argv[2][0] - '0' > 0 && argv[2][0] - '0' <= MAX_PENGUINS)
	{
		struct Gamedata gamedata;
		char inFile[MAX_FILENAME_LENGTH];
		char outFile[MAX_FILENAME_LENGTH];

		strcpy(inFile, argv[3]);
		strcpy(outFile, argv[4]);

		gamedata = loadGameData(inFile);

		strcpy(gamedata.inputFile, inFile);
		strcpy(gamedata.outputFile, outFile);

		if(isGameNew(gamedata))
		{
			gamedata.maxPenguins = argv[2][0] - '0';
			placeAllPenguins(gamedata);	
			printMessage(PLACEMENT_SUCCESS);									
			return PLACEMENT_SUCCESS;
		}
		else
		{
			printMessage(PLACEMENT_FAILURE);
			return PLACEMENT_FAILURE;
		}
	}
	else if(argc == 5 && !strcmp(argv[1], "phase=placement") && argv[2][9] - '0' > 0 && argv[2][9] - '0' <= MAX_PENGUINS)	// ./penguins phase=placement penguins=3
	{
		struct Gamedata gamedata;
		char inFile[MAX_FILENAME_LENGTH];
		char outFile[MAX_FILENAME_LENGTH];

		strcpy(inFile, argv[3]);
		strcpy(outFile, argv[4]);

		gamedata = loadGameData(inFile);

		strcpy(gamedata.inputFile, inFile);
		strcpy(gamedata.outputFile, outFile);

		if(!gamedata.isDataLoaded)
		{
			printMessage(LOADING_DATA_FAILURE);
			return LOADING_DATA_FAILURE;
		}
		
		gamedata.maxPenguins = argv[2][9] - '0';
		placePenguin(gamedata);
		// if()					// Change condition
		// {
		// 	printMessage(PLACEMENT_SUCCESS);									
		// 	return PLACEMENT_SUCCESS;
		// }
		// else
		// {
		// 	printMessage(PLACEMENT_FAILURE);
		// 	return PLACEMENT_FAILURE;
		// }
	}

	/* printMessage(INTERNAL_PROGRAM_ERROR); 
		return INTERNAL_PROGRAM_ERROR; */

	// Showing game data
	else if(argc == 3 && !strcmp(argv[1], "show_data"))		
	{
		struct Gamedata gamedata;
		strcpy(gamedata.inputFile, argv[2]);
		gamedata = loadGameData(gamedata.inputFile);
		showGameData(gamedata);
	}

	else if(argc == 3 && !strcmp(argv[1], "show_board"))		
	{
		struct Gamedata gamedata;
		strcpy(gamedata.inputFile, argv[2]);
		gamedata = loadGameData(gamedata.inputFile);	//gamedata.inputFile is lost here
		printBoard(gamedata);
	}


	// Showing players' id's
	else if(argc == 3 && !strcmp(argv[1], "id"))		
	{	
		struct Gamedata gamedata;
		strcpy(gamedata.inputFile, argv[2]);
		gamedata = loadGameData(gamedata.inputFile);	//gamedata.inputFile is lost here
		showAllPlayersData(gamedata);
		printMessage(CORRECT_MOVE);
		return CORRECT_MOVE; 
	}

	else if(argc == 4 && !strcmp(argv[1], "phase=movement"))
	{
		struct Gamedata gamedata;
		char inFile[MAX_FILENAME_LENGTH];
		char outFile[MAX_FILENAME_LENGTH];

		strcpy(inFile, argv[2]);
		strcpy(outFile, argv[3]);

		gamedata = loadGameData(inFile);

		strcpy(gamedata.inputFile, inFile);
		strcpy(gamedata.outputFile, outFile);


		if(!isGameNew(gamedata))
		{
			movePenguin(gamedata);
		}	
		else
		{
			printMessage(CAN_NOT_MAKE_ANY_MOVE);
		    return CAN_NOT_MAKE_ANY_MOVE; 
		}
	}
}