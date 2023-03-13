#include <iostream>
#include "../headerFiles/machine.h"
#include "../headerFiles/game.h"
#include "../headerFiles/board.h"

#include <ctime>
#include "../headerFiles/jumper.h"

using namespace std;

Machine::Machine(string name, Color color) : Player(name, color) {
    // TODO: randomize the seed of random number generator 
    //       using the current time
    srand((unsigned int)time(NULL));
}

// a sample machine that makes random valid moves
void Machine::makeMove(Board* board) {
    // TODO: make a random but valid move of a randomly picked piece on a board
    // Hint: there exist many ways to do so, one way is as follows:
    // - generate a random integer for picking a piece r from the player's pieces vector
    // - set y1, x1 to r->getY(), r->getX()
    // - generate random integers y2 and x2 in range of [0, H) and [0, W) respectively
    //   [or better in the y, x range of the 4 neighboring cells around (y1, x1), note to
    //    handle jumpable cells, 2 or 3 cells away, as well for Tiger and Lion]
    // - call board's move(y1, x1, y2, x2)
    // - once a valid move is returned, print the from and to cell addresses 
    //   and exit this function
    // Note: it can happen that no valid move can be found despite repeated picks.
    //       For example, only a Rat remains alive at a corner of the board while 
    //       the two cells it may go have been occupied by a Cat and a Dog.
    //       In this case, the player must surrender (set the opponent as winner).
    int kk = board->getGame()->getPlayer(this->getColor())->getPieceCount();
    int x3=-1, y3=-1;
    int j = 0;
    bool run = true;
    while (run) {   //count the number of piece we checked so that the loop stop when we found valid move || there is none valid move
        srand((unsigned int)time(NULL));
        int piece_chosen = rand() % kk;    //random index in player's list of piece to randomly pick one piece to move
        Piece* currentPiece = board->getGame()->getPlayer(this->getColor())->getPiece(piece_chosen);
        if (j == 2) {
            int hh = board->getGame()->getPlayer(this->getColor())->getPieceCount();
            for (int y = 0; y < hh; y++) {   //make sure we still have at least one valid move
                Piece* tempPiece = board->getGame()->getPlayer(this->getColor())->getPiece(y);
                int xx = tempPiece->getX();
                int yy = tempPiece->getY();
                bool any = false;
                Piece* dd= board->get(yy+1, xx);
                if(dd!=OUT_BOUND){
                    if (tempPiece->isMoveValid(board, yy + 1, xx)) {
                        any = true;
                        break;
                    }
                }
                dd = board->get(yy - 1, xx);
                if (dd != OUT_BOUND) {
                    if (tempPiece->isMoveValid(board, yy - 1, xx)) {
                        any = true;
                        break;
                    }
                }
                dd = board->get(yy, xx+1);
                if (dd != OUT_BOUND) {
                    if (tempPiece->isMoveValid(board, yy, xx+1)) {
                        any = true;
                        break;
                    }
                }
                dd = board->get(yy, xx-1);
                if (dd != OUT_BOUND) {
                    if (tempPiece->isMoveValid(board, yy, xx-1)) {
                        any = true;
                        break;
                    }
                }
                if (!any) { //if no any valid move, then surrender, set opponent's as the winner.
                    board->getGame()->setState(GAME_OVER);
                    board->getGame()->setTurn(Color(1 - (int)(board->getGame()->getTurn())));
                    run = false;
                    break;
                }
            }
        }
        int x0, y0;   //for storing the current position of the chosen piece
        int x2, y2;      //for storing destination address
        x0 = currentPiece->getX(); y0 = currentPiece->getY(); 
        int possible_move[4][2] = {{1, 0}, {-1, 0},{0, 1}, {0, -1}};
        srand((unsigned int)time(NULL));
        int ss = rand() % 4;
        x2 = x0 + possible_move[ss][0];
        y2 = y0 + possible_move[ss][1];
        if (x2 == x3 && y2 == y3)   //to avoid checking the piece that we just picked (for better run time)
            continue;
        if (board->isRiver(y2, x2)) {
            int step=0;
            if (x2 == x0 && y2 > y0) {   //jump down
                y2 += 3;
                step = 3;
            }
            else if (x2 == x0 && y2 < y0) {    //jump up
                y2 -= 3;
                step = 3;
            }
            else if (x2 > x0 && y2 == y0) {     //jump left to right
                x2 += 2;
                step = 2;
            }
            else if (x2 < x0 && y2 == y0) {     // jump right to left
                x2 -= 2;
                step = 2;
            }
            Jumper jumper;
            if (!(jumper.isJumpable(board, currentPiece, y2, x2, step)))
                continue;  //if cannot jump, we continue to another iteration to try new piece
        }
        bool valid = board->move(y0, x0, y2, x2);
        if (valid)
            break;
        x3 = x2; y3 = y2;
        j = 2;
    }
}
