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
    cout << "Input received: " << myGM->getInput() << endl; // Added  for debugging


}

void RunLogic(void) {

    // Get the player's body and head position

    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    
    objPos tempBody = playerBody->getHeadElement();


    // Player movement controls
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();

    // Food mechanism: Check for consumption and grow if necessary
   if (myPlayer->checkFoodConsumption()) 
   {
    myPlayer->increasePlayerLength();
    }

    // Self-collision detection
    if (myPlayer->checkSelfCollision()) {
        myGM->setLoseFlag();
    }

    // Clear input for the next cycle
    myGM->clearInput();
}


void DrawScreen(void)
{
    MacUILib_clearScreen(); 

    // initializing local variables
    bool drawn;


    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    
    objPos tempFood = myGM->getFoodPos();

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
            
            for(int k = 0; k < playerBody->getSize(); k++)
            {

                objPos tempBody = playerBody->getElement(k);

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
