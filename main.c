#include <stdio.h>
#include <ncurses.h>
#define body '0'
#define head '8'
#define apple '+'
#define empty ' '
int direction = 3;
//<1 ^2 >3 V4
void update();
void display();
void init_board();
char board[700];
int main(){
    initscr();
    keypad(stdscr, TRUE);
    wtimeout(stdscr, 1000);
    noecho();
    init_board();
    while (1){
        update();
        clear();
        display();
    }
    endwin();
}
void update(){
    char ch = getch();
    switch(ch){
        case KEY_LEFT:
            direction = 1;
            break;
        case KEY_UP:
            direction = 2;
            break;
        case KEY_RIGHT:
            direction = 3;
            break;
        case KEY_DOWN:
            direction = 4;
            break;
    }
    
}
void display(){
    int index=0;
    printw(" --------------------------------------------------\n");
    for(int i=0; i<14; i+=1){
        printw("|");
        for(int j=0; j<50; j+=1){
            printw("%c",board[index]);
            index+=1;
        }
        printw("|\n");
    }
    printw(" --------------------------------------------------\n");
}
void init_board(){
    for(int i=0; i<700; i+=1){
        board[i]=empty;
    }
    board[10]=head;
    board[9]=body;
    board[8]=body;
    board[7]=body;
    board[6]=body;
    board[5]=body;

}
//  ∞
//  0
//  0
//  0
//  0
//  00000008 +