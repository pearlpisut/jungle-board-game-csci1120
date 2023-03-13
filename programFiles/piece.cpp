#include <iostream>
#include "../headerFiles/game.h"
#include "../headerFiles/piece.h"
#include "../headerFiles/board.h"

using namespace std;

Piece::Piece(Color color, int y, int x) : 
    color(color), y(y), x(x), trapped(false) {
}

void Piece::setName(string name) {
    this->name = name;
}

string Piece::getName() const {
    return name;
}

char Piece::getLabel() const {
    char c = getName().at(0);
    if (getName() == "Leopard")
        return color == BLUE ? 'p' : 'P';
    else
        return color == BLUE ? tolower(c) : c;
}

Color Piece::getColor() const {
    return color;
}

void Piece::setRank(int rank){
    this->rank = rank;
}

int Piece::getRank() const {
    return rank;
}

int Piece::getY() const {
    return y;
}

int Piece::getX() const {
    return x;
}

void Piece::setY(int y) {
    this->y = y;
}

void Piece::setX(int x) {
    this->x = x;
}

bool Piece::isTrapped() {
    return trapped;
}

void Piece::setTrapped(bool trapped) {
    this->trapped = trapped;
}

// Return true if p is an opponent piece of this piece, and false otherwise
bool Piece::isOpponent(Piece* p) {
    if (p != EMPTY && p->getColor() != getColor())
        return true;
    return false;
}

// Return true if this piece can capture piece p (assumed p is an opponent),
// and false otherwise
bool Piece::canCapture(Piece* p) {
    // TODO:
    // Check if this piece's rank is >= p's rank
    // Hint: remember to handle trapped situations
    // ...
    if ((this->getRank() >= p->getRank()) && !trapped) 
        return true;
    else
        return false;      //if the piece we want to move is currently trapped / has lower rank --> return false
}

// Carry out the capture of piece p
void Piece::capture(Board* board, Piece* p) {
    // TODO:
    // Remove the piece from board and opponent player's list of pieces
    // ...
    int t = (int)(getColor());
    Player* playerr = board->getGame()->getPlayer((Color)(!t));
    int x, y;
    x = p->getX();
    y = p->getY();
    cout << p->getName() << " of " << playerr->getName() << " captured!" << endl;
    playerr->delPiece(p);    //delete the piece from player's list
    board->put(y, x, EMPTY);  //replace that spot in the board with nullptr
}

// Carry out the move of this piece to (y, x)
void Piece::move(Board* board, int y, int x) {
    // TODO:
    // Hint: by calling suitable existing methods
    
    // capture opponent piece 
    // ...
    
    int current_x, current_y;
    current_x = getX();
    current_y = getY();
    Piece* temp = board->get(current_y, current_x);
    Piece* aimed_spot = board->get(y, x);
    int t = (int)(getColor());
    Player* player = board->getGame()->getPlayer((Color)(!t));
    if (aimed_spot!=EMPTY) {      //if the aimed position is not empty (have opponent's piece on there) --> we can carry out capturing.
        capture(board, aimed_spot);
    }
    // handle rank changes when entering and leaving traps
    // ...
    if (temp->isTrapped() == true && board->isTrap(y, x, (Color)(!t)) == false) {     //moving out of trap, need to restore rank
        string namee = temp->getName();
        int i = 0;
        while (i < 8) {
            if (PIECE_NAME[i] == namee)
                break;
            i++;
        }
        temp->setRank(i+1);
        temp->setTrapped(false);
    }

    else if (temp->isTrapped() == false && board->isTrap(y, x, (Color)(!t)) == true) {      //entering trap
        temp->setRank(0);
        temp->setTrapped(true);
    }
    // check winning conditions
    // (moved into opponent's den or captured all opponent pieces)
    // ...
    if (player->getPieceCount()==0) {      //check if opponent's list of pieces does not have any piece left
        board->getGame()->setState(State::GAME_OVER);
    }
    else if (board->isDen(y, x, (Color)(!t))) {
        board->getGame()->setState(State::GAME_OVER);
    }
    // carry out the move
    // ...
    board->put(y, x, temp);
    board->put(current_y, current_x, EMPTY);  //set the piece we moved from to empty, as nothing remains there
}

// Check if moving this piece to (y, x) is valid
// (Subclasses of Piece may override this method for defining special rules)
// [Note: you can modify this function if it doesn't fit your design]
bool Piece::isMoveValid(Board* board, int y, int x) {
    Piece* q = board->get(y, x);  // target cell
    if (q != EMPTY) {
        if (isOpponent(q) && !canCapture(q))  // cell occuppied by higher-rank opponent
            return false;
        if (board->isRiver(y, x) && tolower(getLabel()) != 't' && tolower(getLabel()) != 'l' && tolower(getLabel()) != 'r')  // target is a river cell, except for lion and tiger and rat
            return false;
        return true;
    }
    else
        return true;
}