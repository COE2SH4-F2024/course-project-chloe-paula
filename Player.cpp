#include "Player.h"
#include "MacUILib.h"

//  Constructor for the Player class
//  Initializes the player's position and direction.
Player::Player(GameMechs* thisGMRef)
{
    // Set reference to the GameMechs instance
    mainGameMechsRef = thisGMRef;

    //Initialize the player position list
    playerPosList = new objPosArrayList();

    // Set initial direction (not moving)
    myDir = STOP;

    // Create the initial head position at the center of the board
    objPos headPos(thisGMRef->getBoardSizeX()/2,
                   thisGMRef->getBoardSizeY()/2,
                   '@');    //snake head
    
    //  Insert head into the player's position list
    playerPosList->insertHead(headPos);
    
}


//  Destructor for the Player class
// Deletes the dynamically allocated objPosArrayList.
Player::~Player()
{
    delete playerPosList;
}


//  Returns the reference to the player's position list (snake body).
//  A pointer to the player’s position list.
objPosArrayList* Player::getPlayerPos() const
{
    return playerPosList;
}


//  Updates the direction of the player based on input.
//  Prevents the player from reversing direction 
void Player::updatePlayerDir()
{
    // Get input from the game mechanics
    char input = mainGameMechsRef->getInput(); 

    if(input != 0) // Ensure the input is valid
    {
        switch(input)
        {                      
            case 'w': case 'W': // Move up
                if(myDir != DOWN) 
                    myDir = UP;
                break;
            case 's': case 'S': // Move down
                if (myDir != UP)
                    myDir = DOWN;
                break;
            case 'a': case 'A': // Move left
                if (myDir != RIGHT)
                    myDir = LEFT;
                break;
            case 'd' : case 'D': // Move right
                if (myDir != LEFT)
                    myDir = RIGHT;
                break;
            default:
                break;
        }
        mainGameMechsRef->clearInput(); // Clear input to prevent repeating actions
    }
}


//  Return the new position of the snake head depending on the direction of snake
objPos Player::getNextHeadPos() const
{
    //  Easy access to board dimensions:
    int board_H = mainGameMechsRef->getBoardSizeY();
    int board_W = mainGameMechsRef->getBoardSizeX();
    
    //  Create a temporary object for the new head position
    objPos currentHead = playerPosList->getHeadElement();
    objPos tempHead = currentHead;

    switch(myDir)
    {
        case UP:
            if(currentHead.pos->y > 1)
                tempHead.pos->y--;  // Move up
            else
                tempHead.pos->y = board_H - 2; // Wrap around to bottom
            break;  
        case DOWN:
            if(currentHead.pos->y < board_H - 2)
                tempHead.pos->y++;  // Move down
            else
                tempHead.pos->y = 1; // Wrap around to top
            break;
        case LEFT:
            if(currentHead.pos->x > 1)
                tempHead.pos->x--;  // Move left
            else 
                tempHead.pos->x = board_W - 2; // Wrap around to right
            break;
        case RIGHT:
            if(currentHead.pos->x < board_W -2)
                tempHead.pos->x++;  // Move right
            else
                tempHead.pos->x = 1; // Wrap around to left
            break;
    }

    return tempHead;
}



//  Moves the player (snake) one step based on the current direction
//  Handles collisions with the body and food
//  Stops the game if the snake collides with itself
void Player::movePlayer()
{
    //  Check for collisions with the snake’s own body
    bool selfcollided = checkSelfCollision();
    bool foodConsumed = checkFoodConsumption();

    //  If collision with body, stop the game
    if(selfcollided)
    {
        myDir = STOP;
        mainGameMechsRef->setLoseFlag();    // Game over!
        mainGameMechsRef->setExitTrue();
        return;
    }
    //  Check if game won
    else if(mainGameMechsRef->getWinGameStatus())
    {
        myDir = STOP;
        mainGameMechsRef->setWinGameFlag();
    }

    // If no collision and the player is moving,
    // update the new head position AND
    // check other conditions (i.e food and self collision)
    if(myDir!=STOP)
    {
        objPos newHead = getNextHeadPos();
        
        //  Check food collision:
        if(foodConsumed)
        {
            //  Generate new food if no more food
            mainGameMechsRef->generateFood(playerPosList);
        }
        else    
        {
            //  Continue normal snake movement
            playerPosList->insertHead(newHead);
            playerPosList->removeTail();  
        }

    }
}



//  Method checks if snake head ate/collided with a food item
//  If yes, different special effects will occur depending the food type (num, upper and lower case letter)
//  If yes, food bucket of items will decrease 
bool Player::checkFoodConsumption()
{

    // Get the head position of the snake
    objPos head = playerPosList->getHeadElement();
 
    // Get the food position list from GameMechs
    objPosArrayList* foodBucket = mainGameMechsRef->getFoodPos();
 
    // Assume snake did not consume food
    bool snakeAte = false;

    // Check if the head matches the food position
    for(int i = 0; i < foodBucket->getSize(); i++)
    {
        objPos food = foodBucket->getElement(i);

        if(head.pos->x == food.pos->x && head.pos->y == food.pos->y)
        {
            if(food.symbol >= '0' && food.symbol <= '9')  // Numbers case
            {
                // # 1 Special food effect: decrease snake body by one
                if(playerPosList->getSize() > 1)
                {
                    playerPosList->removeTail();
                }
            }
            else if(food.symbol >= 'A' && food.symbol <= 'Z') // Upper- case letter
            {
                // # 3 Special food effect: increase score by 10
                mainGameMechsRef->SuperScore();
                increasePlayerLength(); // Grow snake

            }
            else // Lower-case letter 
            {
                // # 4 Special food effect: increase score by 1
                mainGameMechsRef->incrementScore();
                increasePlayerLength(); // Grow snake
            }

            foodBucket->removeElement(i);                   // Remove the consumed food            
            snakeAte = true;                                // Food was consumed 
            break;                                          //  Only one food consumed at a time     

        }
    }
    return snakeAte;
}


void Player::increasePlayerLength()
{
    //  Use method to get new head position depending on movement
    objPos newHead = getNextHeadPos();

    //  Increase snake's body by adding the new head
    playerPosList->insertHead(newHead);
}



//  Checks if the snake’s head collides with its body.
//  True if there is a collision with the body; false otherwise.
bool Player::checkSelfCollision()
{
    // Get head element of snake
    objPos head = playerPosList->getHeadElement();  
    
    // bool will be returned at the end
    bool selfcollided = false;

    //  Iterate through the snake's body
    //  Check if any part of the body collides with the head
    for(int i = 1; i < playerPosList->getSize();i++)    //start at one to not include the head at index = 0
    {
        objPos body = playerPosList->getElement(i);    // get each part of body
        if(head.pos->x == body.pos->x && head.pos->y == body.pos->y)
        {
            selfcollided = true; // collision detected
            break;
        }
    }

    return selfcollided;
}