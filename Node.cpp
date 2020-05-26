#include "Node.h"


Node::Node(Tile* tile, Node* next):
    tile(tile),
    next(next)
{}

Node::Node(Node& other):
    tile(other.tile),
    next(other.next)
{}

Node::~Node() {
    delete tile;
}

Node* Node::getNext() {
    return next;
}

void Node::setNext(Node* node) {
    next = node;
}

Tile* Node::getTile() {
    return tile;
}
