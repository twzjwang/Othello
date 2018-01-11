#ifndef _GAME_H
#define _GAME_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

char board[64]; //x : black, o : white
int black_score, white_score;   //current discs number
int is_black_ai, is_white_ai;   //0 : player, 1 : ai
int is_gameover;    //0 : process, 1 : gameover
int turn;   //0 : black, 1 : white
int i, black_mobility, white_mobility;
char history[256];

//set starting position
void init_board();

//print current position
void print_board();

//put disc on board
void move(int index, char color);

#endif


