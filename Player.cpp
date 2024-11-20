#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included... initialize player details
    playerPos.pos->x = mainGameMechsRef->getBoardSizeX()/2; //player pos in middle
    playerPos.pos->y = mainGameMechsRef->getBoardSizeY()/2; //player pos in middle
    playerPos.symbol = '@'; //player symbol
}


Player::~Player()
{
    // delete any heap members here
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPos;
}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef->getInput(); 

            // PPA2/3 input processing logic for direction!!   
     //note change direction = myDir
}

void Player::movePlayer()
{
    updatePlayerDir();    
    // PPA3 Finite State Machine logic
    //switch cases logic... switch according to direction 
}

// More methods to be added