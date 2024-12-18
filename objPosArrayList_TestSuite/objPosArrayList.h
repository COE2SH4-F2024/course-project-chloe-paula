#ifndef OBJPOS_ARRAYLIST_H
#define OBJPOS_ARRAYLIST_H

#define ARRAY_MAX_CAP 200

#include "objPos.h"
#include <iostream>


class objPosArrayList
{
    private:
        objPos* aList;
        int listSize;
        int arrayCapacity;

    public:
        objPosArrayList();
        ~objPosArrayList();
        //need copy constructor???
        objPosArrayList(const objPosArrayList &l);
        //copy assignment constructor
        objPosArrayList& operator=(const objPosArrayList &l);

        int getSize() const;
        void insertHead(objPos thisPos);
        void insertTail(objPos thisPos);
        void removeHead();
        void removeTail();
        
        //getter
        objPos getHeadElement() const;
        objPos getTailElement() const;
        objPos getElement(int index) const;

        //add for visual check
        void printList();
};

#endif