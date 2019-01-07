#include "game.h"
#include "inout.h"
#include "gamedata.h"
#include <ctype.h>
#include <time.h>
#include <stdbool.h>


void generateBoard()
{
    bool val = true;
    time_t tt;
    int seed = time(&tt);
    srand(seed);
    int input = 0;
    
    // Input parameters
    int height, width, nPlayers;
    printf("Enter dimensions and number of players respectively.\n");
    while(val)
    {
        input = scanf("%d %d %d", &height, &width, &nPlayers);
        val = (3 != input || height < 0 || width < 0 || height > MAX_HEIGHT || width > MAX_WIDTH || nPlayers < 1 || nPlayers > 9); 
        if(val)
            printf("Wrong arguments!\nType in again.\n");
        else
            val = false;
    }

    // Open file
	srand(seed);
    FILE *file;
	file = fopen("board.txt","w");

    // Add dimensions 
	fprintf(file, "%d %d\n", height, width);

    // Add randomly generated fields
    for(int line_count = 1 ; line_count <= height ; ++line_count)
	{
		for(int column_count = 0 ; column_count < width ; ++column_count)
	        fprintf(file, "%d%d ", rand() % 4, 0);	

		fprintf(file, "\n");
    }

    // Add players
    struct Player p;
    for(int i = 0; i < nPlayers;)
    {
        val = true;
        while(val)
        {
            printf("Player %d ID: ", i + 1);
            input = scanf("%s", p.ID);
            val = strlen(p.ID) > 9 || strlen(p.ID) < 1 || input != 1;
            if(val)
                printf("Wrong ID format!\nType in again.\n\n");
            else
            {
                fprintf(file, "%s %d %d\n", p.ID, i + 1, 0);
                val = false;
                ++i;
            }
        }
    }

    // Close file
	fclose(file);

    // struct Gamedata gamedata = loadGameData();
    // placeThePenguins(gamedata);

}

bool properDimension(char number[]) 
{
	for(int i = 0; number[i] != 0; i++)
	{
        	if (!isdigit(number[i]))
		{
            		return false;
		}    
	}
	return true;
}

bool numberOfPenguins(int nPenguins)
{
     bool result;
     if((nPenguins > 1) && (nPenguins < 10))
     {
         result = 1;
     }
     else
     {
         result = 0;
     }
     return result;
}

void placeThePenguins(struct Gamedata gamedata, int penguins)
{
    FILE *file;
    file = fopen("board.txt","w");
    struct Coordinate c;
    for(int i = 0; i < gamedata.playerCount; ++i)
    {
        printf("\nPlayer %d turn.\n\n", gamedata.players[i].playerNumber);                 /* TU SKONCZYLEM */
        for(int j = 0; j < penguins;)
        {	
            printf("Where to place %d. penguin?\n", j + 1);

            while(2 != scanf(" %c%d", &c.x, &c.y))
            {
                if(!isalpha(c.x) || !isdigit(c.y) || c.y > MAX_WIDTH || c.y < 1 || c.x < 'A' || c.x > 'Z')
                    printf("Wrong input!\n");
                printf("Wrong number of arguments!\n");
            }

            int fieldIndex = (c.x - 65) * gamedata.width + c.y - 1;
            if((gamedata.fields[fieldIndex].fishQuantity == 1) && (gamedata.fields[fieldIndex].playerNumber == 0))
            {
                gamedata.fields[fieldIndex].playerNumber =  gamedata.players[i].playerNumber;
                removeTheFish(&gamedata.fields[fieldIndex]);
                moveThePenguin(&gamedata.fields[fieldIndex], i + 1);
                increaseTheScore(&gamedata.players[i], 1);

                saveTheGameState(gamedata);
                printBoard(gamedata);
                ++j;
            }
            else
                printf("The placement was invalid, try again\n");
        }	
    }

    fclose(file);
}


bool canPenguinsMove()
{
    
}

void moveThePenguin(struct Field * f, int pNumber)
{
    f->playerNumber = pNumber;
}

void removeTheFish(struct Field * f)
{
    f->fishQuantity = 0;
}

void increaseTheScore(struct Player * p, int addValue)
{
    p->score += addValue;
}

