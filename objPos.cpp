#include "objPos.h"

objPos::objPos()
{
    pos = new Pos;
    pos->x = 0;
    pos->y = 0;
    symbol = ' '; //NULL
}


objPos::objPos(int xPos, int yPos, char sym) {
    pos = new Pos();
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

// Respect the rule of six / minimum four
// [TODO] Implement the missing special member functions to meet the minimum four rule

// deep copy

objPos::objPos(const objPos& o) 
{
    pos = new Pos{*o.pos};
    symbol = o.symbol;
}

// copy Assignment Operator
objPos& objPos::operator=(const objPos& other) {
    if (this != &other) {
        delete pos;
        pos = new Pos{*other.pos};
        symbol = other.symbol;
    }
    return *this;
}

// move Constructor
objPos::objPos(objPos&& other) noexcept 
    : pos(other.pos), symbol(other.symbol) {
    other.pos = nullptr;
}

// move Assignment Operator
objPos& objPos::operator=(objPos&& other) noexcept {
    if (this != &other) {
        delete pos;
        pos = other.pos;
        symbol = other.symbol;
        other.pos = nullptr;
    }
    return *this;
}

objPos::~objPos()
{
    delete pos;
}



// set object Position (by reference)
void objPos::setObjPos(const objPos& o) {
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

// set object Position (by values)
void objPos::setObjPos(int xPos, int yPos, char sym) {
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

objPos objPos::getObjPos() const
{
    objPos returnPos;
    returnPos.pos->x = pos->x;
    returnPos.pos->y = pos->y;
    returnPos.symbol = symbol;
    
    return returnPos;
}

char objPos::getSymbol() const
{
    return symbol;
}

bool objPos::isPosEqual(const objPos* refPos) const
{
    return refPos && refPos->pos->x == pos->x && refPos->pos->y == pos->y;
}


char objPos::getSymbolIfPosEqual(const objPos* refPos) const
{
    if(isPosEqual(refPos))
        return symbol;
    else
        return 0;
}
