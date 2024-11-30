#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    playerPosList = new objPosArrayList();
    myDir = STOP;

    objPos headPos(thisGMRef->getBoardSizeX()/2,
                    thisGMRef->getBoardSizeY()/2,
                    '@'
                );
    playerPosList->insertHead(headPos);

    // more actions to be included... initialize player details
    // currentHead.pos->x = mainGameMechsRef->getBoardSizeX()/2; //player pos in middle
    // currentHead.pos->y = mainGameMechsRef->getBoardSizeY()/2; //player pos in middle
    // currentHead.symbol = '*'; //player symbol
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos() const
{
    // return the reference to the currentHead arrray list
    return playerPosList;
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

    //Iteration 3:
    //  create temp objPos to calculate the new head position
    //      probably should get the head elements of the playerPosList
    //      as a good starting point.

    objPos currentHead = playerPosList->getHeadElement();
    objPos tempHead = playerPosList->getHeadElement();
    if(myDir != STOP)
    {
        switch(myDir)
        {
            //iteration 3:
                //calculatte new position of the head,
                //using the temp objPos
            case UP:
                if(currentHead.pos->y > 1)
                    tempHead.pos->y--; 
                else
                    //if reached the upper boarder limit -- wraps around to row 9
                    tempHead.pos->y = board_H - 2; 
                break;
            case DOWN:
                if(currentHead.pos->y < board_H - 2)
                    //move within bounds
                    tempHead.pos->y++; 
                else
                    tempHead.pos->y = 1; //reset to limit
                break;
            case LEFT:
                if(currentHead.pos->x > 1)
                    tempHead.pos->x--;
                else //if reached limit -- wrap around
                    tempHead.pos->x = board_W - 2;
                break;
            case RIGHT:
                if(currentHead.pos->x < board_W -2)
                    //move within bounds
                    tempHead.pos->x++;
                else
                    tempHead.pos->x = 1;
                break;
        }
    } 

    //Iter 3: insert temp objPos to the head of the list
    playerPosList->insertHead(tempHead);
    //Iter 3 later feature 2: 
            //check if the new temp objPos overlaps 
            //the new food position (get it from the GameMechs class)

}       


// More methods to be added