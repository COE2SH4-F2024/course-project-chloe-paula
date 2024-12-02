#include "objPos.h"

// Default constructor
objPos::objPos()
{
    // Initializes the position and the symbol
    pos = new Pos;
    pos->x = 0;
    pos->y = 0;
    symbol = 0;     //NULL
}


// Constructor with specific position (x, y) and symbol
objPos::objPos(int xPos, int yPos, char sym)
{
    pos = new Pos;
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}


// Destructor
objPos::~objPos()
{
   // Delete the dynamically allocated Pos object 
    delete pos;
}


// Copy constructor
objPos::objPos(const objPos &o)
{
    // Creates a new objPos by copying the pos & symbol from other object
    pos = new Pos;
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}


// Copy assignment operator
objPos &objPos::operator=(const objPos &o)
{
    if(this != &o)              //  Prevents self-assigning
    {
        delete pos;             // Free existing memory
        pos = new Pos(*o.pos);  // Allocate new memory
        pos->x = o.pos->x;
        pos->y = o.pos->y;
        symbol = o.symbol;
    }
    return *this;
}


// Set position using another objPos object
void objPos::setObjPos(objPos o)
{
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}


// Set position manually using x, y, and symbol
void objPos::setObjPos(int xPos, int yPos, char sym)
{
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}


// Get the position of the object as a new objPos object
objPos objPos::getObjPos() const
{
    objPos returnPos;
    returnPos.setObjPos(pos->x,pos->y,symbol); //using setter 
    return returnPos;
}


// Get the symbol of the object
char objPos::getSymbol() const
{
    return symbol;
}


// Get the symbol if the position matches another objPos
char objPos::getSymbolIfPosEqual(const objPos* refPos) const
{
    if(isPosEqual(refPos))
        return symbol;
    else
        return 0;
}


// Check if the position of this object is equal to another objPos object
bool objPos::isPosEqual(const objPos* refPos) const
{
    // Compare both positions
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}