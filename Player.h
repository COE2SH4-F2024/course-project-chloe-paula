#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"          // For main game mechanics
#include "objPos.h"             // For handling individual snake positions
#include "objPosArrayList.h"    // For handling snake body positions (list)

/*

This class manages the player's snake: 
        movement, 
        direction updates,
        collision detection


*/

class Player
{
    public:
        // Possible movement directions for snake
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};

        // Constructs a Player object
        // thisGMRef: reference to GameMechs instance
        Player(GameMechs* thisGMRef);

        // Destructor
        ~Player();

        // Gets the player's current position list
        // A pointer to the objPosArrayList, which contains the snake's positions
        objPosArrayList* getPlayerPos() const;    

        //  Updates the player's movement direction based on input
        void updatePlayerDir();

        // Moves the player based on the current direction.
        // Handles collisions with food and itself.
        void movePlayer();

        // Checks if the snake's head collides with its body
        bool checkSelfCollision();

        // bool checkFoodConsumption();

        // void increasePlayerLength();

    private:
        // Dynamic list representing the snake's body
        objPosArrayList* playerPosList; 

        // Current movement direction of the snake
        enum Dir myDir;

        // Reference to the GameMechs object
        GameMechs* mainGameMechsRef;
        
};

#endif