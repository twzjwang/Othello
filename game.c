#include "game.h"

//set starting position
void init_board()
{
    int i;
    for (i = 0; i < 64; i++)
        board[i] = ' ';
    board[27] = 'o';
    board[28] = 'x';
    board[35] = 'x';
    board[36] = 'o';
    
    turn = 0;
    is_gameover = 0;
}

//print current position
void print_board()
{
    int i, d;
    char c;
    black_score = 0;
    white_score = 0;
    for (i = 0; i < 64; i++) {
        if (board[i] == 'x')
            black_score++;
        else if (board[i] == 'o')
            white_score++;
    }

    printf("\033[H\033[J");

    printf("Black  ");
    if (is_black_ai)
        printf("AI");
    else
        printf("Player");
    printf(" %-2d vs %2d ", black_score, white_score);
    if (is_white_ai)
        printf("AI");
    else
        printf("Player");    
    printf("  White\n\n");
    if (!turn)
        printf("            Black's move\n\n");
    else
        printf("            White's move\n\n");

    printf("    a   b   c   d   e   f   g   h \n");
    printf("  --------------------------------- \n");
    for (i = 1; i <= 8; i++) {
        printf("%d | %c | %c | %c | %c | %c | %c | %c | %c | %d\n\n", i,
            board[i*8-8], board[i*8-7], board[i*8-6],
            board[i*8-5], board[i*8-4], board[i*8-3],
            board[i*8-2], board[i*8-1], i);
    }
    printf("  --------------------------------- \n");
    printf("    a   b   c   d   e   f   g   h \n\n");

    if (!turn && !is_black_ai) {
        printf("input your move (e.x. 'd3') : ");
        scanf("%c%d", &c, &d);
        getchar();
        move((c - 'a')  + (d - 1) * 8, 'x');
    }
    else if (!turn && is_black_ai) {

    }
    else if (turn && !is_white_ai) {
        printf("Input move (e.x. 'd3') : ");
        do {
            scanf("%c%d", &c, &d);
        } while (c < 'a' || c > 'h' || d < 1 || d > 8);
        getchar();
        move((c - 'a')  + (d - 1) * 8, 'o');
    }
    else {

    }
}

//put disc on board
void move(int index, char color)
{
    int i;
    int mode = 0, temp_id, is_reverse = 0;
    char reverse_color = (color=='o') ? 'x' : 'o';

    if (board[index] != ' ') {
        return;
    }

    //reverse up
    mode = 0;
    temp_id = index;
    while (temp_id - 8 >= 0 && mode < 2) {
        temp_id -= 8;
        if (!mode && board[temp_id] == reverse_color)
            mode++;
        else if (mode == 1 && board[temp_id] == color) {
            mode++;
            is_reverse = 1;        
        } else if (board[temp_id] == ' ')
            break;
    }
    for (i = temp_id + 8; mode == 2 && i < index; i += 8)
        board[i] = color;

    //reverse down
    mode = 0;
    temp_id = index;
    while (temp_id + 8 < 64 && mode < 2) {
        temp_id += 8;
        if (!mode && board[temp_id] == reverse_color)
            mode++;
        else if (mode == 1 && board[temp_id] == color) {
            mode++;
            is_reverse = 1;        
        } else if (board[temp_id] == ' ')
            break;
    }
    for (i = temp_id - 8; mode == 2 && i > index; i -= 8)
        board[i] = color;

    //reverse left
    mode = 0;
    temp_id = index;
    while (temp_id - 1 >= index / 8 * 8 && mode < 2) {
        temp_id--;
        if (!mode && board[temp_id] == reverse_color)
            mode++;
        else if (mode == 1 && board[temp_id] == color) {
            mode++;
            is_reverse = 1;        
        } else if (board[temp_id] == ' ')
            break;
    }
    for (i = temp_id + 1; mode == 2 && i < index; i++)
        board[i] = color;

    //reverse right
    mode = 0;
    temp_id = index;
    while (temp_id + 1 < (index / 8 * 8 + 8) && mode < 2) {
        temp_id++;
        if (!mode && board[temp_id] == reverse_color)
            mode++;
        else if (mode == 1 && board[temp_id] == color) {
            mode++;
            is_reverse = 1;        
        } else if (board[temp_id] == ' ')
            break;
    }
    for (i = temp_id - 1; mode == 2 && i > index; i--)
        board[i] = color;

    //reverse upleft
    mode = 0;
    temp_id = index;
    while (temp_id - 9 >= 0 && (temp_id - 9) % 8 < index % 8 && mode < 2) {
        temp_id -= 9;
        if (!mode && board[temp_id] == reverse_color)
            mode++;
        else if (mode == 1 && board[temp_id] == color) {
            mode++;
            is_reverse = 1;        
        } else if (board[temp_id] == ' ')
            break;
    }
    for (i = temp_id + 9; mode == 2 && i < index; i += 9)
        board[i] = color;

    //reverse upright
    mode = 0;
    temp_id = index;
    while (temp_id - 7 >= 0 && (temp_id - 7) % 8 > index % 8 && mode < 2) {
        temp_id -= 7;
        if (!mode && board[temp_id] == reverse_color)
            mode++;
        else if (mode == 1 && board[temp_id] == color) {
            mode++;
            is_reverse = 1;        
        } else if (board[temp_id] == ' ')
            break;
    }
    for (i = temp_id + 7; mode == 2 && i < index; i += 7)
        board[i] = color;

    //reverse downleft
    mode = 0;
    temp_id = index;
    while (temp_id + 7 >= 0 && (temp_id + 7) % 8 < index % 8 && mode < 2) {
        temp_id += 7;
        if (!mode && board[temp_id] == reverse_color)
            mode++;
        else if (mode == 1 && board[temp_id] == color) {
            mode++;
            is_reverse = 1;        
        } else if (board[temp_id] == ' ')
            break;
    }
    for (i = temp_id - 7; mode == 2 && i > index; i -= 7)
        board[i] = color;

    //reverse downright
    mode = 0;
    temp_id = index;
    while (temp_id + 9 >= 0 && (temp_id + 9) % 8 > index % 8 && mode < 2) {
        temp_id += 9;
        if (!mode && board[temp_id] == reverse_color)
            mode++;
        else if (mode == 1 && board[temp_id] == color) {
            mode++;
            is_reverse = 1;        
        } else if (board[temp_id] == ' ')
            break;
    }
    for (i = temp_id - 9; mode == 2 && i > index; i -= 9)
        board[i] = color;

    if (is_reverse) {
        board[index] = color;
        turn = 1 - turn;
    }
}


