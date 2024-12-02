#include "GameMechs.h"
#include "MacUILib.h"
#include <iostream>
#include "time.h"
#include <cstdlib>

using namespace std;

GameMechs::GameMechs()
{
    boardSizeX = 30; 
    boardSizeY = 15; 
    input = 0; 
    exitFlag = false;
    loseFlag = false; 
    score = 0;
    food.setObjPos(10,10,'0');
}

GameMechs::GameMechs(int boardX, int boardY)
{
    boardSizeX = boardX; 
    boardSizeY = boardY; 
    input = 0; 
    exitFlag = false;
    loseFlag = false; 
    score = 0;
    food.setObjPos(10,10,'0');
}


GameMechs::~GameMechs() 
{
  
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}

char GameMechs::getInput() 
{
    if (MacUILib_hasChar()) 
    {
        input = MacUILib_getChar();
    }
    return input;
}

int GameMechs::getScore() const 
{
    return score;
}

void GameMechs::incrementScore() 
{
    score++;
}

int GameMechs::getBoardSizeX() const 
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const 
{
    return boardSizeY;
}

void GameMechs::setExitTrue() 
{
    exitFlag = true;
}

void GameMechs::setLoseFlag() 
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input) 
{
    input = this_input;
}

void GameMechs::clearInput() {
    input = 0;
}

void GameMechs::generateFood(objPosArrayList* blockOff) // Food generation
{
    srand(time(NULL));  // Seed the random number generator

    bool validFoodPosition = false;
    objPos tempPos;  // temporary variable for body segment comparison

    // loop until a valid position is found
    while (!validFoodPosition) {
        // randomly generate x and y coordinates (avoid boundaries)
        food.pos->x = (rand() % (boardSizeX - 2)) + 1;  // Assign to foodPos.x
        food.pos->y = (rand() % (boardSizeY - 2)) + 1;  // Assign to foodPos.y

        // check if the food position overlaps with any snake body part
        validFoodPosition = true; // Assume valid until proven otherwise
        for (int i = 0; i < blockOff->getSize(); i++) {
            tempPos = blockOff->getElement(i);  // Get the i-th body segment
            // if the food position matches any body segment, it's invalid
            if (food.pos->x == tempPos.pos->x && food.pos->y == tempPos.pos->y) 
            {
                validFoodPosition = false;
                break;  // Exit the loop and regenerate food
            }
        }
    }
    // once a valid position is found, set the food position
    food.setObjPos(food.pos->x, food.pos->y, 'O');  

}


objPos GameMechs::getFoodPos() const
{
    return food;
}
