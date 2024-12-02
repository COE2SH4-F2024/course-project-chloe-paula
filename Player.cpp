#include "Player.h"
#include "MacUILib.h"

//  Constructor for the Player class
//  Initializes the player's position and direction.
//  Reference to the main GameMechs object.
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
            case '+': // Increase speed
                if(mainGameMechsRef->getCurrentSpeed() < mainGameMechsRef->getMaxSpeed())
                    mainGameMechsRef->increment_speed();
                break;
            case '-': // Decrease speed
                if(mainGameMechsRef->getCurrentSpeed() > mainGameMechsRef->getMinSpeed())
                    mainGameMechsRef->decrease_speed();
                break;
            default:
                break;
        }
        mainGameMechsRef->clearInput(); // Clear input to prevent repeating actions
    }
}


//  Moves the player (snake) one step based on the current direction
//  Handles collisions with the body and food
//  Stops the game if the snake collides with itself
void Player::movePlayer()
{

    //  Easy access to board dimensions:
    int board_H = mainGameMechsRef->getBoardSizeY();
    int board_W = mainGameMechsRef->getBoardSizeX();
    
    //  Check for collisions with the snake’s own body
    bool collided = checkSelfCollision();

    //  Create a temporary object for the new head position
    objPos currentHead = playerPosList->getHeadElement();
    objPos tempHead = currentHead;

    //  If collision with body, stop the game
    if(checkSelfCollision())
    {
        myDir = STOP;
        mainGameMechsRef->setLoseFlag();    // Game over!
        return;
    }

    // If no collision and the player is moving, update the head position
    if(myDir!=STOP)
    {
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
    }

    //  Check food collision:
    if(mainGameMechsRef->checkFoodConsumption(playerPosList))
    {
        //  If food consumed, grow snake
        playerPosList->insertHead(tempHead);

        //  Also generate new food
        mainGameMechsRef->generateFood(playerPosList);
    }
    else    
    {
        //  If no food consumed, move snake as
        playerPosList->insertHead(tempHead);
        playerPosList->removeTail();  
    }
    //  Get current food position
    // objPosArrayList* currentFood = mainGameMechsRef->getFoodItems();
    
    // // Check if the head collides with food
    // if(currentHead.pos->x == currentFood->getElement.pos->x && currentHead.pos->y == currentFood.pos->y)
    // {
    //     //  If food is eaten: increase score and grow snake
    //     mainGameMechsRef->incrementScore();
    //     playerPosList->insertHead(tempHead);    // add the new head pos to the snake
        
    //     //Generate a new food item at a random valid position
    //     mainGameMechsRef->generateFood(playerPosList);
    // }
    // else
    // {       
    //     //  If no food eaten, move the snake as normal 
    //         playerPosList->insertHead(tempHead);
    //         // remove the tail (snake body moves forward)
    //         playerPosList->removeTail();  
    // }
}
   

//  Checks if the snake’s head collides with its body.
//  True if there is a collision with the body; false otherwise.
bool Player::checkSelfCollision()
{
    objPos head = playerPosList->getHeadElement();  // Get head element of snake
    objPos body;
    bool collide = false;

    //  Iterate through the snake's body
    //  Check if any part of the body collides with the head
    for(int i = 1; i < playerPosList->getSize();i++)
    {
        body = playerPosList->getElement(i);    // get each part of body
        if(head.pos->x == body.pos->x && head.pos->y == body.pos->y)
        {
            collide = true; // collision detected
            break;
        }
    }

    return collide;
}