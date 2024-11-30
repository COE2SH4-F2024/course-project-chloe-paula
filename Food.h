#ifndef FOOD_H
#define FOOD_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

//file holds Food mechanics

class Food
{
    private:
        //food array list size
        int listSize;

        //holds the most recent generated food position & its ASCII symbol:
        objPos* food; 

        //holds the most recent player position:
        objPos playerPos;

    public:
        //initialize game mechanic-related parameters
        Food();
        ~Food(); 

        //random food generating algorithm // copy from PPA3
        //blockOff should contain: player position... which 
        //the new foOD SHOULD NOT be generated
        void generateFood(objPos blockOff);

        //getter method for obtaining a copy of current food position
        objPos getFoodPos(/*int index*/) const;
        int getListSize() const;
        // char printFoodSymbol();
};

#endif