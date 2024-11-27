#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000
#define BOARDER_CHAR '#'

//
Player *myPlayer;

//global pointer to GameMechs class
GameMechs *myGM;

const int itemlistsize = 3;
objPos asciiList[itemlistsize];

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);


int main(void)
{

    Initialize();

    //accessing exit flag in GameMechs
    while(myGM->getExitFlagStatus() == false)  
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

    //GameMechs object on the heap
    myGM = new GameMechs();
    //
    myPlayer = new Player(myGM);

    //initialize arbitrary ascii chars (ITERATION 0)
    asciiList[0].setObjPos(3, 6, 'A');
    asciiList[1].setObjPos(5, 5, 'B');
    asciiList[2].setObjPos(6, 8,'C');
}

void GetInput(void)
{
    char input_char = myGM->getInput();

    if(input_char != 0)
    {
        myGM->setInput(input_char);

        switch(input_char) 
        { //DECIDE IF EXIT GAME                  
                case ' ': case 13 : case 27: 
                //case space,escape,enter
                    myGM->setExitTrue(); 
                    //set to true = exit game
                    break;
        }
    }
}

void RunLogic(void)
{
    //movePlayer() calls the updatePlayerDir() function
    //determines the direction, and moves player accordingly
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
    for (j = 0; j < boardY; j++) 
    {
        for (i = 0; i < boardX; i++) 
        {
            asciiflag = false;
            if (i == 0 || i == boardX - 1 || j == 0 || j == boardY - 1) 
                //draws boarder
                MacUILib_printf("%c", BOARDER_CHAR); 
            else if (i == playerX && j == playerY) 
                //draws player @
                MacUILib_printf("%c", playerSymbol);
            else
                //draws space
                MacUILib_printf(" ");
        } 
        MacUILib_printf("\n");
    } 
    MacUILib_printf("Press + to speed up, - to slow down. Current speed level: %d\n", myGM->getCurrentSpeed());
}
    
void LoopDelay(void)
{
    // Change the delaying constant to vary the movement speed.
    int delayspeed;

    switch(myGM->getCurrentSpeed())
    {
        case 1: //slowest
            delayspeed = 400000;
            break;
        case 2: 
            delayspeed = 300000;
            break;
        case 3: // default
            delayspeed = DELAY_CONST; 
            break;
        case 4: 
            delayspeed = 60000;
            break;
        case 5: 
            delayspeed = 10000;
            break;
    }
    MacUILib_Delay(delayspeed); 
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
    //delete heap memory
    delete myPlayer;
    delete myGM;

    for(int k = 0; k < itemlistsize; k++)
        delete asciiList[k].pos;

    MacUILib_uninit();
}
