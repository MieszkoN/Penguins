#include "game.h"


void generateBoard(char * outputFile)
{
	bool val = true;
	time_t tt;
    int seed = time(&tt);
    int input = 0;
    
    // Input parameters
    int height, width, nPlayers;
    printf("\nEnter dimensions and number of players respectively.\n");
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
	file = fopen(outputFile,"w");

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


void placeAllPenguins(struct Gamedata gamedata)
{
    struct Coordinate c;
    system("clear");
    printBoard(gamedata);
    for(int i = 0; i < gamedata.playerCount; ++i)
    {       
        for(int j = 0; j < gamedata.maxPenguins;)
        {
            printf("(Player |%d|)\nWhere to place %d. penguin?\n", i + 1, j + 1);

            while(2 != scanf(" %c%d", &c.x, &c.y))
            {
                system("clear");
                printBoard(gamedata);
                if(!isalpha(c.x) || !isdigit(c.y) || c.y > MAX_WIDTH || c.y < 1 || c.x < 'A' || c.x > 'Z')
                    printf("Wrong input!\n");
                printf("Wrong number of arguments!\n");
            }

            int fieldIndex = (c.x - 65) * gamedata.width + c.y - 1;
            if((gamedata.fields[fieldIndex].fishQuantity == 1) && (gamedata.fields[fieldIndex].playerNumber == 0))
            {
                gamedata.fields[fieldIndex].playerNumber =  gamedata.players[i].playerNumber;
                removeTheFish(&gamedata.fields[fieldIndex]);
                updateFieldPlayerNumber(&gamedata.fields[fieldIndex], i + 1);
                increaseTheScore(&gamedata.players[i], 1);

                system("clear");  	
                printBoard(gamedata);
                ++j;
            }
            else
            {
                system("clear");
                printBoard(gamedata);
                printf("The placement was invalid, try again\n");

            }
        }	
    }

    saveTheGameState(gamedata);
}

void placePenguin(struct Gamedata gamedata)
{
    struct Coordinate c;
    system("clear");
    printBoard(gamedata);
    int placingPlayerIndex = 0;
    int placingPenguinNumber = 1;
	
    // Checking if there are any more penguins to place
    if(gamedata.players[gamedata.playerCount - 1].score < gamedata.maxPenguins)
    {
        // Checking which player has to place a penguin
        for(int i = 0; i < gamedata.playerCount - 1; ++i)
        {
            if(gamedata.players[i].score == gamedata.players[i + 1].score) 
                continue;
            else
            {
                placingPlayerIndex = i + 1;
                break;
            }
        }
        placingPenguinNumber = gamedata.players[placingPlayerIndex].score + 1;
        // Placing a penguin of a found player
        printf("(Player |%d|)\nWhere to place %d. penguin?\n", placingPlayerIndex + 1, placingPenguinNumber);
        while(2 != scanf(" %c%d", &c.x, &c.y))
        {
            system("clear");
            printBoard(gamedata);
            if(!isalpha(c.x) || !isdigit(c.y) || c.y > MAX_WIDTH || c.y < 1 || c.x < 'A' || c.x > 'Z')
                printf("Wrong input!\n");
            printf("Wrong number of arguments!\n");
            printf("(Player |%d|)\nWhere to place %d. penguin?\n", placingPlayerIndex + 1, gamedata.players[placingPlayerIndex].score + 1);
        }

        int fieldIndex = (c.x - 65) * gamedata.width + c.y - 1;
        if((gamedata.fields[fieldIndex].fishQuantity == 1) && (gamedata.fields[fieldIndex].playerNumber == 0))
        {
            gamedata.fields[fieldIndex].playerNumber =  gamedata.players[placingPlayerIndex].playerNumber;
            removeTheFish(&gamedata.fields[fieldIndex]);
            updateFieldPlayerNumber(&gamedata.fields[fieldIndex], gamedata.players[placingPlayerIndex].playerNumber);
            increaseTheScore(&gamedata.players[placingPlayerIndex], 1);
            system("clear");
            printBoard(gamedata);
            printMessage(PLACEMENT_SUCCESS);
        }
        else
        {
            system("clear");
            printBoard(gamedata);
            printf("Error! Chosen field was invalid.\n");
            printMessage(PLACEMENT_FAILURE);
        }
    }
    else
    {
        system("clear");
        printBoard(gamedata);
        printf("There are no penguins to place.\n");
        printMessage(PLACEMENT_FAILURE);
    }
    saveTheGameState(gamedata);
}

void movePenguin(struct Gamedata gamedata)
{
    struct Coordinate startPoint, destination;
    system("clear");
    printBoard(gamedata);

    // Starting point
    printf("Which penguin do you want to move?\n");
    int input = scanf(" %c%d", &startPoint.x, &startPoint.y);
    int startPointIndex = (startPoint.x - 65) * gamedata.width + startPoint.y - 1;
    while(2 != input || gamedata.fields[startPointIndex].playerNumber == 0)
    {
        system("clear");
        printBoard(gamedata);
        if(gamedata.fields[startPointIndex].playerNumber == 0)
            printf("Field cannot be chosen.\n");
        if(!isalpha(startPoint.x) || !isdigit(startPoint.y) || startPoint.y > MAX_WIDTH || startPoint.y < 1 || startPoint.x < 'A' || startPoint.x > 'Z')
            printf("Wrong input!\n");
        if(2 != input)
            printf("Wrong number of arguments!\n");
        printf("Which penguin do you want to move?\n");
        input = scanf(" %c%d", &startPoint.x, &startPoint.y);
        startPointIndex = (startPoint.x - 65) * gamedata.width + startPoint.y - 1;
    }

    system("clear");
    printBoard(gamedata);

	int rowStart, rowEnd, colStart, colEnd, ret = 0;
	colStart = startPointIndex % gamedata.width;
	rowStart = startPointIndex - colStart;
	rowEnd = startPointIndex + gamedata.width - colStart;
	
    // Destination point
    printf("Where to place?\n");
    input = scanf(" %c%d", &destination.x, &destination.y);
    int destinationIndex = (destination.x - 65) * gamedata.width + destination.y - 1;
    colEnd = destinationIndex % gamedata.width;
    if((rowStart < destinationIndex) && (destinationIndex < rowEnd))
    {
		ret = 1;
	}
	else if(colStart == colEnd)
	{
		ret = 1;
	}
    while(2 != input || gamedata.fields[destinationIndex].fishQuantity == 0 || gamedata.fields[destinationIndex].playerNumber != 0  || ret != 1)        //colStart != colEnd ||
    {
		//printf("%d %d %d %d %d %d\n", rowStart, rowEnd, colStart, colEnd, destinationIndex, ret);
        system("clear");
        printBoard(gamedata);
        if(gamedata.fields[destinationIndex].fishQuantity == 0 || gamedata.fields[destinationIndex].playerNumber != 0)
            printf("Field cannot be chosen.\n");
        if(!isalpha(destination.x) || !isdigit(destination.y) || destination.y > MAX_WIDTH || destination.y < 1 || destination.x < 'A' || destination.x > 'Z')
            printf("Wrong input!\n");
        if(2 != input)
            printf("Wrong number of arguments!\n");
        if(((rowStart > destinationIndex) && (destinationIndex > rowEnd)) || (colStart != colEnd))
			printf("Wrong column or row!\n");
        printf("Where to place?\n");
        input = scanf(" %c%d", &destination.x, &destination.y);
        destinationIndex = (destination.x - 65) * gamedata.width + destination.y - 1;
        colEnd = destinationIndex % gamedata.width;
        if((rowStart < destinationIndex) && (destinationIndex < rowEnd))
		{
			ret = 1;
		}
		else if(colStart == colEnd)
		{
			ret = 1;
		}
    }

    int chosenPenguinPlayerNumber = gamedata.fields[startPointIndex].playerNumber;
    increaseTheScore(&gamedata.players[chosenPenguinPlayerNumber - 1], gamedata.fields[destinationIndex].fishQuantity);

    // Place penguin on destination point
    removeTheFish(&gamedata.fields[destinationIndex]);
    updateFieldPlayerNumber(&gamedata.fields[destinationIndex], chosenPenguinPlayerNumber);

    // Remove penguin from starting point
    removeTheFish(&gamedata.fields[startPointIndex]);
    updateFieldPlayerNumber(&gamedata.fields[startPointIndex], 0);

    saveTheGameState(gamedata);

    system("clear");
    printBoard(gamedata);
    //printf("%d\n", startPointIndex);
    printf("Penguin moved successfully.\n");
}


/*
bool canPenguinsMove()
{
    
}
*/

void updateFieldPlayerNumber(struct Field * f, int pNumber)
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

