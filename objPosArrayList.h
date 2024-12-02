#ifndef OBJPOS_ARRAYLIST_H
#define OBJPOS_ARRAYLIST_H

#include "objPos.h"
#include <iostream>

#define ARRAY_MAX_CAP 200   // Max capacity of array list

/*

This class a dynamic array-based list to manage a collection of 'objPos' objects
    objPos objects: 
        x,y-coordinate
        symbol

The class allows list operations:
    - Inserting elements at the head or tail of the list.
    - Removing elements from the head or tail.
    - Accessing head, tail and elements by index
    - Checking the current size of the list
    - Printing elements for debugging

*/
class objPosArrayList
{
    private:
        objPos* aList;          //  Array to hold the elements (objPos objects)
        int listSize;           // Number of elements currently in the list
        int arrayCapacity;      // Maximum capacity of the list (fixed size)

    public:

        // Constructor and Destructor
        objPosArrayList();      //  Initializes the list
        ~objPosArrayList();     // Frees dynamically allocated memory

        // Copy constructor and assignment operator for deep copying
        objPosArrayList(const objPosArrayList &l);
        objPosArrayList& operator=(const objPosArrayList &l);

        // Getter functions
        int getSize() const;                // Returns number of elements in the list    
        objPos getHeadElement() const;      // Returns Head element (first item)
        objPos getTailElement() const;      // Returns Tail element (last item)
        objPos getElement(int index) const; // Returns element at a specific index

        // Setter and Deletion functions
        void insertHead(objPos thisPos);    // Sets Head element (first item)
        void insertTail(objPos thisPos);    // Sets Tail element (last item)
        void removeHead();                  // Removes Head element
        void removeTail();                  // Removes Tail element
        void removeElement(int index);      //  Removes element at an index

        
        //  For visual debugging
        void printList();   //prints the list for debugging purposes
};

#endif