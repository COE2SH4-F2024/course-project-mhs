#include "objPos.h"
#include <iostream>

objPos::objPos() 
{
    pos = new Pos();  // Always allocate memory
    pos->x = 0;
    pos->y = 0;
    symbol = ' ';
}

objPos::objPos(int xPos, int yPos, char sym)
 {
    pos = new Pos();
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

objPos::~objPos() 
{
    if (pos) {
        delete pos;
        pos = nullptr;
    }
}

objPos::objPos(const objPos& o) {
    pos = new Pos(*o.pos);  // Deep copy
    symbol = o.symbol;
}

objPos& objPos::operator=(const objPos& other) {
    if (this != &other) {
        delete pos;  // Free existing memory
        pos = new Pos(*other.pos);  // Deep copy
        symbol = other.symbol;
    }
    return *this;
}


void objPos::setObjPos(objPos o) 
{
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

void objPos::setObjPos(int xPos, int yPos, char sym) 
{
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

objPos objPos::getObjPos() const
{
    objPos returnPos;
    returnPos.setObjPos(pos->x,pos->y,symbol); //using setter
    return returnPos;
}

char objPos::getSymbol() const {
    return symbol;
}

char objPos::getSymbolIfPosEqual(const objPos* refPos) const 
{
    return isPosEqual(refPos) ? symbol : 0;
}

bool objPos::isPosEqual(const objPos* refPos) const 
{
    if (!refPos || !refPos->pos || !pos) 
    {
        return false;
    }
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}

