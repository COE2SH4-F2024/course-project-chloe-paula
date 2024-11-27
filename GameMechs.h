#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>
#include <iostream>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

class GameMechs
{
    private:
        char input; //holds the most recent input collected via MacUILib_getChar()
        bool exitFlag;
        bool loseFlag; //recording if the player has lost
        //shouldn't be set to true if the player presses the exit key to end game
        //use this flag to determine what messages to display at the end of the game
        int score; //holds current score of player
        int boardSizeX;
        int boardSizeY;
        int MAX_SPEED;
        int MIN_SPEED;
        int gamespeed;

        objPos food; 

    public:
        //initialize game mechanic-related parameters
        GameMechs();
        GameMechs(int boardX, int boardY);
        // is this one needed at all? Do we have heap members?
        ~GameMechs(); 

        bool getExitFlagStatus() const; 
        void setExitTrue();
        bool getLoseFlagStatus() const ;
        void setLoseFlag();

        //clear most recent collected ASCII input from the field
        //use this to make sure no input is double-processed
        char getInput() ;
        void setInput(char this_input);
        void clearInput();

        int getBoardSizeX() const;
        int getBoardSizeY() const;
        
        int getScore();

        //setter for the score field
        //assumption is that the score can only be 
        //increased by 1 at a time per food item collected
        //... maybe change this method later on to increase
       //score by more than 1?
        void incrementScore();
        
        // More methods should be added here
        int getMaxSpeed() const;
        int getMinSpeed() const;
        int getCurrentSpeed();
        int increment_speed();
        int decrease_speed();


};

#endif