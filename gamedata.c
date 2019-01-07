#include "gamedata.h"

struct Gamedata loadGameData()
{
    struct Gamedata gamedata;
    FILE *fp;

    // Opening file
    fp = fopen("board.txt", "r");
    if(fp == NULL)
    {
        printMessage(INPUT_FILE_ERROR);
        exit(0);
    }

    // Loading dimensions
    if(2 != fscanf(fp, "%d %d", &gamedata.height, &gamedata.width))
    {
        printMessage(INPUT_FILE_ERROR);
        exit(0);
    }
    if(gamedata.height < 0 || gamedata.width < 0)
    {
        printMessage(INPUT_FILE_ERROR);
        exit(0);
    }
    gamedata.fields = (struct Field *)malloc(gamedata.height * gamedata.width * sizeof(struct Field));

    // Loading fields' data
    for(int i = 0; i < gamedata.height * gamedata.width;)
    {
        int v1 = getc(fp);
        if(!isWhitespace(v1))
        {
            int v2 = getc(fp);
            if(!isWhitespace(v2))
            {
                gamedata.fields[i].fishQuantity = v1 - '0';
                gamedata.fields[i].playerNumber = v2 - '0';
                ++i;
            }
        }
    }
    long fileIndicatorPosition = ftell(fp);

    // Count number of players in a file
    int ch = 0;
    gamedata.playerCount = 0;
    while(!feof(fp))
    {
        ch = fgetc(fp);
        if(ch == '\n')
            ++gamedata.playerCount;
    }
    --gamedata.playerCount;

    // Reposition of stream position indicator
    fseek(fp, fileIndicatorPosition, SEEK_SET);

    // Loading players data
    gamedata.players = (struct Player *)malloc(gamedata.playerCount * sizeof(struct Player));

    for(int i = 0; i < gamedata.playerCount; ++i)
    {
        if(3 != fscanf(fp, "%s %d %d", gamedata.players[i].ID , &gamedata.players[i].playerNumber, &gamedata.players[i].score))
        {
            printMessage(INPUT_FILE_ERROR);
            exit(0);
        }
    }

     // Closing file   
    fclose(fp);

    return gamedata;
}

void saveTheGameState(struct Gamedata gamedata)
{
    FILE *fp;
    fp = fopen("board.txt", "w");
    if(fp == NULL)
    {
        printMessage(INPUT_FILE_ERROR);
        exit(0);
    }

    fprintf(fp, "%d %d\n", gamedata.height, gamedata.width);
    for(int i = 1; i < gamedata.height * gamedata.width + 1; ++i)
    {
        fprintf(fp, "%d%d ", gamedata.fields[i - 1].fishQuantity, gamedata.fields[i - 1].playerNumber);
        if(i % gamedata.width == 0) 
            fprintf(fp, "\n");
    }
    for(int i = 0; i < gamedata.playerCount; ++i)
        fprintf(fp, "%s %d %d\n",  gamedata.players[i].ID , gamedata.players[i].playerNumber, gamedata.players[i].score);

    fclose(fp);

}


bool isWhitespace(int ascii)
{
    if(ascii == 32 || ascii == 9 || ascii == 10 || ascii == 11 || ascii == 12 || ascii == 13 )
        return true;
    else
        return false;
}

bool isEmpty()
{
    bool bVal = false;
    FILE *fp = fopen("board.txt", "r");
    fseek(fp, 0, SEEK_END); // Goto the end of file
    if (ftell(fp) == 0)
        bVal = true;
    fclose(fp);

    return bVal;
}
