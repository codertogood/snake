#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/time.h>
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
int game_quit = 0;
int game_over = 0;
int fast = 400;
int slow = 550;
struct timeval stop, start;
int main(){
    initscr();
    keypad(stdscr, TRUE);
    wtimeout(stdscr, fast);
    noecho();
    init_board();
    display();
    while(!game_quit){
        init_board();
        while (!game_over){
            update();
            //getch();
            clear();
            display();
        }
        game_over = 0;
    }
    endwin();
}
void update(){
    gettimeofday(&start, 0);
    int ch = getch();
    gettimeofday(&stop, 0);
    unsigned int mill = ((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);

    if((1000 * fast) - (int)mill  > 0){
        //refresh();
        usleep((fast * 1000) - (int)mill);

    }
    switch(ch){
        case KEY_LEFT:
            direction = 1;
            wtimeout(stdscr, fast);
            break;
        case KEY_UP:
            direction = 2;
            wtimeout(stdscr, slow);
            break;
        case KEY_RIGHT:
            direction = 3;
            wtimeout(stdscr, fast);
            break;
        case KEY_DOWN:
            direction = 4;
            wtimeout(stdscr, slow);
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
                    return;
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
                    return;
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
                    return;
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
                    return;
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
    printw("  _____                 ____              \n / ___/__ ___ _  ___   / __ \\_  _____ ____\n/ (_ / _ `/  \' \\/ -_) / /_/ / |/ / -_) __/\n\\___/\\_,_/_/_/_/\\__/  \\____/|___/\\__/_/   \n   \n your score was:%i\n Press enter to play again\n Press backspace to quit\n", score);
    refresh();
    game_over = 1;
    wtimeout(stdscr, -1);
    sleep(1);
    while(1){
        int ch = getch();
        if(ch == KEY_BACKSPACE){
            endwin();
            game_quit = 1;
            exit(0);
        }else if(ch == '\n'){
           wtimeout(stdscr, fast);
            break;
        }
    }
    
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
    score = 0;
    direction = 3;
    tail_direction = 3;
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