#include "../headerFiles/lion.h"
#include <iostream>

using namespace std;

Lion::Lion(Color color, int y, int x) : Piece(color, y, x) {
    setName(PIECE_NAME[LION - 1]);
    setRank(LION);
}

bool Lion::isMoveValid(Board* board, int y, int x) {
    int currentX = this->getX(), currentY = this->getY();
    int step = abs(y - currentY) + abs(x - currentX);
    if (step!=1) {   //handle jumping over the river case
        if (!(Jumper::isJumpable(board, this, y, x, step - 1)))
            return false;
        else
            return true;
    }
    else if (step==1) {   //handle normal case (not jumping over the river)
        if (board->isRiver(y, x))  
            return false;
        else {
            Piece* q = board->get(y, x);
            if (q!=EMPTY && isOpponent(q) && !canCapture(q))  //square that has opponent's piece with higher rank
                return false;
            return true;
        }
    }
    else
        return false;
}