#include "../headerFiles/rat.h"
#include <iostream>

using namespace std;

Rat::Rat(Color color, int y, int x) : Piece(color, y, x) {
    setName(PIECE_NAME[RAT-1]);
    setRank(RAT);
}

bool Rat::isMoveValid(Board* board, int y, int x) {
    // TODO: Override the superclass version of valid move checks
    // e.g., to allow a Rat to move into a square occuppied by an Elephant 
    //       to allow a Rat to enter a water square
    int x0, y0;      //store current position
    x0 = this->getX();
    y0 = this->getY();
    Piece* q = board->get(y, x);
    if (q != EMPTY) {
        if ((q->getRank() == 8 || q->getRank() <= 1))   //can move to square that has opponent's elephant or rat or trapped piece
            return Piece::isMoveValid(board, y, x);
        else
            return false;
    }
    else {
        if (abs(getY() - y) + abs(getX() - x) != 1)  // move other than 1 square
            return false;
        return true;
    }
}

bool Rat::canCapture(Piece* p) {
    // TODO: Override the superclass version of capture checks
    // A Rat can capture an Elephant
    int x0, y0;     //store position of this piece
    x0 = this->getX();
    y0 = this->getY();
    int x1, y1;     //store position of target piece
    x1 = p->getX();
    y1 = p->getY();
    //check if the pieces are in the river.
    bool river_check = ((x0 == 1 || x0 == 2) || (x0 == 4 || x0 == 5)) && (y0 == 3 || y0 == 4 || y0 == 5);
    bool opponent_river_check = ((x1 == 1 || x1 == 2) || (x1 == 4 || x1 == 5)) && (y1 == 3 || y1 == 4 || y1 == 5);
    if (!(this->isTrapped())) {  
        if ((p->getRank() <= 1 || p->getRank() == 8) && (river_check == opponent_river_check))  //to capture, this rat piece and target piece must be both on land or both on river
            return true;                                                                     // the valid targets are opponent's trapped piece, rat, and elephant.
        else
            return false;
    }
    else
        return false;
}