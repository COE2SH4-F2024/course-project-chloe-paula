#include "Food.h"
#include "GameMechs.h"
#include "MacUILib.h"
// #include <iostream>
#include <ctime> //for seeding rand()
#include <cstdlib> //for rand()


//global pointer to GameMechs class
GameMechs *GM;



///FOOD CLASS
Food::Food()
{
    listSize = 5;
    
    //Dynamically allocate the food position
    food = new objPos(0,0,'F');
    
    //must access player position:

}



Food::~Food()
{
    delete food;
} 




//random food generating algorithm // copy from PPA3
//blockOff = player position... which 
//the new foOD SHOULD NOT be generated
void Food::generateFood(objPos blockOff)
{
    // int generatedItems = 0;
    // int xRange = GM->getBoardSizeX();
    // int yRange = GM->getBoardSizeY();
    // int ascii_range = rand() % 3; // three options for ASCII 
    // int i = 0;

    // //generate random food from ascii
    // while(generatedItems < listSize){
    //     int x_random = 0, y_random = 0;
    //     char food_symbol;
    //     bool unique = false; 

    //     while(!unique){
    //     // Assume the new random position and symbol are unique
    //         unique = true;

    //         //generates random coordinates within range (1-17)
    //         x_random = (rand() % xRange) + 1; 
    //         y_random = (rand() % yRange) + 1;

    //         //generates random ASCII char
    //         if (ascii_range == 0)
    //             food_symbol = '0' + rand() % 10; //range is 0-9
    //         else if (ascii_range == 1)
    //             food_symbol = 'a' + rand() % 26; //range a-z : 97-122 ... 25 difference, so range here is 0-25
    //         else
    //             food_symbol = 'A' + rand() % 26; //ascii range 65-90

    //         //Important checks to ensure no repeated coordinates or food items:
    //         if (x_random == blockOff.pos->x && y_random == blockOff.pos->y) 
    //             //checks if food pos is the same as the player
    //             unique = false;  // Not a unique position
    //         for (i = 0; i < generatedItems && unique; i++) 
    //         { 
    //             //check through all the iterations if repeated coordinates
    //             if (food[i].pos->x == x_random && food[i].pos->y == y_random) 
    //             {
    //                 unique = false; // Not a unique position
    //                 break;
    //             }
    //         }
    //         for (i = 0; i < generatedItems && unique; i++) 
    //         { 
    //             //checks if the symbol is repeated
    //             if (food[i].symbol == food_symbol) 
    //             { 
    //                 unique = 0; // Not a unique character
    //                 break;
    //             }   
    //         }
    //     }
    //     //if PASSED all checks: both positions and symbol are unique (=1)
    //     if (unique) 
    //     { 
    //         food[generatedItems] = {x_random, y_random, food_symbol};
    //         generatedItems++; // Move to next item
    //     }
    // }

    int x,y;
    // char food_sym;
    do
    {
        x = rand() % (GM->getBoardSizeX() - 2) + 1;
        y = rand() % (GM->getBoardSizeY() - 2) + 1;

    } while (x == blockOff.pos->x && y == blockOff.pos->y /*&& food_sym == blockOff.symbol*/);
    
    food->setObjPos(x,y,'F');
}




//Getter method for obtaining a copy of current food position
objPos Food::getFoodPos(int index)
{
    //     //DETECT COLLISION
    // for(int i = 0; i < listSize; i++){
    //     if(playerPos.pos->x == food[i].pos->x && playerPos.pos->y == food[i].pos->y)
    //     {
    //         char collision_item = food[i].symbol;
    //         food[i].symbol = ' ';
    //     }
    // }

    // return food[index];
    //for now just do this cuz instructions are confusing and are based off 
    //only having one food item in iteration 2b

    return *food;

} 

//Getter method for size of food list
int Food::getListSize() const
{
    return listSize;
}

char Food::printFoodSymbol()
{
    MacUILib_printf("%c", food->getSymbol());
}