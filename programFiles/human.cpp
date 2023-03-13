#include <iostream>
#include "../headerFiles/human.h"
#include "../headerFiles/game.h"
#include "../headerFiles/board.h"

using namespace std;

Human::Human(string name, Color color) : Player(name, color) { }

void Human::makeMove(Board* board) {
    while (true) {
        cout << this->getName() <<  "'s turn: ";
        char c1, c2;    // columns letters
        int r1, r2;     // row indexes (begin at 1)
        cin >> c1 >> r1 >> c2 >> r2;
        // if input fails, reset cin's state, skip the buffer and try again
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid. Try again!" << endl;
            continue;
        }
        
        // ad hoc stop condition (surrender)
        if (c1 == 'Z' && c2 == 'Z' && r1 == 0 && r2 == 0) {
            board->getGame()->setState(GAME_OVER);
            // TODO: set opponent as winner, 
            board->getGame()->setTurn(Color(1-(int)(board->getGame()->getTurn())));
            // e.g. by flipping the turn (if you assumed the player 
            // making the last turn before game over is the winner)
            return;
        }
        
        // TODO:
        // Convert r1, c1 and r2, c2 into integers y1, x1, y2, x2 
        int y1 = r1 - 1, y2 = r2 - 1;
        int x1, x2;
        if (c1 >= 'a' && c1 <= 'g')
            x1 = c1 - 'a';
        else if (c1 >= 'A' && c1 <= 'G')
            x1 = c1 - 'A';
        if (c2 >= 'a' && c2 <= 'g')
            x2 = c2 - 'a';
        else if (c2 >= 'A' && c2 <= 'G')
            x2 = c2 - 'A';
        bool valid = board->move(y1, x1, y2, x2);
        if (valid)
            break;
        cout << "Invalid. Try again!" << endl;
    }
}
