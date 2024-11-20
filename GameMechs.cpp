#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;
    boardSizeX = 30; //on page 14 of manual: 
    //recommended board size (it looks ugly tho)
    boardSizeY = 15;
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

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
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
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore()
{
    
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
