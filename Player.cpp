#include "Player.h"
#include "MacUILib.h"

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
    bool collided = checkSelfCollision();

    //Iteration 3:
    //  create temp objPos to calculate the new head position
    //      probably should get the head elements of the playerPosList
    //      as a good starting point.

    objPos currentHead = playerPosList->getHeadElement();
    objPos tempHead = currentHead;

    if(collided){
        myDir = STOP;
        mainGameMechsRef->setLoseFlag();
        return;

    }
    if(myDir!=STOP){
    
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
         //most recent food position + symbol
        objPos currentFood = mainGameMechsRef->getFoodPos();
        // objPosArrayList* currentPlayer = playerPosList();
        // switch(myDir){
        //     case UP:
        //         if(playerPosList->getElement((tempHead.getObjPos().pos->x)-1).getSymbol()=='@'){
        //             collided = true;
        //         }
        //     case DOWN:
        //         if(playerPosList->getElement((tempHead.getObjPos().pos->x)+1).getSymbol()=='@'){
        //             collided = true;
        //         }
        //     case LEFT:
        //         if(playerPosList->getElement((tempHead.getObjPos().pos->y)-1).getSymbol()=='@'){
        //             collided = true;
        //         }
        //     case RIGHT:
        //         if(playerPosList->getElement((tempHead.getObjPos().pos->y)+1).getSymbol()=='@'){
        //             collided = true;
        //         }
        // }

        if(currentHead.pos->x == currentFood.pos->x && currentHead.pos->y == currentFood.pos->y)
        {
            //Increment score on collision:
            mainGameMechsRef->incrementScore();
            playerPosList->insertHead(tempHead);
            //Generate a new food item at a rand valid position:
            mainGameMechsRef->generateFood(playerPosList);

            // MacUILib_printf("Food eaten! New food generated. Current score: %d\n", mainGameMechsRef->getScore());

        }
        else
        {       
                
                playerPosList->insertHead(tempHead);
                playerPosList->removeTail();  
                

        }
    } 

   
    //Iter 3: insert temp objPos to the head of the list
    
    //Iter 3 later feature 2: 
            //check if the new temp objPos overlaps 
            //the new food position (get it from the GameMechs class)

            //use isPosEqual() method from objPos class

            //If overlapped, that means food consumed, DO NOT REMOVE SNAKE TAIL
            //and take the respective actions to increase score

            //if NOT overlapped, remove tail and complete movement
}       


// More methods to be added
bool Player::checkSelfCollision(){
    objPos head = playerPosList->getHeadElement();
    objPos body;
    bool collide = false;
    //objPos tempHead = playerPosList->getHeadElement();

    for(int i = 1; i < playerPosList->getSize();i++){
        body = playerPosList->getElement(i);
    // if(myDir!=STOP){
    //     switch(myDir){
    //         case UP:
    //             if(playerPosList->getElement((tempHead.getObjPos().pos->x)-1).getSymbol()=='@'){
    //                 collide = true;
    //                 break;
    //             }
    //         case DOWN:
    //             if(playerPosList->getElement((tempHead.getObjPos().pos->x)+1).getSymbol()=='@'){
    //                 collide = true;
    //                 break;
    //             }
    //         case LEFT:
    //             if(playerPosList->getElement((tempHead.getObjPos().pos->y)-1).getSymbol()=='@'){
    //                 collide = true;
    //                 break;
    //             }
    //         case RIGHT:
    //             if(playerPosList->getElement((tempHead.getObjPos().pos->y)+1).getSymbol()=='@'){
    //                 collide = true;
    //                 break;
    //             }
    //     }
    // }
        if(head.pos->x == body.pos->x && head.pos->y == body.pos->y){
            collide = true;
            break;
        }
    }

    return collide;
}