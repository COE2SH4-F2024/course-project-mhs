#include "Player.h"


Player::Player(GameMechs* thisGMRef) // constructor
{
   //intitialzing data members 
    mainGameMechsRef = thisGMRef;
    myDir = STOP;



    // more actions to be included

    playerPosList = new objPosArrayList();

    // initializing the head of the player as the first element of the array
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '*'); 
    playerPosList->insertHead(tempPos);

}


Player::~Player() // deconsturctor 
{
    // delete any heap members here
    delete playerPosList;

}

objPosArrayList* Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    //return playerPosList->getHeadElement();

    objPos head;
    playerPosList->getHeadElement(head);  // pass head by reference to get the head element
    return playerPosList;  // return the head object
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

    switch (myDir) {
        case UP:
            newY--;
            if (newY < 1) newY = mainGameMechsRef->getBoardSizeY() - 2; // Wrap around
            break;
        case DOWN:
            newY++;
            if (newY >= mainGameMechsRef->getBoardSizeY() - 1) newY = 1; // Wrap around
            break;
        case LEFT:
            newX--;
            if (newX < 1) newX = mainGameMechsRef->getBoardSizeX() - 2; // Wrap around
            break;
        case RIGHT:
            newX++;
            if (newX >= mainGameMechsRef->getBoardSizeX() - 1) newX = 1; // Wrap around
            break;
        default:
            return; // No movement if direction is STOP
    }

    // Create a new head position
    objPos newHead(newX, newY, '*');

    // Add new head to the list and remove the tail
    playerPosList->insertHead(newHead);
    playerPosList->removeTail(); // Maintains snake length
}

bool Player::checkSelfCollision() {
   // objPos head = playerPosList->getHeadElement();

  objPos head;
    playerPosList->getHeadElement(head);  // Get the head element by reference

    // iterate through the body, no head!!
  for (int i = 1; i < playerPosList->getSize(); i++) 
  {
        objPos bodySegment;
        playerPosList->getElement(bodySegment, i);  // get the body segment by reference

        if (head.isPosEqual(&bodySegment)) 
        {
            return true;  // collision detected
        }
    }
    return false;  // else no collision
}



bool Player::checkFoodConsumption() 
{
    //objPos head = *playerPosList->getHeadElement();
    //objPos food = *mainGameMechsRef->getFoodPos(); //  current food position
    
    objPos head;  // local variable to store the player's head position
    playerPosList->getHeadElement(head);  // Update head with the first element

    objPos food;  // local variable to store the food position
    mainGameMechsRef->getFoodPos(food);  // Update food with the current food position
    
    return head.isPosEqual(&food);
}

void Player::increasePlayerLength() 
{
    mainGameMechsRef->incrementScore(); // update score
    mainGameMechsRef->generateFood(playerPosList); // generate new food
}

// More methods to be added