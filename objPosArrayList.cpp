#include "objPosArrayList.h"
#include <iostream>
using namespace std;

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    listSize =0;
    //alliocated in heap
    arrayCapacity = ARRAY_MAX_CAP; //aka 200
    aList = new objPos[arrayCapacity];
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
    aList = nullptr;

}

objPosArrayList::objPosArrayList(const objPosArrayList &l)
{
    //deep copy 
    listSize = l.listSize;
    arrayCapacity = l.arrayCapacity;
    aList = new objPos[arrayCapacity];
    for(int i = 0; i < listSize; i++)
    {
        aList[i] = l.aList[i];
    }
       
}

//copy assignment operator
objPosArrayList &objPosArrayList::operator=(const objPosArrayList &l)
{
    if(this != &l)
    {
        delete[] aList; //aka starting all over
       
        listSize = l.listSize;
        arrayCapacity = l.arrayCapacity;
        aList = new objPos[arrayCapacity];

        //deep copy
        for(int i = 0; i < listSize; i++)
        {
            aList[i] = l.aList[i];
        }
    }
 
    return *this;
}

int objPosArrayList::getSize() const
{
    return listSize;
}


void objPosArrayList::insertHead(objPos thisPos)
{
    if(listSize >= arrayCapacity){
        return;
    }
   
    for(int i = listSize; i > 0; i--){
        aList[i] = aList[i - 1]; //shifts elements down
    }

    aList[0] = thisPos;
    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize == arrayCapacity)
    {
        return;
    }
    aList[listSize++] = thisPos;  
}

void objPosArrayList::removeHead()
{
    if(listSize == 0) return;
 
    for(int i = 0; i < listSize - 1; i++)
        aList[i] = aList[i+1];
   
    listSize--;
}

void objPosArrayList::removeTail()
{
    if(listSize > 0)
        listSize--;
}

objPos objPosArrayList::getHeadElement() const
{
    return aList[0];  
}

objPos objPosArrayList::getTailElement() const
{
    return aList[listSize - 1];  
}

objPos objPosArrayList::getElement(int index) const
{
    if(index < 0 || index >= listSize)
    {
        index = 0;
    }

    return aList[index];
}