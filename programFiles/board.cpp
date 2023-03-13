#include <iostream>
#include <cctype>
#include "../headerFiles/game.h"
#include "../headerFiles/board.h"
#include "../headerFiles/piece.h"
#include "../headerFiles/elephant.h"
#include "../headerFiles/lion.h"
#include "../headerFiles/leopard.h"
#include "../headerFiles/wolf.h"
#include "../headerFiles/rat.h"
#include "../headerFiles/tiger.h"
#include "../headerFiles/dog.h"
#include "../headerFiles/cat.h"
#include "../headerFiles/player.h"

// TODO: include more necessary headers
#include "fileman.h"

using namespace std;

Board::Board(Game* game, char* filename) : 
    game(game), cells() {  // initalize cells' elements to nullptr
    // Set up the initial game board
    if (filename != nullptr)
        loadFromFile(filename, this);
    else
        init();
}

// initial gameboard configuration
void Board::init() {
    // TODO:
    // set up the Jungle chess standard initial gameboard properly;
    // add Elephants, Lions, ..., Rats to the cells array at correct positions 
    // TODO: also add the created pieces to each player's vector of pieces

    Piece* p;
    Player* red;
    red = getGame()->getPlayer(Color::RED);
    // for player Red
    p = new Elephant(Color::RED, 6, 0);
    put(6, 0, p);
    red->addPiece(p);
    p = new Wolf(Color::RED, 6, 2);
    put(6, 2, p);
    red->addPiece(p);
    p = new Leopard(Color::RED, 6, 4);
    put(6, 4, p);
    red->addPiece(p);
    p = new Rat(Color::RED, 6, 6);
    put(6, 6, p);
    red->addPiece(p);
    p = new Cat(Color::RED, 7, 1);
    put(7, 1, p);
    red->addPiece(p);
    p = new Dog(Color::RED, 7, 5);
    put(7, 5, p);
    red->addPiece(p);
    p = new Tiger(Color::RED, 8, 0);
    put(8, 0, p);
    red->addPiece(p);
    p = new Lion(Color::RED, 8, 6);
    put(8, 6, p);
    red->addPiece(p);
    
    //for player Blue
    Player* blue;
    blue = getGame()->getPlayer(Color::BLUE);
    p = new Lion(Color::BLUE, 0, 0);
    put(0, 0, p);
    blue->addPiece(p);
    p = new Tiger(Color::BLUE, 0, 6);
    put(0, 6, p);
    blue->addPiece(p);
    p = new Dog(Color::BLUE, 1, 1);
    put(1, 1, p);
    blue->addPiece(p);
    p = new Cat(Color::BLUE, 1, 5);
    put(1, 5, p);
    blue->addPiece(p);
    p = new Rat(Color::BLUE, 2, 0);
    put(2, 0, p);
    blue->addPiece(p);
    p = new Leopard(Color::BLUE, 2, 2);
    put(2, 2, p);
    blue->addPiece(p);
    p = new Wolf(Color::BLUE, 2, 4);
    put(2, 4, p);
    blue->addPiece(p);
    p = new Elephant(Color::BLUE, 2, 6);
    put(2, 6, p);
    blue->addPiece(p);
}

// Return true if (y, x) is an empty cell, and false otherwise
bool Board::isEmpty(int y, int x) {
    if (cells[y][x] == EMPTY)
        return true;
    return false;
}

// Return true if (y, x) is the den on the side of the specified color, 
// and false otherwise
bool Board::isDen(int y, int x, Color color) {
    // TODO: Add your code here
    if (color == BLUE) {
        if (x == 3 && y == 0)
            return true;
        else
            return false;
    }
    else {
        if (x == 3 && y == 8)
            return true;
        else
            return false;
    }
}

// Return true if (y, x) is a trap on the side of the specified color, 
// and false otherwise
bool Board::isTrap(int y, int x, Color color) {
    // TODO: Add your code here
    if (color == BLUE) {
        if ((x == 2 && y == 0) || (x == 4 && y == 0) || (x == 3 && y == 1))
            return true;
        else
            return false;
    }
    else {
        if ((x == 2 && y == 8) || (x == 4 && y == 8) || (x == 3 && y == 7))
            return true;
        else
            return false;
    }
}

// Return true if (y, x) is a river cell, and false otherwise
bool Board::isRiver(int y, int x) {
    return y >= 3 && y <= 5 && (x >= 1 && x <= 2 || x >= 4 && x <= 5);
}

// Get a piece from the specified cell
Piece* Board::get(int y, int x){
    if (0 <= y && y < H && 0 <= x && x < W)
        return cells[y][x];
    return OUT_BOUND; // out of bound
}

// Put piece p onto the specified cell
void Board::put(int y, int x, Piece* p){
    cells[y][x] = p;
    if (p != EMPTY) {
        p->setY(y);
        p->setX(x);
    }
}

// Print the gameboard
void Board::print() {
    // TODO: Add code to print the HxW gameboard by looping over cells array
    // Hint: Make use of isEmpty(), isRiver(), isTrap(), isDen(), and 
    //       getLabel() of Piece to ease your work
    // Remember * for river cells, # for trap cells, X for den cells
    char pp = 'A';
    int ii = 1;
    for (int i = -1; i < H; i++) {
        for (int k = -1; k < W; k++) {
            if (i == -1) {   //print alphabetic header of the board
                if (k == -1)
                    cout << "    ";
                if(k>=0)
                    cout << (char)(pp + k)<< "   ";
            }
            else if (k == -1 && i != -1)  //print numeric row number of the board
                cout << ii + i <<" ";
            if (i >= 0 && k >= 0) {
                Piece* tmp = this->get(i, k);
                if(!(this->isEmpty(i, k))) {
                    char t = tmp->getLabel();
                    cout << t << " ";
                }
                else if (this->isTrap(i, k, BLUE) || this->isTrap(i, k, RED))
                    cout << "# ";
                else if (this->isRiver(i, k))
                    cout << "* ";
                else if (this->isDen(i, k, BLUE) || this->isDen(i, k, RED))
                    cout << "X ";
                else {
                    cout << "  ";
                } 
            }
            if(i!=-1)
                cout << "| ";
        }
        cout << "\n  +---+---+---+---+---+---+---+\n";
    }
}

// Check if the move from (y1, x1) to (y2, x2) is valid
bool Board::isMoveValid(int y1, int x1, int y2, int x2) {
    // TODO:
    // check against invalid cases, for example,
    // - the source is an empty cell
    // - the source and destination are the same position
    // - the destination is out of bound of the board (hint: use OUT_BOUND)
    // - the source piece is not of same color of current turn of the game     -->> aka: tryna move opponent's piece
    // (... and anymore ?)
             //check if the player tries to move his piece to the spot which is already occupied by his own piece
             // check if the player tries to move into his own den.
    // [Note: you can modify the following code if it doesn't fit your design]

    // Piece-specific validation
    Piece* p = get(y1, x1);
    Piece* q = get(y2, x2);
    if (p == EMPTY)
        return false;
    else if (q == OUT_BOUND)
        return false;
    else if ((x1 == x2) && (y1 == y2))   //if destination == current position
        return false;
    else if (getGame()->getTurn() != p->getColor())    //check if player try to move opponent's piece
        return false;
    else if (q != EMPTY && (p->getColor()) == (q->getColor()))   //check if the player tries to move his piece to the spot which is already occupied by his own piece
        return false;
    else if (isDen(y2, x2, p->getColor()))   //check if the player tries to move into his own den.
        return false;
    else
        return (p->isMoveValid(this, y2, x2));
}

// Carry out the move from (y1, x1) to (y2, x2)
bool Board::move(int y1, int x1, int y2, int x2) {
    if (isMoveValid(y1, x1, y2, x2)) {
        get(y1, x1)->move(this, y2, x2);
        return true;
    }
    return false;
}

// Return the pointer to the Game object
Game* Board::getGame() const {
    return game;
}
