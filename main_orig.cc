#include <iostream>
#include <string>
#include <vector>
#include "floor.h"
using namespace std;

int main(int argc, char *argv[]) {
    cin.exceptions(ios::eofbit|ios::failbit);
    string cmd;
    Floor fl(25,79);
    string input_file = "";

    if ( argc >= 2 ) {
        input_file = argv[1];
    }

    fl.loadLevels(input_file);
    fl.displayFloor();

    try {
        while (true) {
            if (!fl.alive()) { cout << "You dead. Restart or quit." << endl; }
            cin >> cmd;
            if (cmd == "r") {
                fl.restart();
                fl.displayFloor();
            }
            else if ((cmd == "q") || (cmd == "quit") || (cmd == "exit")) break;

            if (fl.alive()) {
                if ((cmd == "no") || (cmd == "so") || (cmd == "ea") ||
                    (cmd == "we") || (cmd == "ne") || (cmd == "nw") ||
                    (cmd == "se") || (cmd == "sw")) {
                    if (fl.movePlayer(cmd)) fl.enemyAction();
                    fl.displayFloor();
                    if (fl.gameEnd()) { 
                        cout << "You have won the game! Final Score: " << 
                            fl.getScore() << endl; 
                        break; }
                }
                else if (cmd == "u") {
                    string dir;
                    cin >> dir;
                    if (fl.usePotion(dir)) fl.enemyAction();
                    fl.displayFloor();
                }
                else if (cmd == "a") {
                    string dir;
                    cin >> dir;
                    if (fl.attack(dir)) fl.enemyAction();
                    fl.displayFloor();
                }
                else if (cmd == "f") {
                    fl.toggleFreeze();
                    fl.displayFloor();
                }
                else if ((cmd == "s") || (cmd == "d") || (cmd == "v") || 
                        (cmd == "g") || (cmd == "t") || (cmd == "h")) {
                    fl.generate(cmd, true);
                    fl.displayFloor();
                }
            }
        }
    }
    catch (ios::failure &) {
    }
}
