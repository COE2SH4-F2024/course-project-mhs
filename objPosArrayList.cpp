#include "objPosArrayList.h"

using namespace std;

// Paste your Tested implementation here.
// Paste your Tested implementation here.
// Paste your Tested implementation here.


objPosArrayList::objPosArrayList() // Default constructor
{
    aList = new objPos[ARRAY_MAX_CAP];
    listSize = 0;
    arrayCapacity = ARRAY_MAX_CAP;
}

objPosArrayList::~objPosArrayList() // Destructor
{
    delete[] aList;
}

int objPosArrayList::getSize()const
{
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

    //returnPos.setObjPos(aList[index]);
    returnPos.setObjPos(aList[index].pos->x, aList[index].pos->y, aList[index].symbol);

}

void objPosArrayList::insertHead(objPos thisPos)
{
    // check if array is at max capacity
    if(listSize == arrayCapacity)
    {
        return;
    }

    // create space for a new element to be inserted at index 0
    for(int i = listSize; i > 0; i--){
        aList[i].setObjPos(aList[i - 1]);  // shift towards the tail
    }
    aList[0].setObjPos(thisPos);
    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize == arrayCapacity)
    {
        return;
    }

    // insert element at the end of the list
    aList[listSize++].setObjPos(thisPos); 
}

void objPosArrayList::removeHead()
{
    // check if the array is empty
    if(listSize == 0)
    {
        return;
    }

    for(int i = 0; i < listSize - 1; i++)   
        aList[i].setObjPos(aList[i + 1]);  // shift towards  head

    listSize--;
}

void objPosArrayList::removeTail()
{
    // check if the array is empty
    if(listSize == 0)
    {
        return;
    }

    listSize--;  
}

