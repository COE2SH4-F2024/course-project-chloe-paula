#include "GameMechs.h"
#include "MacUILib.h"
#include "objPos.h"
#include "objPosArrayList.h"
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

    winGame = false;
    MAXSCORE = 100;

    foodBucket = new objPosArrayList();

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

    winGame = false;
    MAXSCORE = 100;

    foodBucket = new objPosArrayList();

}


// Destructor:
GameMechs::~GameMechs()
{
    delete foodBucket;
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
    loseFlag = true;    //  true = player lost the game and proper exit message will display
    setExitTrue();      //  make sure game exits
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


// Increment the score by 1 when snake eats a Regular food
void GameMechs::incrementScore()
{
    // Check if player has won the game -- reached a score of 100+
    score++;

    if(getScore() > MAXSCORE)
        setWinGameFlag();

    clearInput();
}


void GameMechs::decreaseScore()
{
    score--;
    // Check if score is invalid -- lost game
    if(getScore() < 0)
        setLoseFlag();
    
    clearInput();

}
//  Increment score by 10 when snake eats a SUPER food
void GameMechs::SuperScore()
{    
    // Check if player has won the game -- reached a score of 100+
    score += 10;

    if(getScore() > MAXSCORE)
        setWinGameFlag();        

    clearInput();
}



// Generate food at a random position
// Requires pointer to playerlist so it won't generate food on the snake
void GameMechs::generateFood(objPosArrayList* blockOff)
{
    //  Generate 5 new foods if no food or after eating 
    if(foodBucket->getSize() == 0 || foodBucket->getSize() < 5)
    {
        foodBucket->clearList();        // clear food bucket to generate new 5 foods

        while(foodBucket->getSize() < 5)
        {
            // Generate random food position within game board
            int x_random = (rand() % (boardSizeX - 2)) + 1; 
            int y_random = (rand() % (boardSizeY - 2)) + 1;
            char newFoodSym = '\0';

            // Generate random food symbol
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
            
            //  Pass by value 
            objPos newFood(x_random, y_random, newFoodSym);

            bool validFood = true;
            for(int i = 0; i < blockOff->getSize(); i++)
            {   
                objPos body = blockOff->getElement(i);
                if(newFood.pos->x == body.pos->x && newFood.pos->y == body.pos->y)
                {
                    validFood = false;  // Random food is invalid, it overlaps with snake
                    break;
                }
            }

            if(validFood)
            {
                foodBucket->insertTail(newFood);     //  Add valid food to the list
            }
        }
    }
}


// Return the current food position
objPosArrayList* GameMechs::getFoodPos() const
{
    return foodBucket;
}


// Return win flag
bool GameMechs::getWinGameStatus() const
{
    return winGame;
}


// Set win flag to ture -- player won game (reached score of 100!)
void GameMechs::setWinGameFlag()
{
    winGame = true;
    setExitTrue();      //  make sure game exits
}