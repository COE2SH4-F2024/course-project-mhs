#include "GameMechs.h"
#include "Player.h"

Player::Player(GameMechs* thisGMRef) {
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // Initialize playerPosList and insert the starting head position
    playerPosList = new objPosArrayList();

    objPos tempPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '*');
    playerPosList->insertHead(tempPos);
}

Player::~Player() 
{
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos() const 
{
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

    // board dimensions

    int Board_height = mainGameMechsRef->getBoardSizeY();
    int Board_width = mainGameMechsRef->getBoardSizeX();


    objPos currentHead = playerPosList->getHeadElement();
    
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



bool Player::checkSelfCollision() 
{
    if (playerPosList->getSize() <= 1) 
    {
        return false;
    }

    objPos head = playerPosList->getHeadElement();

    for (int i = 1; i < playerPosList->getSize(); ++i) 
    {
        objPos bodySegment = playerPosList->getElement(i);
        if (head.pos->x == bodySegment.pos->x && head.pos->y == bodySegment.pos->y) 
        {
            return true;
            break;
        }
    }
    return false;
}

bool Player::checkFoodConsumption() 
{
    
    
    objPos tempBody = playerPosList->getHeadElement();  // Update head with the first element

    objPos tempFood = mainGameMechsRef->getFoodPos();
   
    return tempBody.isPosEqual(&tempFood);

}


void Player::increasePlayerLength() 
{
    objPos currentHead = playerPosList->getHeadElement();

    // Calculate new head position based on direction
    int newX = currentHead.pos->x;
    int newY = currentHead.pos->y;

    switch (myDir) {
        case UP:    newY--; if (newY <= 0) newY = mainGameMechsRef->getBoardSizeY() - 2; break;
        case DOWN:  newY++; if (newY > mainGameMechsRef->getBoardSizeY() - 2) newY = 1; break;
        case LEFT:  newX--; if (newX <= 0) newX = mainGameMechsRef->getBoardSizeX() - 2; break;
        case RIGHT: newX++; if (newX > mainGameMechsRef->getBoardSizeX() - 2) newX = 1; break;
    }

    // Create new head position and add it
    objPos newHead(newX, newY, '*');
    playerPosList->insertHead(newHead); // No tail removal, snake grows

    // Increment score and generate new food
    mainGameMechsRef->incrementScore();
    mainGameMechsRef->generateFood(playerPosList);
}


