#include "objPos.h"
#include <iostream>

objPos::objPos() {
    pos = new Pos();  // Always allocate memory
    pos->x = 0;
    pos->y = 0;
    symbol = ' ';
}

objPos::objPos(int xPos, int yPos, char sym) {
    pos = new Pos();
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
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

objPos::objPos(objPos&& other) noexcept : pos(other.pos), symbol(other.symbol) {
    other.pos = nullptr;  // Transfer ownership
}

objPos& objPos::operator=(objPos&& other) noexcept {
    if (this != &other) {
        delete pos;  // Free existing memory
        pos = other.pos;  // Take ownership
        symbol = other.symbol;
        other.pos = nullptr;
    }
    return *this;
}

objPos::~objPos() {
    if (pos) {
        delete pos;
        pos = nullptr;
    }
}

void objPos::setObjPos(const objPos& o) {
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

void objPos::setObjPos(int xPos, int yPos, char sym) {
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

char objPos::getSymbol() const {
    return symbol;
}

bool objPos::isPosEqual(const objPos* refPos) const {
    if (!refPos || !refPos->pos || !pos) {
        std::cerr << "Error: Null pointer in isPosEqual()" << std::endl;
        return false;
    }
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}

char objPos::getSymbolIfPosEqual(const objPos* refPos) const {
    return isPosEqual(refPos) ? symbol : 0;
}
