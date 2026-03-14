#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"

int checker[MAX][MAX][2];

void display_link_board(){
    int x1, y1;
    char c;
    for(int i=0; i<MAX; i++){
        for(int j=0; j<MAX; j++){
            c = board[i][j].player;

            for(int k=0; k<8; k++){
                if(display1[i][j][k]){

                    x1 = board[i][j].links.x_coords[k];
                    y1 = board[i][j].links.y_coords[k];

                    if (x1 != -1 && y1 != -1 && display1[x1][y1][7-k]) {

                        if(c == 'X')
                            printf("\nA link for " BLUE BOLD "'X' " RESET "has been established between "BLUE BOLD"(%c%d) <---> (%c%d)\n"RESET,
                                j+'A', i+1, y1+'A', x1+1);

                        if(c == 'O')
                            printf("\nA link for " YELLOW BOLD "'O' " RESET"has been established between "YELLOW BOLD"(%c%d) <---> (%c%d)\n"RESET,
                                j+'A', i+1, y1+'A', x1+1);
                        display1[i][j][k] = 0;
                        display1[x1][y1][7-k] = 0;
                    }
                }
            }
        }
    }
}

void delay() {
    long long i;
    for(i = 0; i < 1e9*4; i++);
}

double absd(double x){
    if(x<0) return -x;
    else return x;
}

int between01(double t){
    return (t > 0.000001 && t < 0.999999);
}

int segment_intersection(double Ax, double Ay, double Bx, double By,double Cx, double Cy, double Dx, double Dy){
    double delta_x1 = Bx - Ax;
    double delta_y1 = By - Ay;
    double delta_x2 = Dx - Cx;
    double delta_y2 = Dy - Cy;

    double denom = delta_x1 * delta_y2 - delta_y1 * delta_x2;
    if (absd(denom) < 1e-9) return 0;

    double t = ((Cx - Ax) * delta_y2 - (Cy - Ay) * delta_x2) / denom;
    double u = ((Cx - Ax) * delta_y1 - (Cy - Ay) * delta_x1) / denom;

    if (between01(t) && between01(u)) return 1;
    return 0;
}

int prevent_crosslink(int x, int y, int x1, int y1){
    double Ax = y,  Ay = x;
    double Bx = y1, By = x1;

    for(int i=0; i<MAX; i++){
        for(int j=0; j<MAX; j++){

            if (board[i][j].links.link_count == 0) continue;

            for(int k=0; k<8; k++){
                int ex = board[i][j].links.x_coords[k];
                int ey = board[i][j].links.y_coords[k];

                if(ex == -1 || ey == -1) 
                    continue;

                if ((i==x && j==y) || (i==x1 && j==y1) || (ex==x && ey==y) || (ex==x1 && ey==y1)) continue;

                double Cx = j,  Cy = i;
                double Dx = ey, Dy = ex;

                if (segment_intersection(Ax,Ay,Bx,By, Cx,Cy,Dx,Dy)) return 0;
            }
        }
    }
    return 1;
}

int check_all_links(int x, int y){
    int x_arr[8] = {1,1,2,2,-2,-2,-1,-1};
    int y_arr[8] = {2,-2,1,-1,1,-1,2,-2};

    char pos = board[x][y].player;

    for (int k = 0; k < 8; k++) {

        int x1 = x + x_arr[k];
        int y1 = y + y_arr[k];

        if (x1 < 0 || x1 >= MAX || y1 < 0 || y1 >= MAX) continue;

        if (pos == 'o' && (board[x1][y1].player=='o' || board[x1][y1].player=='O')){
            if (prevent_crosslink(x,y,x1,y1)){
                board[x][y].player='O';
                board[x1][y1].player='O';

                board[x][y].links.x_coords[k] = x1;
                board[x][y].links.y_coords[k] = y1;
                board[x1][y1].links.x_coords[7-k] = x;
                board[x1][y1].links.y_coords[7-k] = y;

                board[x][y].links.link_count++;
                board[x1][y1].links.link_count++;
            }
            else {
                printf("\nCross-link prevented between "YELLOW BOLD"(%c%d) <-/-> (%c%d)\n"RESET, y+'A',x+1,y1+'A',x1+1);
                delay();
            }
        }

        if (pos=='x' && (board[x1][y1].player=='x' || board[x1][y1].player=='X')){
            if (prevent_crosslink(x,y,x1,y1)){
                board[x][y].player='X';
                board[x1][y1].player='X';

                board[x][y].links.x_coords[k] = x1;
                board[x][y].links.y_coords[k] = y1;
                board[x1][y1].links.x_coords[7-k] = x;
                board[x1][y1].links.y_coords[7-k] = y;

                board[x][y].links.link_count++;
                board[x1][y1].links.link_count++;
            }
            else {
                printf("\nCross-link prevented between "BLUE BOLD"(%c%d) <-/-> (%c%d)\n"RESET, y+'A',x,y1+'A',x1);
                delay();
            }
        }
    }
    return board[x][y].links.link_count;
}


int yellow_dp[MAX][MAX];
int blue_dp[MAX][MAX];

int is_yellow_cell(int x, int y){ char c = board[x][y].player; return (c=='o' || c=='O'); } 
int is_blue_cell(int x, int y){ char c = board[x][y].player; return (c=='x' || c=='X'); }

int yellow_win(int x, int y){
    if (!is_yellow_cell(x,y)) return 0;
    if (x == MAX-1) return 1;

    if (yellow_dp[x][y] != -1) return yellow_dp[x][y];

    int res = 0;

    for (int k = 0; k < 8; k++){
        int nx = board[x][y].links.x_coords[k];
        int ny = board[x][y].links.y_coords[k];

        if (nx == -1 || ny == -1) continue;
        if (!is_yellow_cell(nx, ny)) continue;
        if (nx <= x) continue;

        if (yellow_win(nx, ny)) {
            res = 1;
            break;
        }
    }

    yellow_dp[x][y] = res;
    return res;
}

int blue_win(int x, int y){
    if (!is_blue_cell(x,y)) return 0;
    if (y == MAX-1) return 1;

    if (blue_dp[x][y] != -1) return blue_dp[x][y];

    int res = 0;

    for (int k = 0; k < 8; k++){
        int nx = board[x][y].links.x_coords[k];
        int ny = board[x][y].links.y_coords[k];

        if (nx == -1 || ny == -1) continue;
        if (!is_blue_cell(nx, ny)) continue;

        if (ny <= y) continue;

        if (blue_win(nx, ny)) {
            res = 1;
            break;
        }
    }

    blue_dp[x][y] = res;
    return res;
}

int check_winner(){
    for (int i = 0; i < MAX; i++){
        for (int j = 0; j < MAX; j++){
            yellow_dp[i][j] = -1;
            blue_dp[i][j] = -1;
        }
    }
    for (int j = 0; j < MAX; j++){
        if (is_yellow_cell(0, j)){
            if (yellow_win(0, j))
                return 1;  // Yellow wins
        }
    }

    for (int i = 0; i < MAX; i++){
        if (is_blue_cell(i, 0)){
            if (blue_win(i, 0))
                return 2;  // Blue wins
        }
    }

    return 0; // No winner
}
