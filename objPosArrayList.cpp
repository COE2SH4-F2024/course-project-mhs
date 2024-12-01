#include "objPosArrayList.h"
#include <iostream>

using namespace std;

objPosArrayList::objPosArrayList()
    : aList(new objPos[ARRAY_MAX_CAP]), listSize(0), arrayCapacity(ARRAY_MAX_CAP) {}

objPosArrayList::~objPosArrayList() {
    delete[] aList; // Free allocated memory for the array
}

int objPosArrayList::getSize() const {
    return listSize;
}

void objPosArrayList::getHeadElement(objPos &returnPos) {
    if (listSize == 0) {
        cout << "Error: Attempted to access head of an empty list." << endl;
        return;
    }
    returnPos = aList[0]; // Deep copy of the head element
}

void objPosArrayList::getTailElement(objPos &returnPos) {
    if (listSize == 0) {
        cout << "Error: Attempted to access tail of an empty list." << endl;
        return;
    }
    returnPos = aList[listSize - 1]; // Deep copy of the tail element
}

void objPosArrayList::getElement(objPos &returnPos, int index) {
    if (index < 0 || index >= listSize) {
        cout << "Error: Index " << index << " out of bounds for getElement." << endl;
        return;
    }
    returnPos = aList[index];  // Deep copy of the indexed element
}

void objPosArrayList::insertHead(objPos thisPos) {
    if (listSize == arrayCapacity) {
        cout << "Error: Array is full. Cannot insert head." << endl;
        return;
    }

    // Shift elements to make room for the new head
    for (int i = listSize; i > 0; --i) {
        aList[i] = aList[i - 1]; // Deep copy to the next position
    }

    // Insert the new head
    aList[0] = thisPos; // Deep copy of thisPos
    listSize++;
    cout << "List size after insert: " << listSize << endl;  // Debugging

}

void objPosArrayList::insertTail(objPos thisPos) {
    if (listSize == arrayCapacity) {
        cout << "Error: Array is full. Cannot insert tail." << endl;
        return;
    }

    // Insert element at the end
    aList[listSize] = thisPos; // Deep copy of thisPos
    listSize++;
}

void objPosArrayList::removeHead() {
    if (listSize == 0) {
        cout << "Error: Attempted to remove head of an empty list." << endl;
        return;
    }

    // Shift elements to overwrite the first element
    for (int i = 0; i < listSize - 1; ++i) {
        aList[i] = aList[i + 1]; // Deep copy to the previous position
    }

    listSize--;
}

void objPosArrayList::removeTail() {
    if (listSize == 0) {
        cout << "Error: Attempted to remove tail of an empty list." << endl;
        return;
    }

    listSize--; // Simply decrement size
}
