#include "../headerFiles/jumper.h"
#include <algorithm>

using namespace std;

Jumper::Jumper() {
}

/* Check if animal p can jump over a river
   The 'steps' argument is used to control how many river cells to test.
   Call isJumpable(board, p, y, x, 2) to test if p can do a horizontal river jump (2 steps)
   Call isJumpable(board, p, y, x, 3) to test if p can do a vertical river jump (3 steps)
   Return true if p can jump and false otherwise (e.g. due to blocking by a Rat in river)
 */
bool Jumper::isJumpable(Board* board, Piece* p, int y, int x, int steps) {
    /* TODO: Add code to check if p can jump over 'steps' river squares 
             to the destination(y, x) */
    int current_x, current_y;
    current_x = p->getX();
    current_y = p->getY();
    char label = tolower(p->getLabel());
    if ( !(label == 't' || label == 'l') )    //verify if the piece is either Tiger or Lion
        return false;
    if (steps == 3) {    //vertical jump test
        if (y > current_y) {  //jump down
            for (int i = 1; i <= 3; i++) {
                if (!(board->isEmpty(current_y + i, x)))    //make sure no rat is blocking the way
                    return false;
            }
        }
        else if (y < current_y) {   //jump up
            for (int i = 1; i <= 3; i++) {
                if (!(board->isEmpty(current_y - i, x))) //make sure no rat is blocking the way
                    return false;
            }
        }
    }
    else if (steps == 2) {   //horizontal jump test
        if (x > current_x) {     //jump from left to right
            for (int i = 1; i <= 2; i++) {
                if (!(board->isEmpty(y, current_x + i)))  //make sure no rat is blocking the way
                    return false;
            }
        }
        else if (x < current_x) {      //jump from right to left
            for (int i = 1; i <= 2; i++) {
                if (!(board->isEmpty(y, current_x - i)))  //make sure no rat is blocking the way
                    return false;
            }
        }
    }
    else
        return false;
    bool vv;
    Piece* q = board->get(y, x);   //validating if the jumping piece can land on the selected square
    if (q!=EMPTY && p->isOpponent(q) && !(p->canCapture(q)))
        vv = false;
    else 
        vv = true;
    return vv;
}