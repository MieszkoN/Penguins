#ifndef INOUT_H
#define INOUT_H

#include <stdio.h>
#include "return_values.h"
#include <string.h>
#include "structures.h"

void printMessage(int result);		                                    /* Function prints an error message depending on the result type (return value) */

void showGameData(struct Gamedata gamedata);                            /* Function shows all game data stored in given parameter */

void printBoard(struct Gamedata gamedata);	                            /* Function prints the board which data is stored in gamedata parameter */

void displayPlayersData(struct Player p);	    	                    /* Function displays players ID with players number */

void showAllPlayersData(struct Gamedata gamedata);                      /* Function displays all players's data which was written to the gamedata parameter */

#endif