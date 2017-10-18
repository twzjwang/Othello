#ifndef _GAME_H
#define _GAME_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int board[8][8];
int black_num, white_num;

int gameover;
int turn;

void init_board();

void print_board();

int move_pos();

void next_move();

void start_game();

#endif

