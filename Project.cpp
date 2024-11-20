#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000
#define BOARDER_CHAR '#'

Player *myPlayer;
GameMechs *myGM;

const int itemlistsize = 3;
objPos asciiList[itemlistsize];

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(exitFlag == false)  
    //or while(myGM->getExitFlagStatus()==false)
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    exitFlag = false;

    myGM = new GameMechs();
    myPlayer = new Player(myGM);

    //initialize arbitrary ascii chars (ITERATION 0)
    asciiList[0].setObjPos(3, 6, 'A');
    asciiList[1].setObjPos(5, 5, 'B');
    asciiList[2].setObjPos(6, 8,'C');
}

void GetInput(void)
{
   
}

void RunLogic(void)
{
    myPlayer->movePlayer();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    

    //copy from ppa2, change the variable names accordingly
    int i, j, k;
    int asciiflag;
    //get board dimensions
    int boardX = myGM->getBoardSizeX();
    int boardY = myGM->getBoardSizeY();
    
    //get player position and symbol
    objPos playerPos = myPlayer->getPlayerPos();
    int playerX = playerPos.pos->x;
    int playerY = playerPos.pos->y;
    char playerSymbol = playerPos.getSymbol();
    
    //draw the board
    for (i = 0; i < boardX; i++) 
    {
        for (j = 0; j < boardY; j++) 
        {
            asciiflag = false;
            if (i == 0 || i == boardX - 1 || j == 0 || j == boardY - 1) 
            {
                MacUILib_printf("%c", BOARDER_CHAR); //boarder
            } 
            else if (i == playerX && j == playerY) 
            {
                MacUILib_printf("%c", playerSymbol);
            } 
            else 
            {
                for(k = 0; k < itemlistsize; k++)
                {
                    if(asciiList[k].pos->x == i && asciiList[k].pos->y == j)
                    {
                        MacUILib_printf("%c", asciiList[k].getSymbol());
                        asciiflag = true;
                        break;
                    }
                }
                if(!asciiflag)
                {
                    MacUILib_printf(" "); //space
                }
            }
        } MacUILib_printf("\n");
    } 
}
    



void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
    //delete pointers
    delete myPlayer;
    delete myGM;

    for(int k = 0; k < itemlistsize; k++)
        delete asciiList[k].pos;

    MacUILib_uninit();
}
