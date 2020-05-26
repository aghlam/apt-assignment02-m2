#include "Player.h"


Player::Player(string name):
    name(name),
    score(0),
    turn(true)
{
    floor = new Floor();
    mosaic = new Mosaic();
}

Player::Player(string name, int score, bool turn, string savedFloor, string savedMosaic[]) {
    
    this->name = name;
    this->score = score;
    this->turn = turn;
    floor = new Floor(savedFloor);
    mosaic = new Mosaic(savedMosaic);

}

Player::~Player() {

    delete mosaic;
    delete floor;

}

string Player::getName(){
    return name;
}

void Player::setScore(int score) {
    this->score = score;
}

int Player::getScore(){
    return score;
}

void Player::addScore(int score) {
    this->score += score;
}

void Player::minusScore(int score) {
    this->score -= score;
}

void Player::setTurn(bool turn) {
    this->turn = turn;
}

bool Player::getTurn() {
    return turn;
}

Floor* Player::getFloor() {
    return floor;
}

Mosaic* Player::getMosaic() {
    return mosaic;
}
