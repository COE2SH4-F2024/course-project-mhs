#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "objPosArrayList.h"

Player::Player(GameMechs* thisGMRef) {
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // Initialize playerPosList and insert the starting head position
    playerPosList = new objPosArrayList();
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '*');
    playerPosList->insertHead(tempPos);
}

Player::~Player() {
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos() const {
    return playerPosList; // Return reference to playerPosList
}
void Player::updatePlayerDir()
{
    // PPA3 input processing logic  

    char input = mainGameMechsRef->getInput();
    
    if (input != 0) {
        switch (input) {

            case ' ':
                mainGameMechsRef->setExitTrue();
                break;

            case 'W': case 'w':
                if (myDir != DOWN) {
                    myDir = UP;

                }
                break;

            case 'S': case 's':
                if (myDir != UP) {
                    myDir = DOWN;
                }
                break;

            case 'A': case 'a':
                if (myDir != RIGHT) {
                    myDir = LEFT;
                }
                break;

            case 'D': case 'd':
                if (myDir != LEFT) {
                    myDir = RIGHT;
                }
                break;
                
            default:
            break;
        }
    }
}

void Player::movePlayer() {
    // Get the current head position
   // objPos currentHead = playerPosList->getHeadElement();

    objPos currentHead;
    playerPosList->getHeadElement(currentHead);

    // Calculate new head position based on direction
    int newX = currentHead.pos->x;
    int newY = currentHead.pos->y;

   switch (myDir)
    {
        case UP:
            newY--;
            if(newY <= 0){
                newY = mainGameMechsRef->getBoardSizeY() - 2;
            }
            break;
        case RIGHT:
            newX++;
            if(newX > mainGameMechsRef->getBoardSizeX() - 2){
                newX = 1;
            }
            break;

        case LEFT:
            newX--;
            if(newX <= 0){
                newX = mainGameMechsRef->getBoardSizeX() - 2;
            }
            break;

        case DOWN:
            newY++;
            if(newY > mainGameMechsRef->getBoardSizeY() - 2){
                newY = 1;
            }
            break;

        default:
            break;
    }

    // Create a new head position
    objPos newHead(newX, newY, '*');

    // Add new head to the list and remove the tail
    playerPosList->insertHead(newHead);
    playerPosList->removeTail(); // Maintains snake length

}



bool Player::checkSelfCollision() {
    if (playerPosList->getSize() <= 1) {
        return false;
    }

    objPos head;
    playerPosList->getHeadElement(head);

    for (int i = 1; i < playerPosList->getSize(); ++i) {
        objPos bodySegment;
        playerPosList->getElement(bodySegment, i);
        if (head.isPosEqual(&bodySegment)) {
            return true;
        }
    }
    return false;
}

bool Player::checkFoodConsumption() 
{
    
    
    objPos tempBody;
    playerPosList->getHeadElement(tempBody);  // Update head with the first element


    objPos tempFood;
    mainGameMechsRef->getFoodPos(tempFood);


    return tempBody.isPosEqual(&tempFood);


   
}


void Player::increasePlayerLength() {
    
   
    if (playerPosList->getSize() == 0) 
    {
        return;
    }
    objPos tempFood;
    objPos tempBody;
    objPos newInsert;

    mainGameMechsRef->incrementScore();
    newInsert.setObjPos(tempBody.pos->x, tempBody.pos->y, '*');
    playerPosList->insertHead(newInsert);
    mainGameMechsRef->generateFood(playerPosList);
}



