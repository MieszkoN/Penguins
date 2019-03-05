#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string.h>
#include <stdbool.h>
#include "return_values.h"

struct Player
{
	char ID[MAX_ID_LENGTH];
	int playerNumber; 				//player number is a value from 1 to 9,
	int score; 
	int penguinsPlaced;
};

struct Coordinate
{
	char x;
	int y; 
};

struct Field
{
	int fishQuantity;  
	int playerNumber; //number of the player which is currently located on the field
};

struct Gamedata
{
	int height;
	int width;

	int playerCount;
	int maxPenguins;

	bool isDataLoaded;

	char inputFile[MAX_FILENAME_LENGTH];
	char outputFile[MAX_FILENAME_LENGTH];

	struct Field * fields;
	struct Player * players;
};

#endif
