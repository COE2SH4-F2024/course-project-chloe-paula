#include "objPosArrayList.h"
#include <iostream>
using namespace std;
// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    //number of valid list elements in the list
    listSize = 0;
    //number of array elements allocated in heap array
    arrayCapacity = ARRAY_MAX_CAP; //200
    //Allocate objPos array - 200-element on heap
    aList = new objPos[arrayCapacity];
   

     for(int i=0; i<ARRAY_MAX_CAP;i++){
         (aList+i)->symbol = '0';
     }


}


//copy constructor: added this based on what we think is missing
objPosArrayList::objPosArrayList(const objPosArrayList &l)
{
    //deep copy!
    listSize = l.listSize;
    arrayCapacity = l.arrayCapacity;
    aList = new objPos[arrayCapacity];
    for(int i = 0; i < listSize; i++){
        aList[i] = l.aList[i];
    }
        
}

//destructor:
objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

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
    char newSym = thisPos.getSymbol();
    if(listSize >= arrayCapacity){
        return;
    } 
    
    for(int i = listSize; i > 0; i--){
        aList[i] = aList[i - 1]; //shifts elements down
    }
    aList[0].symbol = newSym;
    listSize++;
    std::cout << " size: " << listSize << std::endl;
     std::cout << " sym: " << aList[0].symbol << std::endl;

    
   // return;

}
//easier of the two
void objPosArrayList::insertTail(objPos thisPos)
{
    //shorter version: if(listSize == arrayCapacity) return; //"sanity check"
    if(listSize == arrayCapacity){
        std::cout << " array full" << std::endl;
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
    if(index < 0 ){
        index = 0;
    } 
    else if(index >= listSize){
        index = listSize - 1;
    } 

    return aList[index];
}

void objPosArrayList::printList() 
{
   if(listSize == 0) 
   {
    std::cout << "list empty!" << std::endl;
    return;
   }

    for(int i = 0; i < listSize; i++)
        cout<< aList[i].symbol << " ";
        
    std::cout << std::endl;
}