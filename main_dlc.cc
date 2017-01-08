#include <iostream>
#include <string>
#include <vector>
#include "floor.h"
#include <termios.h>
#include <stdio.h>

using namespace std;
/* Read 1 character without echo */
static struct termios old, keyw;

void initTermios(int echo) {
    tcgetattr(0, &old);
    keyw = old;
    keyw.c_lflag &= ~ICANON;
    keyw.c_lflag &= echo ? ECHO : ~ECHO;
    tcsetattr(0, TCSANOW, &keyw);
}

void resetTermios(void) {
    tcsetattr(0, TCSANOW, &old);
}

char getch_(int echo) {
    char ch;
    initTermios(echo);
    ch = getchar();
    resetTermios();
    return ch;
}

char getch() 
{
  return getch_(0);
}

string translate(char input) {
    if(input == 'w') return "no";
    if(input == 'd') return "ea";
    if(input == 'x') return "so";
    if(input == 'a') return "we";
    if(input == 'e') return "ne";
    if(input == 'q') return "nw";
    if(input == 'z') return "sw";
    if(input == 'c') return "se";
    if(input == 'o') return "a";
    if(input == 'p') return "u";
    if(input == '1') return "s";
    if(input == '2') return "d";
    if(input == '3') return "v";
    if(input == '4') return "g";
    if(input == '5') return "t";
    if(input == '6') return "h";
    if(input == '`') return "f";
    if(input == 10) return "r";
    if(input == 27) return "q";
    return "";
}

int main() {
        char input;
        string cmd;
        Floor fl(25,79);
        string input_file = "";
        fl.loadLevels(input_file);

        printf("\n");
        printf("  / __/ __|__ / |/ /\n");
        printf(" | (_| (__ |_ \\ ' < \n");
        printf("  \\___\\___|___/_|\\_\\\n");
        printf("\n");
        printf("Press Enter to start\n");
        printf("Press Esc to quit\n");

        try {
        while (true) {
            input = getch();
            cmd = translate(input);
            if (!fl.alive()) { 
                printf("\n");
                printf(" __      ____ _ ___| |_ ___  __| |\n");
                printf(" \\ \\ /\\ / / _` / __| __/ _ \\/ _` |\n");
                printf("  \\ V  V / (_| \\__ \\ ||  __/ (_| |\n");
                printf("   \\_/\\_/ \\__,_|___/\\__\\___|\\__,_|\n");
                printf("\n");
                printf("Press Enter to restart\n");
                printf("Press Esc to quit\n");
                input = getch();
                if(input == 'r') {
                        cmd = "r";
                }
                else if(input == 't') {
                        cmd = "quit";
                }
            }
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
                        cout << "You have won the game!" << endl; break; }
                }
                else if (cmd == "u") {
                    string dir;
                    input = getch();
                    dir = translate(input);
                    if (fl.usePotion(dir)) fl.enemyAction();
                    fl.displayFloor();
                }
                else if (cmd == "a") {
                    string dir;
                    input = getch();
                    dir = translate(input);
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
        return 0;
}
