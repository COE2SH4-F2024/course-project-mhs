#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "objPosArrayList.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs* myGM;
Player* myPlayer;

//bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while((myGM->getExitFlagStatus()) == false)  // Run program until exit conditions met
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    //exitFlag = false;

    myGM = new GameMechs(26, 13); // Makes a board that's 26x13
    myPlayer = new Player(myGM);
    myGM->generateFood(myPlayer->getPlayerPos());

}

void GetInput(void)
{
    myGM->getInput();
    cout << "Input received: " << myGM->getInput() << endl; // Add this for debugging


}

void RunLogic(void)
{
    
    // init local variabels 
    objPos tempFood;
    objPos tempBody;
    objPos newInsert;

    objPosArrayList* playerBody = myPlayer->getPlayerPos();
   
    myGM->getFoodPos(tempFood);

    myPlayer->getPlayerPos()->getHeadElement(tempBody);  // Get the head element by reference


    // player movement controls
    myPlayer->updatePlayerDir();  
    myPlayer->movePlayer(); 

    // food mechanism:

    // compare head pos with food pos
    // if equalm, increment score + generate new food + grow snake

   // playerBody->getHeadElement(tempBody);

    if(tempBody.isPosEqual(&tempFood))
    {
        myGM->incrementScore();
        newInsert.setObjPos(tempBody.pos->x, tempBody.pos->y, '*');
        myPlayer->getPlayerPos()->insertHead(newInsert);
        myGM->generateFood(myPlayer->getPlayerPos());  // Generate new food
    }

    // self collision

     if(myPlayer->checkSelfCollision())
    {
        myGM->setLoseFlag();
    }
    myGM->clearInput();

}

void DrawScreen(void)
{
    MacUILib_clearScreen(); 

    // initializing local variables
    bool drawn;
    objPos tempBody;
    objPos tempFood;

    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    myGM->getFoodPos(tempFood);

    MacUILib_printf("--------Snake--------\n"); // game header message

    /* Gameboard drawing routine:
    A nested for-loop iterates through rows and columns, checking the game element it's supposed to draw.
    It does this by getting the indexes of each object present on the board and displaying its associates symbol.
    */
    for(int i = 0; i < myGM->getBoardSizeY(); i++)
    {
        for(int j = 0; j < myGM->getBoardSizeX(); j++)
        {
            drawn = false;
            
            /* Drawing the player:
                - Iterates through the array list of player objects
                - Displays the symbol associates with each object instance each time it occurs
                - Once it's drawn, sets the boolean "drawn" to true, breaking the loop to prevent overlaps
            */
            for(int k = 0; k < playerBody->getSize(); k++)
            {
                playerBody->getElement(tempBody, k);
                if(j == tempBody.pos->x && i == tempBody.pos->y)
                {
                    MacUILib_printf("%c", tempBody.symbol);
                    drawn = true;
                    break;
                }
            }
            if(drawn) continue;

            // Drawing the board border
            if(i == 0 || i == myGM->getBoardSizeY() - 1 || j == 0 || j == myGM->getBoardSizeX() - 1)
            {
                MacUILib_printf("%c", '#');
            }

            // Drawing the food object
            else if(j == tempFood.pos->x && i == tempFood.pos->y)
            {
                MacUILib_printf("%c", tempFood.symbol);
            }

            // Filling in the rest of the board with whitespaces
            else
            {
                MacUILib_printf("%c", ' ');
            }
        }
        MacUILib_printf("\n");
    }

    // Welcome message and score display
    MacUILib_printf("Press WASD to start contorl the snake.\nPress SPACE to exit! \n SCORE: %d\n", myGM->getScore()); 

    // Forced-quit message
    if(myGM->getExitFlagStatus())
    {
        MacUILib_printf("\nGAME QUIT."); 
    }

    // Game loss message         
    if(myGM->getLoseFlagStatus())
    {
        MacUILib_printf("\n BETTER LUCK NEXT TIME!!"); 
        myGM->setExitTrue();
    }
}
void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    

    MacUILib_uninit();
    //prevent memory leak
    delete myGM; 
    delete myPlayer;
}
