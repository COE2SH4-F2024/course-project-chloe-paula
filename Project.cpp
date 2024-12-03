#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include <ctime>    //For seeding random numbers
#include <cstdlib>  //For random number generation

using namespace std;

//Constants
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
    while(myGM->getExitFlagStatus() == false)  
    {

        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


//  Funtion Definitions


//  Initialize game objects
void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    //Allocate memory for global objects
    myGM = new GameMechs();
    myPlayer = new Player(myGM);

    //Seed rnadom number generation
    srand(time(NULL)); 

    //Generate initial food
    myGM->generateFood(myPlayer->getPlayerPos());

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

    if(!myGM->getLoseFlagStatus() && !myGM->getExitFlagStatus() && !myGM->getWinGameStatus())
        myPlayer->movePlayer();

}


//Create the game board and display the game state
void DrawScreen(void)
{
    MacUILib_clearScreen();    
    
    //  Display instructions
    MacUILib_printf("________C++ Snake Game________\n");
    MacUILib_printf("\nIntructions:\n");
    MacUILib_printf("Reach 100 points to WIN!\n");
    MacUILib_printf("Don't run into your own snake!\n");
    MacUILib_printf("\n1. Use AWDS keys to move snake\n");
    MacUILib_printf("2. Eat UPPER CASE letters\n");
    MacUILib_printf("    +10 EXTRA POINTS \n\n");
    MacUILib_printf("3. Eat NUMBERS:\n");
    MacUILib_printf("    +0 POINTS & SHORTER TAIL:\n");
    MacUILib_printf("4. EXIT GAME:\n");
    MacUILib_printf("   - press ESCAPE, ENTER, SPACE\n\n");


    //  Get board dimensions and player/food positions
    int boardX = myGM->getBoardSizeX();
    int boardY = myGM->getBoardSizeY();
    objPosArrayList* playerPos = myPlayer->getPlayerPos();
    int playerSize = playerPos->getSize();
    objPosArrayList* foodItems = myGM->getFoodPos();
    
    //Draw game state
    for(int j = 0; j < boardY; j++) 
    {
        for(int i = 0; i < boardX; i++) 
        {
            bool printed = false;

            //Draw borders
            if(i == 0 || i == boardX - 1 || j == 0 || j == boardY - 1)
                MacUILib_printf("%c", BOARDER_CHAR); //print boarder
            
            //Draw food
            else
            {
                for(int k = 0; k < foodItems->getSize(); k++)
                {
                    objPos food = foodItems->getElement(k);
                    if(food.pos->x == i && food.pos->y == j)
                    {
                        MacUILib_printf("%c", food.symbol);  // Draw food
                        printed = true;
                        break;
                    }
                }

                if(!printed)
                {
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
}
    


// Control game speed (delay between iterations)
void LoopDelay(void)
{
    int delaySpeed = 100000;
    
    // default delay constant
    MacUILib_Delay(delaySpeed); 
}



// CLean up allocated memory and display end-game messages
void CleanUp(void)
{
    MacUILib_clearScreen();    

    // Display end-game status
    if(myGM->getWinGameStatus())
    {
        MacUILib_printf("Game Won: Amazing!\n");
        MacUILib_printf("Final Score:%d", myGM->getScore());
    }
    else if(myGM->getLoseFlagStatus())
    {    
        MacUILib_printf("Game Over: You lost the game, better luck next time!\n");
    }
    else if(myGM->getExitFlagStatus())
        MacUILib_printf("Game Over: You exited the game!\n");

    // Free allocated memory
    delete myPlayer;
    delete myGM;

    MacUILib_uninit();
}