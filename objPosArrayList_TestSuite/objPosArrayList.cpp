#include "objPosArrayList.h"
#include <iostream>

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    listSize = 0;
    arrayCapacity = ARRAY_MAX_CAP; //200
    aList = new int[ARRAY_MAX_CAP]; //create 200-int array on heap
}
//destructor:
objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

//copy constructor:??? i added this based on what i think is missing
// objPosArrayList::objPosArrayList(const objPosArrayList &l)
// {
//     //deep copy!
//     listSize = l.listSize;
//     arrayCapacity = l.arrayCapacity;
//      aList = new int[DEFAULT_SIZE];
//     for(int i = 0; i < sizeList; i++)
//         aList[i] = l.aList[i];
// }
int objPosArrayList::getSize() const
{

}

void objPosArrayList::insertHead(objPos thisPos)
{
    
}
//easier of the two
void objPosArrayList::insertTail(objPos thisPos)
{
    //shorter version: if(listSize == arrayCapacity) return; //"sanity check"
    if(listSize == arrayCapacity){
        cout << " array full" << endl;
        return;
    }
    aList[listSize++] = thisPos;
}

void objPosArrayList::removeHead()
{
    
}

void objPosArrayList::removeTail()
{
    
}

objPos objPosArrayList::getHeadElement() const
{
    
}

objPos objPosArrayList::getTailElement() const
{
    
}

objPos objPosArrayList::getElement(int index) const
{
    
}

void objPosArrayList::printList() 
{
   if(listSize == 0) 
   {
    cout << "list empty!" << endl;
    return;
   }

    for(int i = 0; i < listSize; i++)
        cout << aList[i] <<" ";
        
    cout << endl;
}