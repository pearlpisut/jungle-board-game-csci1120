#include "../headerFiles/elephant.h"
#include <iostream>

using namespace std;

Elephant::Elephant(Color color, int y, int x) : Piece(color, y, x) {
    setName(PIECE_NAME[ELEPHANT - 1]);
    setRank(ELEPHANT);
}

bool Elephant::isMoveValid(Board* board, int y, int x) {
    if (abs(getY() - y) + abs(getX() - x) != 1)  // move other than 1 square
        return false;
    if (board->get(y, x) != EMPTY) {
        if (board->get(y, x)->getRank()!=0 && tolower(board->get(y, x)->getLabel()) == 'r' )  //cant move to the spot occupied by an untrapped rat
            return false;
        else
            return true;
    }
    else
        return true;
}
