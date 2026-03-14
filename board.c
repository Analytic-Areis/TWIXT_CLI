#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"board.h"

int display1[MAX][MAX][8];
int display2[MAX][MAX][8];
square board[MAX][MAX];

void init_board(){
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            board[i][j].player = '.';
            board[i][j].links.link_count = 0;
            for(int k=0;k<8;k++){
                board[i][j].links.x_coords[k] = -1;
                board[i][j].links.y_coords[k] = -1;
                display1[i][j][k] = 1;
                display2[i][j][k] = 1;
            }
        }
    }
    board[0][MAX-1].player = ' ';
    board[MAX-1][0].player = ' ';
    board[MAX-1][MAX-1].player = ' ';
    board[0][0].player = ' ';
}

void print_board() {
    printf("\033[2J\033[H"); // Clear screen
    printf(MAGENTA"████████╗██╗    ██╗ ██╗ ██╗  ██╗████████╗\n");
    printf("╚══██╔══╝██║    ██║ ██║  █║  █╔╝╚══██╔══╝\n");
    printf("   ██║   ██║ █╗ ██║ ██║    █╔╝     ██║   \n");
    printf("   ██║   ██║███╗██║ ██║  █╔═██╗    ██║   \n");
    printf("   ██║   ╚███╔███╔╝ ██║ ██║  ██╗   ██║   \n");
    printf("   ╚═╝    ╚══╝╚══╝  ╚═╝ ╚═╝  ╚═╝   ╚═╝   \n\n"RESET);

    printf("   ");  
    for (int col = 0; col < MAX; col++) {
        if (col == 1 || col == MAX-1) printf(BLUE BOLD "|" RESET " ");
        printf(BOLD "%c " RESET, 'A' + col);
    }
    printf("\n");

    for (int i = 0; i < MAX; i++) {

        if (i == 1 || i == MAX-1) {
            printf(" ");  
            printf(YELLOW BOLD "----" RESET MAGENTA "+" YELLOW);
            for (int x = 0; x < (MAX - 2) * 2; x++) printf("-");
            printf("-" MAGENTA "+" YELLOW "----" RESET "\n");
        }

        printf(BOLD "%02d " RESET, i+1);

        for (int j = 0; j < MAX; j++) {

            if (j == 1 || j == MAX-1) printf(BLUE BOLD "|" RESET " ");

            char c = board[i][j].player;

            if (c == 'O' || c == 'o') {
                if (c == 'O') printf(BOLD YELLOW "O " RESET);
                else printf(BOLD "O " RESET);
            }
            else if (c == 'X' || c == 'x') {
                if (c == 'X') printf(BOLD BLUE "X " RESET);
                else printf(BOLD "X " RESET);
            }
            else {
                printf(GREY BOLD"%c " RESET, c);
            }
        }

        printf(BOLD "%02d" RESET, i+1);
        printf("\n");
    }

    printf("   ");
    for (int col = 0; col < MAX; col++) {
        if (col == 1 || col == MAX-1) printf(BLUE BOLD "|" RESET " ");
        printf(BOLD "%c " RESET, 'A' + col);
    }
    printf("\n");
}

