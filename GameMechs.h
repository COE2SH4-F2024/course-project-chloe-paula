#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

/**
    This class controls the game mechanics for the snake game:
        - input handling,
        - score tracking
        - speed control
        - food generation
 */

class GameMechs
{
    private:
        char input;     //  Holds most recent input collected from user
        bool exitFlag;  //  Indicates if game is over
        bool loseFlag;  //  Indicates if player lost, game over
        int score;      //  Holds current score of player
        int boardSizeX; //  Width of board
        int boardSizeY; //  Height of board
        int MAX_SPEED;  //  Max speed of game
        int MIN_SPEED;  //  Min speed of game
        int gamespeed;  //  Initiaul speed of game
        
        objPosArrayList* foodItems;    //  List of food items 

    public:
        //  Default Constructor: 
        //      initializes game mechanic-related parameters
        GameMechs();

        //  Constructor with custom board sizes
        GameMechs(int boardX, int boardY);

        // Destructor
        ~GameMechs(); 

        //  Getter Methods for Game State
        bool getExitFlagStatus() const;
        bool getLoseFlagStatus() const;

        //  Setter Methods for Game State
        void setExitTrue();
        void setLoseFlag();

        //   Methods for managing player input
        void collectAsynInput();
        char getInput() const;
        void setInput(char this_input);
        void clearInput();

        //   Getter Methods for board size
        int getBoardSizeX() const;
        int getBoardSizeY() const;
        
        //   Methods for managing score
        int getScore();
        void incrementScore();
        
        //   Methods for managing speed
        int getMaxSpeed() const;
        int getMinSpeed() const;
        int getCurrentSpeed();
        int increment_speed();
        int decrease_speed();
        
        //   Methods for food
        void generateFood(objPosArrayList* blockOff);
        bool checkFoodConsumption(objPosArrayList* playerPos);
        objPosArrayList* getFoodItems() const;

};
#endif