#ifndef BOARD_H
#define BOARD_H
#include"game.h"

#define MAX 24
#define BOLD    "\033[1m"
#define YELLOW  "\033[93m"
#define BLUE    "\033[36m"
#define RESET   "\033[0m"
#define MAGENTA "\033[95m"
#define GREY    "\e[90m"
#define L_GREY  "\033[37m"

extern int display1[MAX][MAX][8];
extern int display2[MAX][MAX][8];


typedef struct link_store{
    int link_count;
    int x_coords[8];
    int y_coords[8];
}link_store;


typedef struct square{
    char player; //'.' is empyt ; 'O' is yellow (player 1); 'X' is Blue (player 2) '*' is not valid state;
    link_store links;
}square;

extern square board[MAX][MAX];


void init_board();
void print_board();

#endif