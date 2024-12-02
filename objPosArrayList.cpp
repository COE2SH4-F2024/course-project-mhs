#include "objPosArrayList.h"
#include <iostream>

using namespace std;

objPosArrayList::objPosArrayList() // Default constructor
{
    aList = new objPos[ARRAY_MAX_CAP];
    listSize = 0;
    sizeArray = ARRAY_MAX_CAP;
}

objPosArrayList::~objPosArrayList() // Destructor
{
    delete[] aList;
}

int objPosArrayList::getSize() const {
    return listSize;
}
void objPosArrayList::getHeadElement(objPos &returnPos)
{
    if(listSize == 0)
    {
        return;
    }
    
    returnPos.setObjPos(aList[0]);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    if(listSize == 0)
    {
        return;
    }
    returnPos.setObjPos(aList[listSize-1]);
    
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    if(listSize == 0 || index < 0 || index >= listSize)
    {
        return;
    }

    returnPos.setObjPos(aList[index]);
}

void objPosArrayList::insertHead(objPos thisPos)
{
    // Checking if the array is at max capacity
    if(listSize == sizeArray)
    {
        return;
    }

    // Creating space for a new element to be inserted at index 0
    for(int i = listSize; i > 0; i--){
        aList[i].setObjPos(aList[i - 1]);  // Shifting towards the tail
    }
    aList[0].setObjPos(thisPos);
    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    // Checking if the array is at max capacity
    if(listSize == sizeArray)
    {
        return;
    }

    // Inserting an element at the end of the list
    aList[listSize++].setObjPos(thisPos); 
}

void objPosArrayList::removeHead()
{
    // Checking if the array is empty
    if(listSize == 0)
    {
        return;
    }

    for(int i = 0; i < listSize - 1; i++)   
        aList[i].setObjPos(aList[i + 1]);  // Shifting towards the head

    listSize--;
}

void objPosArrayList::removeTail()
{
    // Checking if the array is empty
    if(listSize == 0)
    {
        return;
    }

    listSize--;  
}
