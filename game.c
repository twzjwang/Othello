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
    black_mobility = 4;
    white_mobility = 4;
    memset(history, '\0', sizeof(history));
}

//print current position
void print_board()
{
    int i;
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
    printf("  %-2d vs %2d  ", black_score, white_score);
    if (is_white_ai)
        printf("AI");
    else
        printf("Player");    
    printf("  White\n");   
    printf("\n");
    printf("History : ");
    for (i = 0; i < 2 * (black_score + white_score - 4); i += 2) {
        if (i % 20 == 0)
             printf("\n");   
        printf(" %c%c", history[i], history[i + 1]);
    }
    printf("\n");
    if (!turn)
        printf("\n\n            Black's move\n\n");
    else
        printf("\n\n            White's move\n\n");

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
}

int count_mobility(char color)
{
    int sum = 0, index;
    int mode = 0, temp_id, is_reverse = 0;
    char reverse_color = (color=='o') ? 'x' : 'o';

    for (index = 0; index < 64; index++) {
        if (board[index] != ' ') {
            continue;
        }
        is_reverse = 0;
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
            else if (mode == 0 && board[temp_id] == color)
                break;
        }

        //reverse down
        mode = 0;
        temp_id = index;
        while (!is_reverse && temp_id + 8 < 64 && mode < 2) {
            temp_id += 8;
            if (!mode && board[temp_id] == reverse_color)
                mode++;
            else if (mode == 1 && board[temp_id] == color) {
                mode++;
                is_reverse = 1;        
            } else if (board[temp_id] == ' ')
                break;
            else if (mode == 0 && board[temp_id] == color)
                break;
        }

        //reverse left
        mode = 0;
        temp_id = index;
        while (!is_reverse && temp_id - 1 >= index / 8 * 8 && mode < 2) {
            temp_id--;
            if (!mode && board[temp_id] == reverse_color)
                mode++;
            else if (mode == 1 && board[temp_id] == color) {
                mode++;
                is_reverse = 1;        
            } else if (board[temp_id] == ' ')
                break;
            else if (mode == 0 && board[temp_id] == color)
                break;
        }

        //reverse right
        mode = 0;
        temp_id = index;
        while (!is_reverse && temp_id + 1 < (index / 8 * 8 + 8) && mode < 2) {
            temp_id++;
            if (!mode && board[temp_id] == reverse_color)
                mode++;
            else if (mode == 1 && board[temp_id] == color) {
                mode++;
                is_reverse = 1;        
            } else if (board[temp_id] == ' ')
                break;
            else if (mode == 0 && board[temp_id] == color)
                break;
        }

        //reverse upleft
        mode = 0;
        temp_id = index;
        while (!is_reverse && temp_id - 9 >= 0 && (temp_id - 9) % 8 < index % 8 && mode < 2) {
            temp_id -= 9;
            if (!mode && board[temp_id] == reverse_color)
                mode++;
            else if (mode == 1 && board[temp_id] == color) {
                mode++;
                is_reverse = 1;        
            } else if (board[temp_id] == ' ')
                break;
            else if (mode == 0 && board[temp_id] == color)
                break;
        }
        //reverse upright
        mode = 0;
        temp_id = index;
        while (!is_reverse && temp_id - 7 >= 0 && (temp_id - 7) % 8 > index % 8 && mode < 2) {
            temp_id -= 7;
            if (!mode && board[temp_id] == reverse_color)
                mode++;
            else if (mode == 1 && board[temp_id] == color) {
                mode++;
                is_reverse = 1;        
            } else if (board[temp_id] == ' ')
                break;
            else if (mode == 0 && board[temp_id] == color)
                break;
        }

        //reverse downleft
        mode = 0;
        temp_id = index;
        while (!is_reverse && temp_id + 7 >= 0 && (temp_id + 7) % 8 < index % 8 && mode < 2) {
            temp_id += 7;
            if (!mode && board[temp_id] == reverse_color)
                mode++;
            else if (mode == 1 && board[temp_id] == color) {
                mode++;
                is_reverse = 1;        
            } else if (board[temp_id] == ' ')
                break;
            else if (mode == 0 && board[temp_id] == color)
                break;
        }

        //reverse downright
        mode = 0;
        temp_id = index;
        while (!is_reverse && temp_id + 9 >= 0 && (temp_id + 9) % 8 > index % 8 && mode < 2) {
            temp_id += 9;
            if (!mode && board[temp_id] == reverse_color)
                mode++;
            else if (mode == 1 && board[temp_id] == color) {
                mode++;
                is_reverse = 1;        
            } else if (board[temp_id] == ' ')
                break;
            else if (mode == 0 && board[temp_id] == color)
                break;
        }
        if (is_reverse) {
            sum++;
            continue;
        }
    }
    return sum;
}

//put disc on board
void move(int index, char color)
{
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
        else if (mode == 0 && board[temp_id] == color)
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
        else if (mode == 0 && board[temp_id] == color)
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
        else if (mode == 0 && board[temp_id] == color)
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
        else if (mode == 0 && board[temp_id] == color)
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
        else if (mode == 0 && board[temp_id] == color)
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
        else if (mode == 0 && board[temp_id] == color)
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
        else if (mode == 0 && board[temp_id] == color)
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
        else if (mode == 0 && board[temp_id] == color)
            break;
    }
    for (i = temp_id - 9; mode == 2 && i > index; i -= 9)
        board[i] = color;

    if (is_reverse) {
        board[index] = color;
        if (!turn)
            history[2 * (black_score + white_score - 4)] = (index % 8) + 'A';
        else
            history[2 * (black_score + white_score - 4)] = (index % 8) + 'a';
        history[2 * (black_score + white_score - 4) + 1] = index / 8 + 49;    
        black_mobility = count_mobility('x');
        white_mobility = count_mobility('o');
        if (!black_mobility && !white_mobility) {
            is_gameover = 1;
        } else if (turn == 0 && white_mobility) {
            turn = 1;
        } else if (turn == 1 && black_mobility) {
            turn = 0;
        }
    }
}


