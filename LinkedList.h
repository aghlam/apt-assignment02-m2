#ifndef COSC_ASS_TWO_LINKED_LIST
#define COSC_ASS_TWO_LINKED_LIST

#include <iostream>
#include <limits>

#include "Node.h"


class LinkedList {
public:

    LinkedList();
    ~LinkedList();
    
    /**
     * Clears the linked list by utilising removeFront() method
    */
    void clear();

    /**
     * @return tile stored at node i of linked list
    */
    Tile* get(int i);

    /**
     * @return tile at the head of the linked list
    */
    Tile* getFront();

    /**
     * @param tile added to the front of the linked list
    */
    void addFront(Tile* tile);

    /**
     * @param tile added to the back of the linked list
    */
    void addBack(Tile* tile);

    /**
     * Removes the first node in the linked list
    */
    void removeFront();

    /**
     * Removes the last node in the linked list
    */
    void removeBack();

    /**
     * @return int number of nodes in the list
    */
    int getListSize();
    


private:

    Node* head;
    int listSize;

};

#endif // COSC_ASS_TWO_LINKED_LIST