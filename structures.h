#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string.h>

struct Player
{
	char ID[100]; //max length of Player's ID
	int playerNumber; //player number is a value from 1 to 9, ID is a string
	int score; // the current score of the player
};

struct Coordinate
{
	char x;
	int y; 
    //Coordinates system: one letter, one number
};

struct Field
{
	int fishQuantity;  // the number of fish on the tile
	int playerNumber; //number of the player which is currently located on the field
	struct Coordinate * c;
};

struct Gamedata
{
	int height;
	int width;
	int playerCount;
	struct Field * fields;
	struct Player * players;
};

#endif
