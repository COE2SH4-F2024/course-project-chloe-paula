#ifndef OBJPOS_H
#define OBJPOS_H


/*
    This class holds the coordinates (x,y) and symbol of game objects:
        - snake
        - food
        
    Allows flexibility when dealing with dynamically sized game lists/grid
    by using the pos pointer.
*/

// Represents the position of any object on the 2D grid
typedef struct 
{
    int x;
    int y;
} Pos;

class objPos
{
    public:
        Pos* pos;       //  Pointer to Pos structure for position data
        char symbol;    //  Character symbol for objects (ex. snake, food)

        //  Default constructor: initializes object
        objPos();

        //  Constructor with input position and symbol
        objPos(int xPos, int yPos, char sym);
        
        //  Destructor: 
        ~objPos();

        //  Copy Constructor:
        //  (used to assign one objPos object to another)
        objPos(const objPos &o);

        //  Copy assignment operator:
        //  (used to assign one objPos object to another)
        objPos& operator=(const objPos &o);
        
        // Setter functions
        void setObjPos(objPos o); 
        void setObjPos(int xPos, int yPos, char sym);  

        // Getter functions
        objPos getObjPos() const;
        char getSymbol() const;
        char getSymbolIfPosEqual(const objPos* refPos) const;
        
        // Get the symbol if the position mathes another objPos
        bool isPosEqual(const objPos* refPos) const;
};

#endif