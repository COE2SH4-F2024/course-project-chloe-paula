#include "objPos.h"

objPos::objPos()
{
    pos = new Pos;
    pos->x = 0;
    pos->y = 0;
    symbol = 0; //NULL
}

objPos::objPos(int xPos, int yPos, char sym)
{
    pos = new Pos;
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

// Respect the rule of six / minimum four
// [TODO] Implement the missing special member functions to meet the minimum four rule

objPos::~objPos()
{
    delete pos;
}

//copy constructor
objPos::objPos(const objPos &o)
{
    pos = new Pos;
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

//copy assignment operator
objPos &objPos::operator=(const objPos &o)
{
    if(this != &o) //to make sure no self-assigning
    {
        delete pos; // free existing memory
        pos = new Pos; //allocate new memory
        pos->x = o.pos->x;
        pos->y = o.pos->y;
        symbol = o.symbol;
        // *pos = *o.pos;
        // symbol = o.symbol;
    }
    return *this;
}

void objPos::setObjPos(objPos o)
{
    //this sets position using another objPos (o)
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

void objPos::setObjPos(int xPos, int yPos, char sym)
{
    //this manually sets position using inputs
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

objPos objPos::getObjPos() const
{
    //get the position of player
    objPos returnPos;
    returnPos.setObjPos(pos->x,pos->y,symbol); //using helper funciton
    return returnPos;
}

char objPos::getSymbol() const
{
    //get the symbol of player
    return symbol;
}

bool objPos::isPosEqual(const objPos* refPos) const
{
    //checks if positions are equal
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}

char objPos::getSymbolIfPosEqual(const objPos* refPos) const
{
    //checks if symbol positions are equal
    if(isPosEqual(refPos))
        return symbol;
    else
        return 0;
}
