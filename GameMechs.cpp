#include "GameMechs.h"
#include "MacUILib.h"
#include <ctime> //for seeding rand()
#include <cstdlib> //for rand()

// Default constructor: Initializes the game with default values
GameMechs::GameMechs()
{
    input = 0;
    score = 0;

    exitFlag = false;
    loseFlag = false;

    boardSizeX = 30; 
    boardSizeY = 15;

    MAX_SPEED = 5;
    MIN_SPEED = 1; 
    gamespeed = 3;

    food.setObjPos(5,5,'o');
}


// Constructor with custom board size
GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    score = 0;

    exitFlag = false;
    loseFlag = false;
    
    // Custom board
    boardSizeX = boardX; 
    boardSizeY = boardY;

    MAX_SPEED = 5;
    MIN_SPEED = 1; 
    gamespeed = 3;

    food.setObjPos(5,5,'o');
}


// Destructor:
GameMechs::~GameMechs()
{
    // Destructor body is empty since there are no dynamically allocated members
}


// Return the status of the exit flag
bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}


// Return the status of the lose flag
bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}


// Set the exit flag to true (game over)
void GameMechs::setExitTrue()
{
    exitFlag = true;
}


// Return the status of the lose flag 
void GameMechs::setLoseFlag()
{
    loseFlag = true; //true = player lost the game
}


// Collect asynchronous input using MacUILib
void GameMechs:: collectAsynInput()
{
    if(MacUILib_hasChar())
    {
        input = MacUILib_getChar();
    }
    
    if(input == ' ') exitFlag = true;
    
}


// Get the most recent input from the user
char GameMechs::getInput() const
{
    return input;
}


// Manually set the input value (useful for debugging)
void GameMechs::setInput(char this_input)
{
    input = this_input; //manually set input if needed
}


// Clear the current input value
void GameMechs::clearInput()
{
    input = '\0'; //reset input to null
}


// Return the width of the game board
int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}


// Return the height of the game board
int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


// Return the current score of the player
int GameMechs::getScore() 
{
    return score;
}


// Increment the score by 1
void GameMechs::incrementScore()
{
    score++;
    clearInput();
}


// Return the maximum allowed game speed
int GameMechs::getMaxSpeed() const
{
    return MAX_SPEED;
}


// Return the minimum allowed game speed
int GameMechs::getMinSpeed() const
{
    return MIN_SPEED;
}


// Return the current game speed
int GameMechs::getCurrentSpeed()
{
    return gamespeed;
}


// Increment the game speed by 1
int GameMechs::increment_speed()
{
    if(gamespeed < MAX_SPEED || gamespeed > MIN_SPEED)
        gamespeed++;
}


// Decrease the game speed by 1
int GameMechs::decrease_speed()
{
    if(gamespeed < MAX_SPEED || gamespeed > MIN_SPEED)
        gamespeed--;
}


// Generate food at a random position
void GameMechs::generateFood(objPosArrayList* blockOff)
{
    bool validFood = false;
    int x_random, y_random;
    char newFoodSym;

    // Easy access to board size
    int xRange = getBoardSizeX();
    int yRange = getBoardSizeY();
    
    do{
        // Generate random food position
        x_random = (rand() % (xRange-2)) + 1; 
        y_random = (rand() % (yRange-2)) + 1;
        
        //Generate random food symbol: (Three options types: num, a, A) 
        int ascii_range = rand() % 3;

        //  Number:
        if (ascii_range == 0)
            newFoodSym = '0' + rand() % 10; 
        //  Lower case letter:
        else if (ascii_range == 1)
           newFoodSym = 'a' + rand() % 26; 
        //  Upper case letter:
        else
            newFoodSym = 'A' + rand() % 26; 
        
        validFood = true;   // Assume the random food position is valid


        // Check if the new food position overlaps with any part of the snake
        for(int i = 0; i < blockOff->getSize(); i++)
        {   
            objPos body = blockOff->getElement(i);
            if (x_random == body.pos->x && y_random == body.pos->y)
            {
                validFood = false;  // Random food is invalid, it overlaps with snake
                break;
            }
        }
    }while(!validFood);    // Continue generating food, until a valid food position is made

    // Set the valid food position and symbol
    food.pos->x = x_random;
    food.pos->y = y_random;
    food.symbol = newFoodSym;

}


// Return the current food position
objPos GameMechs::getFoodPos() const
{
    return food;
}