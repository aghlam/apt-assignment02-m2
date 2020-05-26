#ifndef COSC_ASS_TWO_NODE
#define COSC_ASS_TWO_NODE

#include "Tile.h"


class Node {
public:

    Node(Tile* tile, Node* next);
    Node(Node& other);
    ~Node();

    /**
     * @return tile pointer stored at this node
    */
    Tile* getTile();

    /**
     * @return node pointer stored as next
    */
    Node* getNext();

    /**
     * @param node to be set as the following node
    */
    void setNext(Node* node);

private:
    
    Tile* tile;
    Node* next;

};

#endif // COSC_ASS_TWO_NODE