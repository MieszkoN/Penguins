#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "structures.h"
#include "inout.h"
#include "return_values.h"

struct Gamedata loadGameData(char * inputFile);                                         /* Function that loads all the data from a file with a specified format */
void saveTheGameState(struct Gamedata gamedata);                        /* The function saves data from gamedata object to board.txt file */
bool isWhitespace(int ascii);
bool isEmpty(char * file);
bool isGameNew(struct Gamedata gamedata);

#endif