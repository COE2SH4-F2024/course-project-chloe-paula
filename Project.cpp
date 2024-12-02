#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include <ctime>    //For seeding random numbers
#include <cstdlib>  //For random number generation

using namespace std;

//Constants
#define DELAY_CONST 100000
#define BOARDER_CHAR '#'

//Global Variables
Player *myPlayer;       //Pointer to Player class
GameMechs *myGM;        //Pointer to GameMechs class

//Function Prototypes
void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

//Main Function
int main(void)
{

    Initialize();

    //Main game loop
    while(myGM->getExitFlagStatus() == false && myGM->getLoseFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


// Funtion Definitions


//Initialize game objects
void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    //Allocate memory for global objects
    myGM = new GameMechs();
    myPlayer = new Player(myGM);

    //Seed rnadom number generation
    srand(time(NULL)); 

}


//Get input from the player and exit commands
void GetInput(void)
{
    myGM->collectAsynInput();
    char input_char = myGM->getInput();

    if(input_char != '\0')
    {
        myGM->setInput(input_char);

        switch(input_char) 
        {                   
                // Space, Enter, or Escape: Exit game
                case ' ': case 13 : case 27:
                    myGM->setExitTrue(); 
                    break;
        }
    }
}


//Update game logic
void RunLogic(void)
{
    myPlayer->updatePlayerDir();

    if(!myGM->getLoseFlagStatus() && !myGM->getExitFlagStatus())
        myPlayer->movePlayer();

}


//Create the game board and display the game state
void DrawScreen(void)
{
    MacUILib_clearScreen();    

    //Get board dimensions and player/food positions
    int boardX = myGM->getBoardSizeX();
    int boardY = myGM->getBoardSizeY();
    objPosArrayList* playerPos = myPlayer->getPlayerPos();
    int playerSize = playerPos->getSize();
    objPos foodPos = myGM->getFoodPos();
    
    //Draw game state
    for(int j = 0; j < boardY; j++) 
    {
        for(int i = 0; i < boardX; i++) 
        {
            //Draw borders
            if(i == 0 || i == boardX - 1 || j == 0 || j == boardY - 1)
                MacUILib_printf("%c", BOARDER_CHAR); //print boarder
            
            //Draw food
            else if(i == foodPos.pos->x && j == foodPos.pos->y)
                MacUILib_printf("%c", foodPos.symbol); 
            
            //Draw snake
            else
            {
                bool printed = false;
                for(int k = 0; k < playerSize; k++)
                {
                    objPos thisSeg = playerPos->getElement(k);

                    if(thisSeg.pos->x == i && thisSeg.pos->y == j)
                    {
                        MacUILib_printf("%c", thisSeg.symbol);
                        printed = true;
                        break;
                    }
                }   

                //Print a space if no other element matches
                if(!printed)
                    MacUILib_printf("%c", ' ');
            }
        } 
        MacUILib_printf("\n"); //move to next row with new line
    } 

    // Display game information
    MacUILib_printf("Score: %d",myGM->getScore());
    MacUILib_printf("\nPress + to speed up, - to slow down. Current speed level: %d\n", myGM->getCurrentSpeed());
    MacUILib_printf("To EXIT GAME: press ESCAPE, ENTER or SPACE button");
}
    

// Control game speed (delay between iterations)
void LoopDelay(void)
{
    // Change the delaying constant to vary the movement speed.
    int delayspeed;

    // Adjust delay based on current game speed
    switch(myGM->getCurrentSpeed())
    {
        case 1: //slowest
            delayspeed = 400000;
            break;
        case 2: 
            delayspeed = 300000;
            break;
        case 3: 
            delayspeed = DELAY_CONST;  //default speed
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


// CLean up allocated memory and display end-game messages
void CleanUp(void)
{
    MacUILib_clearScreen();    

    // Display end-game status
    if(myGM->getLoseFlagStatus())
        MacUILib_printf("Game Over: You lost the game!\n");
    else if(myGM->getExitFlagStatus())
        MacUILib_printf("Game Over: You exited the game!\n");

    // Free allocated memory
    delete myPlayer;
    delete myGM;

    MacUILib_uninit();

}