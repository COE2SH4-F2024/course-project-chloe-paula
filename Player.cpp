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
     if(input != 0)  // if not null character
    {
        switch(input)
        {                      
            // case ' ':  // exit
            //     exitFlag = 1;
            //     break;
            case 'w': //set to UP if not going down
                if(myDir != DOWN){
                    myDir = UP;
                }
                break;
            case 'a': //set to RIGHT if not going left
                if(myDir != RIGHT){
                    myDir = LEFT;
                }
                break;
            case 's': //set to DOWN if not going up
                if(myDir != UP){
                    myDir = DOWN;
                }
                break;
            case 'd':
                if(myDir != LEFT){
                    myDir = RIGHT;
                }
                break;

            default:
                break;
        }
        input = 0;
    }
}

void Player::movePlayer()
{
    updatePlayerDir();    
    // PPA3 Finite State Machine logic
    //switch cases logic... switch according to direction 
    switch(myDir){
        case LEFT:
            if (playerPos.pos->x == 1){
                playerPos.pos->x = 18;
            }else{
                playerPos.pos->x--;
            }
            break;
        case RIGHT:
            if (playerPos.pos->x == 18){
                playerPos.pos->x = 1;
            }else{
                playerPos.pos->x++;
            }
            break;
        case UP:
            if (playerPos.pos->y == 1){
                playerPos.pos->y = 8;
            }else{
                playerPos.pos->y--;
            }
            break;
        case DOWN:
            if (playerPos.pos->y == 8){
                playerPos.pos->y = 1;
            }else{
                playerPos.pos->y++;
            }
        default:
            break;
    }
}

// More methods to be added