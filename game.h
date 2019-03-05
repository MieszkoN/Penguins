#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <stdbool.h>
#include "gamedata.h"
#include "inout.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "structures.h"
#include "return_values.h"

void generateBoard(char * outputFile);                    

void addPlayers();

bool properDimension(char number[]);

bool numberOfPenguins();    // Parameters need to be added (int nPenguins)

    /*bool type function, which checks whether the number of penguins is less than 10 and greater than 1*/
    //When the phase == placement

void placeAllPenguins(struct Gamedata gamedata);     

void placePenguin(struct Gamedata gamedata);

void movePenguin(struct Gamedata gamedata);

bool canPenguinsMove();

    /*bool type function, checks whether penguin can move (remaining space on the board, other players), return value*/

void updateFieldPlayerNumber(struct Field * f, int pNumber);    // Parameters need to be added (struct Coordinate x)

    /* Function changes the playerNumber value of a field f with given pNumber value*/

void removeTheFish(struct Field * f);      

    /*Int type function, Removes fish when penguin takes over the square*/

void increaseTheScore(struct Player * p, int addValue);      


#endif