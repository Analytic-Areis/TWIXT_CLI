#ifndef GAME_H
#define GAME_H

#include "board.h"

void display_link_board();
void delay();
int segment_intersection(double Ax, double Ay, double Bx, double By, double Cx, double Cy, double Dx, double Dy);
int prevent_crosslink(int x, int y, int x1, int y1);
int check_all_links(int x, int y);


int check_winner();
int yellow_win(int x, int y);
int blue_win(int x, int y);

#endif
