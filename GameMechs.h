#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

class GameMechs
{
    private:
        char input;
        bool exitFlag;
        bool loseFlag;
        int score;

        int boardSizeX;
        int boardSizeY;

        objPos food;

    public:
        GameMechs();
        GameMechs(int boardX, int boardY);
        ~GameMechs(); // is this one needed at all? Why or why not?
        
        bool getExitFlagStatus() const; 
        void setExitTrue();
        bool getLoseFlagStatus() const;
        void setLoseFlag();

        char getInput();

        void setInput(char this_input);
        void clearInput();

        int getBoardSizeX() const;
        int getBoardSizeY() const;
        
        objPos getFoodPos() const;

        int getScore() const;
        void incrementScore();
        void generateFood(objPosArrayList* blockOff); 

        
        // More methods should be added here
};

#endif