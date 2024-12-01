#include "objPosArrayList.h"
#include <iostream>

#define ARRAY_MAX_CAP 200 // Example capacity


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
    //cout << "Head position: (" << aList[0].pos->x << ", " << aList[0].pos->y << ")" << endl;
    
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
    cout << "Before inserting, listSize: " << listSize << endl;

    // Check if the array is at max capacity
    if (listSize == arrayCapacity)
    {
        cout << "Array is full. Cannot insert head" << endl;
        return;
    }

    // Shift elements towards the tail to make space for the new head
    for (int i = listSize; i > 0; i--)
    {
        cout << "Shifting element from index " << i-1 << " to index " << i << endl; // Debug print
        aList[i].setObjPos(aList[i - 1]);  // Shift the element towards the tail
    }

    // Insert the new head at the front of the list
    cout << "Inserting head at (" << thisPos.pos->x << ", " << thisPos.pos->y << ")" << endl;
    aList[0].setObjPos(thisPos);
    listSize++;

    cout << "After insertion, listSize: " << listSize << endl;
}




void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize == arrayCapacity)
    {
        cout<<"Array is full. Cannot insert tail" << endl ;
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

