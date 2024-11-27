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
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    // data 3 5 7 
    // index 0 1 2
    //size: 3

    //ex. insert 9 to head
    //shuffle from tail to head until i = 1
    if(listSize >= arrayCapacity) return;

    for(int i = listSize; i > 0; i--)
        aList[i] = aList[i - 1]; //shifts elements down

    aList[0] = thisPos.symbol;
    listSize++;

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
    if(listSize == 0) return;

    for(int i = 0; i < listSize - 1; i++)
        aList[i] = aList[i+1];
    
    listSize--;
}

void objPosArrayList::removeTail()
{
    //removing the last element
    //Lazy deletion
    // 2 5 7
    // 0 1 2
    //size: 2 (not 3 since we "deleted" last elem...for loop iterates up to listsize)
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
    //check if index out of bound
    if(index < 0 ) index = 0;
    else if(index >= listSize) index = listSize - 1;

    return aList[index];
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