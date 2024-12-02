#include "objPosArrayList.h"
#include "MacUILib.h"
using namespace std;

//  Constructor:
//  Initializes array list
objPosArrayList::objPosArrayList()
{
    listSize = 0;                       //  Empty list at start
    arrayCapacity = ARRAY_MAX_CAP;
    aList = new objPos[arrayCapacity];  //  Dynamically allocate memory for the list
}


//  Destructor:
//  Frees dynamically allocated memory for the list
objPosArrayList::~objPosArrayList()
{
    delete[] aList;
    aList = nullptr;    //  Prevents dangling pointer
}


//  Copy Constructor: 
//  Deep copy of another objPosArrayList
objPosArrayList::objPosArrayList(const objPosArrayList &l)
{
    listSize = l.listSize;
    arrayCapacity = l.arrayCapacity;
    aList = new objPos[arrayCapacity];  // Allocate new memory for l-list
    for(int i = 0; i < listSize; i++)
        aList[i] = l.aList[i];          // deep copy each objPos element        
}


//  Copy Assignment Operator:
//  Assigns a new list to an existing list (deep copy)
objPosArrayList &objPosArrayList::operator=(const objPosArrayList &l)
{
    if(this != &l)                          // Checks for self-assignment
    {
        delete[] aList;                     //   Ensures to free up exisitng array memory before deep copy
        
        listSize = l.listSize;
        arrayCapacity = l.arrayCapacity;
        aList = new objPos[arrayCapacity];  //  Allocate new memory for the list

        for(int i = 0; i < listSize; i++)
            aList[i] = l.aList[i];          //  Deep copy each objPos element
    }

    return *this;
}


//  Return the size (num of elements) of list
int objPosArrayList::getSize() const
{
    return listSize;
}


//  Return the first element of the list (head)
objPos objPosArrayList::getHeadElement() const
{
    return aList[0];   
}


//  Return the last element of the list (tail)
objPos objPosArrayList::getTailElement() const
{
    return aList[listSize - 1];
}


//  Return the element at the specific index
objPos objPosArrayList::getElement(int index) const
{
    //  Check if index out of bound, true: returns the first element
    if(index < 0 || index >= listSize)
        index = 0;          // default to 0 if index invalid

    return aList[index];
}


//  Insert an element at the head (first element)
void objPosArrayList::insertHead(objPos thisPos)
{
    //  Checks if the list is full, cannot add element if full
    if(listSize >= arrayCapacity)
        return;
    
    //  Shift all elements one position to the right
    for(int i = listSize; i > 0; i--)
        aList[i] = aList[i - 1]; 
    
    aList[0] = thisPos;     //  Insert the new element at the head
    listSize++;             //  Increment list size by one

}


//  Insert an element at the tail (last element)
void objPosArrayList::insertTail(objPos thisPos)
{
    //  Checks if the list is full, cannot add element if full
    if(listSize >= arrayCapacity)
        return;

    //  Inser the element at the tail and increment size by one
    aList[listSize++] = thisPos;  
}


// Removes the head (first) element of the list
void objPosArrayList::removeHead()
{
    //  Checks if list is empty, cannot remove if empty
    if(listSize == 0) return;

    // Shift all elements to the left by one
    for(int i = 0; i < listSize - 1; i++)
        aList[i] = aList[i+1];
    
    //  Decrease the list size by one
    listSize--;
}


// Removes the tail (last) element of the list
void objPosArrayList::removeTail()
{
    if(listSize > 0)
        listSize--;     //  Decrease the list size, removes the tail
}


//  Removes an item in a list at the index
void objPosArrayList::removeElement(int index)
{
    //  Check if valid index
    if(index < 0 || index >= listSize)  return;

    //  Shift all elements to the left one position, after the index 
    for(int i = index; i < listSize - 1; i++)
        aList[i] = aList[i+1];

    listSize--;
}


// Prints the list for debugging purposes
void objPosArrayList::printList() 
{
    // Check if list is empty
    if(listSize == 0) 
    {
        MacUILib_printf("List is empty, nothing to print!");
        return;
    }

    //  Print each element in the list
    for(int i = 0; i < listSize; i++)
        MacUILib_printf("%c", aList[i].symbol);
        MacUILib_printf("\n");
}