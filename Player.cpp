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
    updatePlayerDir();    
    // PPA3 Finite State Machine logic
    //switch cases logic... switch according to direction 
    if(myDir != STOP)
    {
        switch(myDir)
        {
            case UP:
                playerPos.pos->y--; //up = negative on cartesian of board
                if(playerPos.pos->y < 1) //reached the upper boarder limit
                    playerPos.pos->y = mainGameMechsRef->getBoardSizeY() - 1; //resets to lower limit = height
                break;
            case DOWN:
                playerPos.pos->y++; // increasing y moves char visually down (vise versa^)
                if(playerPos.pos->y > mainGameMechsRef->getBoardSizeY() - 1)
                    playerPos.pos->y = 1;
                break;
            case LEFT:
                playerPos.pos->x--;
                if(playerPos.pos->x == 1)
                    playerPos.pos->x = mainGameMechsRef->getBoardSizeX() - 1;
                break;
            case RIGHT:
                playerPos.pos->x++;
                if(playerPos.pos->x == mainGameMechsRef->getBoardSizeX() - 1)
                    playerPos.pos->x = 1;
                break;
        }
    } 
}


// More methods to be added