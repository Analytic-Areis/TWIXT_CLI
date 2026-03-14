#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"play.h"
#include"game.h"
#include"board.h"

int main(){
    init_board();
    print_board();
    int x,y;
    while(1){
        // Yellow move
        input_yellow(&x,&y);
        check_all_links(x,y);
        print_board();
        display_link_board();

        int win = check_winner();
        if (win == 1){
            printf("\n" YELLOW BOLD "Yellow (O) WINS by connecting top to bottom!\n" RESET);
            exit(EXIT_SUCCESS);
        } else if (win == 2){
            printf("\n" BLUE BOLD "Blue (X) WINS by connecting left to right!\n" RESET);
            exit(EXIT_SUCCESS);
        }

        // Blue move
        input_blue(&x,&y);
        check_all_links(x,y);
        print_board();
        display_link_board();

        win = check_winner();
        if (win == 1){
            printf("\n" YELLOW BOLD "Yellow (O) WINS by connecting top to bottom!\n" RESET);
            exit(EXIT_SUCCESS);
        } else if (win == 2){
            printf("\n" BLUE BOLD "Blue (X) WINS by connecting left to right!\n" RESET);
            exit(EXIT_SUCCESS);
        }
    }
    return 0;
}
