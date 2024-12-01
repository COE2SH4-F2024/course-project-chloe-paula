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




void GameMechs::generateFood(objPosArrayList* blockOff)
{
    bool validFood = false;
    int x_random, y_random;
    char newFoodSym;

    int xRange = getBoardSizeX();
    int yRange = getBoardSizeY();

    // //generate random food from ascii
    while(!validFood)
    {
    
        x_random = (rand() % xRange) + 1; 
        y_random = (rand() % yRange) + 1;
        
        //Generate random fool: (Three options types: num, a, A) 
        int ascii_range = rand() % 3;  
        if (ascii_range == 0)
            newFoodSym = '0' + rand() % 10; //range is 0-9
        else if (ascii_range == 1)
           newFoodSym = 'a' + rand() % 26; //range a-z : 97-122 ... 25 difference, so range here is 0-25
        else
            newFoodSym = 'A' + rand() % 26; //ascii range 65-90

        //check if new food is overlapping with player:
        for(int i = 0; i < blockOff->getSize(); i++)
        {
            for(int j = 0; j < blockOff->getSize(); j++)
            {
                if (x_random != blockOff->getElement(i).pos->x && y_random != blockOff->getElement(i).pos->y && food.symbol != blockOff->getElement(i).symbol) 
                validFood = true;  //valid new food
            }
        }
        
    }

    food.pos->x = x_random;
    food.pos->y = y_random;
    food.symbol = newFoodSym;

}


objPos GameMechs::getFoodPos() const
{
    return food;
}
