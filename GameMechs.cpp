#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;
    boardSizeX = 20; 
    boardSizeY = 10;
    MAX_SPEED = 5;
    MIN_SPEED = 1; 
    gamespeed = 3;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    boardSizeX = boardX;
    boardSizeY = boardY;
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    //at this moment no because we dont have a heap member
}

bool GameMechs::getExitFlagStatus() 
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() 
{
    return loseFlag;
}
    

char GameMechs::getInput() 
{
    //from ppa 2; macui getinput
    if(MacUILib_hasChar())
    {
        input = MacUILib_getChar();
    }
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