#ifndef GAME_H
#define GAME_H

#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "structures.h"
#include "return_values.h"

void generateBoard();                    

void addPlayers();

bool properDimension(char number[]);

bool numberOfPenguins();    // Parameters need to be added (int nPenguins)

    /*bool type function, which checks whether the number of penguins is less than 10 and greater than 1*/
    //When the phase == placement

void placeThePenguins(struct Gamedata gamedata, int penguins);     // Parameters need to be added (struct Coordinate x)

    /*int type function, place penguins on the board by coordinates:
    Read the number of players & player ID from the command line parameter
    Checks whether the entered values are valid
    Use pointers to replace the blocks with player IDs*/

bool canPenguinsMove();

    /*bool type function, checks whether penguin can move (remaining space on the board, other players), return value*/

void moveThePenguin(struct Field * f, int pNumber);    // Parameters need to be added (struct Coordinate x)

    /* Function changes the playerNumber value of a field f with given pNumber value*/

void removeTheFish(struct Field * f);      

    /*Int type function, Removes fish when penguin takes over the square*/

void increaseTheScore(struct Player * p, int addValue);      


#endif
