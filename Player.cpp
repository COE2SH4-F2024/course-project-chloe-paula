#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included... initialize player details
    playerPos.pos->x = mainGameMechsRef->getBoardSizeX()/2; //player pos in middle
    playerPos.pos->y = mainGameMechsRef->getBoardSizeY()/2; //player pos in middle
    playerPos.symbol = '*'; //player symbol
}


Player::~Player()
{
    // delete any heap members here
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPos;
    // return the reference to the playerPos arrray list

}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef->getInput(); 

            // PPA2/3 input processing logic for direction!!   
     //note change direction = myDir
     if(input != 0) 
    {
        switch(input)
        {                      
            case 'w': case 'W':
                if(myDir != DOWN) 
                    myDir = UP;
                break;
            case 's': case 'S':
                if (myDir != UP)
                    myDir = DOWN;
                break;
            case 'a': case 'A': 
                if (myDir != RIGHT)
                    myDir = LEFT;
                break;
            case 'd' : case 'D':
                if (myDir != LEFT)
                    myDir = RIGHT;
                break;
            case '+': //increment speed
                if(mainGameMechsRef->getCurrentSpeed() < mainGameMechsRef->getMaxSpeed())
                    mainGameMechsRef->increment_speed();
                break;
            case '-': //lower speed
                if(mainGameMechsRef->getCurrentSpeed() > mainGameMechsRef->getMinSpeed())
                    mainGameMechsRef->decrease_speed();
                break;
            default:
                break;
        }
        mainGameMechsRef->clearInput();
    }
}

void Player::movePlayer()
{
    //updatePlayerDir();    
    // PPA3 Finite State Machine logic
    //switch cases logic... switch according to direction 

    //easy access to board dimensions:
    int board_H = mainGameMechsRef->getBoardSizeY();
    int board_W = mainGameMechsRef->getBoardSizeX();

    if(myDir != STOP)
    {
        switch(myDir)
        {
            case UP:
                if(playerPos.pos->y > 1)
                    playerPos.pos->y--; 
                else
                    //if reached the upper boarder limit -- wraps around to row 9
                    playerPos.pos->y = board_H - 2; 
                break;
            case DOWN:
                if(playerPos.pos->y < board_H - 2)
                    //move within bounds
                    playerPos.pos->y++; 
                else
                    playerPos.pos->y = 1; //reset to limit
                break;
            case LEFT:
                if(playerPos.pos->x > 1)
                    playerPos.pos->x--;
                else //if reached limit -- wrap around
                    playerPos.pos->x = board_W - 2;
                break;
            case RIGHT:
                if(playerPos.pos->x < board_W -2)
                    //move within bounds
                    playerPos.pos->x++;
                else
                    playerPos.pos->x = 1;
                break;
        }
    } 
}


// More methods to be added