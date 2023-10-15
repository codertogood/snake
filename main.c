#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#define body '0'
#define head '8'
#define head2 '8'
#define tail '~'
#define tail2 '?'
#define apple '+'
#define empty ' '
int direction = 3;
int tail_direction = 3;
int score = 0;
void update();
void display();
void init_board();
void quit();
int crash(char square);
int tail_directions[700];
int board[700];
int langth;
int main(){
    initscr();
    keypad(stdscr, TRUE);
    wtimeout(stdscr, 400);
    noecho();
    init_board();
    display();
    while (1){
        update();
        //getch();
        clear();
        display();
    }
    endwin();
}
void update(){
    int ch = getch();
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
     int apple_ate = 0;

    for(int i=0; i<700; i+=1){    
        if(board[i] == head ){
            if(direction == 1){
                if(board[i-1] == apple){
                    langth += 1;
                    apple_ate = 1;
                    score += 1;
                }else if(crash(board[i-1])){
                    quit();
                }
                if(i-1 < 0){
                    board[i + 699] = head;
                }else{
                board[i-1] = head;
                }
                board[i] = body;
            }else if(direction == 2){ 
                if(board[i-50] == apple){
                    langth += 1;
                    apple_ate = 1;
                    score += 1;
                }else if(crash(board[i-50])){
                    quit();
                }
                if(i-50 < 0){
                    board[i - 50 + 699] = head;
                }else{
                board[i-50] = head;
                }
                board[i] = body;
            }else if(direction == 3){
                if(board[i+1] == apple){
                    langth += 1;
                    apple_ate = 1;
                    score += 1;
                }else if(crash(board[i+1])){
                    quit();
                }
                board[i] = body;
               if(i+1 >699){
                    board[i - 699] = head;
                }else{
                board[i+1] = head;
                }
            }else if(direction == 4){ 
                if(board[i+50] == apple){
                    langth += 1;
                    apple_ate = 1;
                    score += 1;
                }else if(crash(board[i+50])){
                    quit();
                }
                board[i] = body;
                if(i+50 > 699){
                    board[i + 50 - 699] = head;
                }else{
                board[i+50] = head;
                }
            }
            break;   
        }
    }

    for(int i=700; i>0; i-=1){
        tail_directions[i] = tail_directions[i-1];
        // 3 2 1 0
        // 2 3 4 1
    }
    tail_directions[0] = direction;
    tail_direction = tail_directions[langth];
    //printw("%i\n", tail_direction);
        //printw("\n%i", direction);
    if (apple_ate){
        int randome = rand() % 700 + 0;
        while(board[randome] != empty){
            randome = rand() % 700 + 0;
        }
        board[randome] = apple;
        return;
    }
        
    for(int i=0; i<700; i+=1){
        if(board[i] == tail||board[i] == tail2){
            if(tail_direction == 1){ 
                 if(i-1 < 0){
                    board[i + 699] = tail;
                }else{
                    board[i-1] = tail;
                }    
                board[i] = empty;    
            }else if(tail_direction == 2){
                if(i-50 < 0){
                    board[i - 50 + 699] = tail2;
                }else{
                board[i-50] = tail2;
                }
                board[i] = empty;
            }else if(tail_direction == 3){ 
                if(i+1 > 699){
                    board[i - 699] = tail;
                }else{
                board[i+1] = tail;
                }
                board[i] = empty;
            }else if(tail_direction == 4){ 
                if(i+50 > 699){
                    board[i + 50 - 699] = tail2;
                }else{
                board[i+50] = tail2;
                }
                board[i] = empty;
            }  
            break;  
        }
    }    
}

// direction 1 = left, derection 2 = up, derection 3 = right, derection 4 = down.
void quit(){
    clear();
    printw("  _____                 ____              \n / ___/__ ___ _  ___   / __ \\_  _____ ____\n/ (_ / _ `/  \' \\/ -_) / /_/ / |/ / -_) __/\n\\___/\\_,_/_/_/_/\\__/  \\____/|___/\\__/_/   \n   \n your score was:%i\n", score);
    refresh();
    sleep(5);
    endwin();
    exit(0);
}

int crash(char square){
    return square == body|| square == tail|| square == tail2;
}

void display(){
    int index=0;
    printw(" --------------------------------------------------  score: %i\n", score);
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
    board[8]=tail;
   // board[7]=body;
   // board[6]=body;
   // board[5]=body;
   board[375]=apple;
    langth = 2;
    tail_directions[0] = 3;
    tail_directions[1] = 3;
}

//  ∞
//  0
//  0
//  0
//  0
//  ?
//  ~08 +