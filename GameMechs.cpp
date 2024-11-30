#include "GameMechs.h"
#include "MacUILib.h"
#include <ctime> //for seeding rand()
#include <cstdlib> //for rand()

GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;
    boardSizeX = 30; 
    boardSizeY = 15;
    MAX_SPEED = 5;
    MIN_SPEED = 1; 
    gamespeed = 3;

    food.setObjPos(5,5,'o');
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;
    MAX_SPEED = 5;
    MIN_SPEED = 1; 
    gamespeed = 3;
    
    boardSizeX = boardX;
    boardSizeY = boardY;

    food.setObjPos(5,5,'o');

}

// do you need a destructor?
GameMechs::~GameMechs()
{
    //at this moment no because we dont have a heap member
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    
void GameMechs:: collectAsynInput()
{
        //from ppa 2; macui getinput
    if(MacUILib_hasChar())
    {
        input = MacUILib_getChar();
    }
    
    if(input == ' ') exitFlag = true;
    
}
char GameMechs::getInput() const
{
    return input;
}

int GameMechs::getScore() 
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
    clearInput();
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true; //true = player lost the game
}

void GameMechs::setInput(char this_input)
{
    input = this_input; //manually set input if needed
}

void GameMechs::clearInput()
{
    input = '\0'; //reset input to null
}

// More methods should be added here

int GameMechs::getMaxSpeed() const
{
    return MAX_SPEED;
}

int GameMechs::getMinSpeed() const
{
    return MIN_SPEED;
}

int GameMechs::getCurrentSpeed()
{
    return gamespeed;
}

int GameMechs::increment_speed()
{
    if(gamespeed < MAX_SPEED || gamespeed > MIN_SPEED)
        gamespeed++;
}

int GameMechs::decrease_speed()
{
    if(gamespeed < MAX_SPEED || gamespeed > MIN_SPEED)
        gamespeed--;
}

void GameMechs::generateFood(objPos blockOff)
{
    // int generatedItems = 0;
    // int xRange = getBoardSizeX();
    // int yRange = getBoardSizeY();
    // int ascii_range = rand() % 3; // three options for ASCII 
    // int i = 0;

    // //generate random food from ascii
    // while(generatedItems < listSize){
    // do
    // {}
    // int x_random = 0, y_random = 0;
    // char food_symbol;
    // bool unique = false; 

    // // while(!unique){
    // // Assume the new random position and symbol are unique
    //     unique = true;

    //     //generates random coordinates within range (1-17)
    //     x_random = (rand() % xRange) + 1; 
    //     y_random = (rand() % yRange) + 1;

    //     //generates random ASCII char
    //     if (ascii_range == 0)
    //         food_symbol = '0' + rand() % 10; //range is 0-9
    //     else if (ascii_range == 1)
    //         food_symbol = 'a' + rand() % 26; //range a-z : 97-122 ... 25 difference, so range here is 0-25
    //     else
    //         food_symbol = 'A' + rand() % 26; //ascii range 65-90

    //     //Important checks to ensure no repeated coordinates or food items:
    //     if (x_random == blockOff.pos->x && y_random == blockOff.pos->y) 
    //         //checks if food pos is the same as the player
    //         unique = false;  // Not a unique position
    //     for (i = 0; i < generatedItems && unique; i++) 
    //     { 
    //         //check through all the iterations if repeated coordinates
    //         if (food[i].pos->x == x_random && food[i].pos->y == y_random) 
    //         {
    //             unique = false; // Not a unique position
    //             break;
    //         }
    //     }
    //     for (i = 0; i < generatedItems && unique; i++) 
    //     { 
    //         //checks if the symbol is repeated
    //         if (food[i].symbol == food_symbol) 
    //         { 
    //             unique = 0; // Not a unique character
    //             break;
    //         }   
    //     }
    // }
    // //if PASSED all checks: both positions and symbol are unique (=1)
    // if (unique) 
    // { 
    //     food[generatedItems] = {x_random, y_random, food_symbol};
    //     generatedItems++; // Move to next item
    // }
    // }
}


objPos GameMechs::getFoodPos() const
{
    return food;
}
