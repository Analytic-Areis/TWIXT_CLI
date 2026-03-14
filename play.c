#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "play.h"
#include "board.h"

int yellow_full(){
    for(int i=0;i<MAX;i++){
        for(int j=1;j<MAX-1;j++){
            if(board[i][j].player == '.') return 0;
        }
    }
    return 1;
}

int blue_full(){
    for(int i=1;i<MAX-1;i++){
        for(int j=0;j<MAX;j++){
            if(board[i][j].player == '.') return 0;
        }
    }
    return 1;
}


char input(int *n, int *m) {
    char col;
    int row;
    char temp[64];

    printf(BOLD"Enter position"RESET" (e.g., A6, C12) "BOLD "or -1 to resign: "RESET);

    if (scanf("%63s", temp) != 1) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
        return 0;
    }

    if (strcmp(temp, "-1") == 0) {
        return -1;
    }

    if (sscanf(temp, " %c%d", &col, &row) != 2) return 0;
    if (col >= 'a' && col <= 'z') col -= 32;

    *m = col - 'A';
    *n = row-1;

    if (*m < 0 || *m >= MAX || *n < 0 || *n >= MAX) return 0;
    return board[*n][*m].player;
}

void input_yellow(int *x, int *y){
    int n,m;
    printf(YELLOW BOLD"\nPLAYER 1's (O) TURN\n"RESET);
    if(yellow_full()){
        printf("\nNo More playable moves to play for "YELLOW BOLD"Yellow!\n" RESET BOLD "Game DRAW!\n" RESET);
        exit(EXIT_SUCCESS);
    }
    while(1) {
        char ret = input(&n,&m);
        if (ret == -1){
            printf(YELLOW BOLD"Yellow resign!"RESET);
            exit(EXIT_SUCCESS);
        }
        if (ret != 0 && ret == '.' && m > 0 && m < MAX-1) break;
        print_board();
        printf(YELLOW BOLD"\nInvalid input for PLAYER 1 try again!\n" RESET);
    }
    board[n][m].player = 'o';
    *x = n;
    *y = m;
    return;
}

void input_blue(int *x, int *y){
    int n,m;
    printf(BLUE BOLD"\nPLAYER 2's (X) TURN\n"RESET);
    if(blue_full()){
        printf("\nNo More playable moves to play for "BLUE"Blue!\n" RESET BOLD "Game DRAW!\n" RESET);
        exit(EXIT_SUCCESS);
    }
    while(1){
        char ret = input(&n,&m);
        if (ret == -1){
            printf(BLUE BOLD"Blue resign!"RESET);
            exit(EXIT_SUCCESS);
        }
        if (ret != 0 && ret == '.' && n > 0 && n < MAX-1) break;
        print_board();
        printf(YELLOW BOLD"\nInvalid input for PLAYER 2 try again!\n"RESET);
    }
    board[n][m].player = 'x';
    *x = n;
    *y = m;

    return;
}
