#include "inout.h"

void printMessage(int result)
{
    switch(result)   
	{  
		case CORRECT_MOVE:  printf("You made the correct move!\n"); 
		   break;
		/*The movement is valid. The program continues to execute the movement loop, and this message is printed*/
		
		case CAN_NOT_MAKE_ANY_MOVE:  printf("The program cannot make any movement!\n"); 
		   break;
		/*The message announces that the move is invalid. The game state remains unchanged, and the program wait for a valid input*/
		
		case INPUT_FILE_ERROR: printf("Something went wrong, check your input/output file!\n"); 
		   break;
		/*This message is printed when there is an error in the input file. The game does not proceed*/
		
		case INTERNAL_PROGRAM_ERROR:  printf("Internal program error!\n");
		   break;
		/*Unknown error detected during the program execution*/

        case EMPTY_FILE : printf("The input file is empty. You must create a new game.\n");
		   break;
	}  
}

void showGameData(struct Gamedata gamedata)
{
    printf("\n%d %d\n", gamedata.height, gamedata.width);
    for(int i = 1; i < gamedata.height * gamedata.width + 1; ++i)
    {
        printf("%d%d ", gamedata.fields[i - 1].fishQuantity, gamedata.fields[i - 1].playerNumber);
        if(i % gamedata.width == 0) 
            printf("\n");
    } 

    for(int i = 0; i < gamedata.playerCount; ++i)
        printf("%s %d %d\n",  gamedata.players[i].ID , gamedata.players[i].playerNumber, gamedata.players[i].score);
    
    printf("\n");
}

void printBoard(struct Gamedata gamedata)
{
    printf("-BOARD-\n\n");
    printf("     ");
        for(int i = 1; i <= gamedata.width; ++i)
        {
            if(i < 10)
                printf("0%d ", i);
            else
                printf("%d ", i);
        }
    printf("\n\n");

    int count = 0;

    for(int i = 1; i < gamedata.height * gamedata.width + 1; ++i)
    {
        if((i - 1) % gamedata.width == 0)
        {
            printf(" %c   ", count + 65);
            ++count;
        }
        printf("%d%d ", gamedata.fields[i - 1].fishQuantity, gamedata.fields[i - 1].playerNumber);
        if(i % gamedata.width == 0)         
            printf("   %c\n", count + 64);
    } 

    printf("\n     ");
        for(int i = 1; i <= gamedata.width; ++i)
        {
            if(i < 10)
                printf("0%d ", i);
            else
                printf("%d ", i);
        }
        printf("\n");
}

void displayPlayersData(struct Player p)
{
    printf("Player |%d|\n\n    Player ID: %s\n    Player score: %d\n", p.playerNumber, p.ID, p.score);
}

void showAllPlayersData(struct Gamedata gamedata)
{
    printf("\n-INFORMATION-ABOUT-PLAYERS-\n\n");
    for(int i = 0; i < gamedata.playerCount; ++i)
    {
        displayPlayersData(gamedata.players[i]);
        printf("\n\n");
    }
}
