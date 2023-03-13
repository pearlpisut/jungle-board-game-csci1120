#include "../headerFiles/player.h"
#include <iostream>
using namespace std;

Player::Player(string name, Color color) {
    this->name = name;
    this->color = color;
}

string Player::getName() const {
    return name;
}

Color Player::getColor() const {
    return color;
}

int Player::getPieceCount() const {
    // TODO: 
    // Return the size of the pieces vector
    return (int) pieces.size();
}

Piece* Player::getPiece(int i) const {
    // TODO: 
    // Get the piece indexed at i from the pieces vector
    return pieces.at(i);
}

void Player::addPiece(Piece* p) {
    // TODO: 
    // Add p to the pieces vector
    pieces.push_back(p);
}

void Player::delPiece(Piece* p) {
    // TODO: 
    // Remove p from the pieces vector
    int i;
    for (i = 0; i < pieces.size(); i++) {
        if (pieces[i] == p) 
            break;
    }
    pieces.erase(pieces.begin() + i);
}
