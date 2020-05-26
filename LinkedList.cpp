#include "LinkedList.h"


LinkedList::LinkedList(): 
    head(nullptr),
    listSize(0)
{}

LinkedList::~LinkedList() {
    clear();
    delete head;
}

void LinkedList::clear() {

    while (head != nullptr) {
      removeFront();
   }

   listSize = 0;
}

Tile* LinkedList::get(int i) {

    Node* current = head;
    Tile* toReturn = nullptr;
    int counter = 0;
    
    if (head != nullptr) {
        if (i >= 0 && i < listSize) {
            while (counter < i){
                current = current->getNext();
                ++counter;
            }

            toReturn = current->getTile();
        }
    }

    return toReturn;
}

Tile* LinkedList::getFront() {
    return head->getTile();
}

void LinkedList::addFront(Tile* tile) {

    Node* newNode = new Node(tile, nullptr);

    if (head == nullptr) {
        head = newNode;

    } else { 
        newNode->setNext(head);
        head = newNode;

    }

    ++listSize;
}

void LinkedList::addBack(Tile* tile) {

    Node* newNode = new Node(tile, nullptr);

    if(head == nullptr) {
        head = newNode;

    } else {
        Node* currentNode = head;

        while(currentNode->getNext() != nullptr) {
            currentNode = currentNode->getNext();
        }
        
        currentNode->setNext(newNode);
    }

    ++listSize;
}

void LinkedList::removeFront() {

    if (head != nullptr) {
        Node* toDelete = head;
        head = head->getNext();
        delete toDelete;
        --listSize;
    } else {
        throw std::logic_error("Deleting on empty list");
    }
}

void LinkedList::removeBack() {

    if (head != nullptr) {

        if (head->getNext() == nullptr) {
            removeFront();

        } else {
            Node* currentNode = head;
            Node* prevNode = nullptr;

            while(currentNode->getNext() != nullptr) {
                prevNode = currentNode;
                currentNode = currentNode->getNext();
            }

            prevNode->setNext(nullptr);
            delete currentNode;
            --listSize;
        }

    } else {
        throw std::logic_error("Deleting on empty list");
    }
}

int LinkedList::getListSize() {
    return listSize;
}
