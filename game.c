#include "game.h"

void init_board()
{
    black_num = 0;
    white_num = 0;
    memset(board, sizeof(board), 0);
    gameover = 0;
    board[3][3] = 2;
    board[4][4] = 2;
    board[3][4] = 1;
    board[4][3] = 1;
    turn = 1;
}

void print_board()
{
    int i, j, tmp;
    black_num = 0;
    white_num = 0;
    for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++) {
            if (board[i][j] == 1)
                black_num++;
            else if (board[i][j] == 2)
                white_num++;
        }
    printf("\033[H\033[J");
    printf("Black : %d vs %d White\n\n", black_num, white_num);
    printf("   1 2 3 4 5 6 7 8\n");
    printf("  -----------------\n");
    for (i = 0; i < 8; i++) {
        printf("%c |", i + 97);
        for (j = 0; j < 8; j++) {
            tmp = board[i][j];
            if (!tmp)
                printf(" |");
            else if (tmp == -1)
                printf("*|");
            else if (tmp == 1)
                printf("X|");
            else
                printf("O|");
        }
        printf("\n");
    }
    printf("  -----------------\n\n");
    
}

int move_pos()
{
    int i, j, x, y;
    int result = 0;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if (board[i][j] <= 0) {
                for (x = i - 1; x >= -1 && (board[x][j] + turn) == 3; x--);
                if (x < i - 1 && x > -1 && board[x][j] == turn) {
                    board[i][j] = -1;
                    result++;
                    continue;
                }
                
                for (x = i + 1; x <= 8 && (board[x][j] + turn) == 3; x++);
                if (x > i + 1 && x < 8 && board[x][j] == turn) {
                    board[i][j] = -1;
                    result++;
                    continue;
                }

                for (y = j - 1; y >= -1 && (board[i][y] + turn) == 3; y--);
                if (y < j - 1 && y > -1 && board[i][y] == turn) {
                    board[i][j] = -1;
                    result++;
                    continue;
                }

                for (y = j + 1; y <= 8 && (board[i][y] + turn) == 3; y++);
                if (y > j + 1 && y < 8 && board[i][y] == turn) {
                    board[i][j] = -1;
                    result++;
                    continue;
                }

                for (x = i - 1, y = j - 1; x >= -1 && y >= -1 && (board[x][y] + turn) == 3; x--, y--);
                if (x < i - 1 && x > -1 && y < j - 1 && y > -1 && board[x][y] == turn) { 
                    board[i][j] = -1;
                    result++;
                    continue;
                }

                for (x = i - 1, y = j + 1; x >= -1 && y <= 8 && (board[x][y] + turn) == 3; x--, y++);
                if (x < i - 1 && x > -1 && y > j + 1 && y < 8 && board[x][y] == turn) { 
                    board[i][j] = -1;
                    result++;
                    continue;
                }

                for (x = i + 1, y = j - 1; x <= 8 && y >= -1 && (board[x][y] + turn) == 3; x++, y--);
                if (x > i + 1 && x < 8 && y < j - 1 && y > -1 && board[x][y] == turn) { 
                    board[i][j] = -1;
                    result++;
                    continue;
                }

                for (x = i + 1, y = j + 1; x <= 8 && y <= 8 && (board[x][y] + turn) == 3; x++, y++);
                if (x > i + 1 && x < 8 && y > j + 1 && y < 8 && board[x][y] == turn) { 
                    board[i][j] = -1;
                    result++;
                    continue;
                }



                board[i][j] = 0;
            }
        }
    }
    return result;
}

void reverse(int i, int j)
{
    int x, y;

    for (x = i - 1; x >= -1 && (board[x][j] + turn) == 3; x--);
    if (x < i - 1 && x > -1 && board[x][j] == turn) {
        for (; x < i; x++)
            board[x][j] = turn;
    }

    for (x = i + 1; x <= 8 && (board[x][j] + turn) == 3; x++);
    if (x > i + 1 && x < 8 && board[x][j] == turn) {
        for (; x > i; x--)
            board[x][j] = turn;
    }

    for (y = j - 1; y >= -1 && (board[i][y] + turn) == 3; y--);
    if (y < j - 1 && y > -1 && board[i][y] == turn) {
        for (; y < j; y++)
            board[i][y] = turn;
    }

    for (y = j + 1; y <= 8 && (board[i][y] + turn) == 3; y++);
    if (y > j + 1 && y < 8 && board[i][y] == turn) {
        for (; y > j; y--)
            board[i][y] = turn;
    }

    for (x = i - 1, y = j - 1; x >= -1 && y >= -1 && (board[x][y] + turn) == 3; x--, y--);
    if (x < i - 1 && x > -1 && y < j - 1 && y > -1 && board[x][y] == turn) { 
        for (; x < i && y < j; x++, y++)
            board[x][y] = turn;
    }

    for (x = i - 1, y = j + 1; x >= -1 && y <= 8 && (board[x][y] + turn) == 3; x--, y++);
    if (x < i - 1 && x > -1 && y > j + 1 && y < 8 && board[x][y] == turn) { 
        for (; x < i && y > j; x++, y--)
            board[x][y] = turn;
    }

    for (x = i + 1, y = j - 1; x <= 8 && y >= -1 && (board[x][y] + turn) == 3; x++, y--);
    if (x > i + 1 && x < 8 && y < j - 1 && y > -1 && board[x][y] == turn) {
        for (; x > i && y < j; x--, y++)
            board[x][y] = turn;

    }

    for (x = i + 1, y = j + 1; x <= 8 && y <= 8 && (board[x][y] + turn) == 3; x++, y++);
    if (x > i + 1 && x < 8 && y > j + 1 && y < 8 && board[x][y] == turn) {
        for (; x > i && y > j; x--, y--)
            board[x][y] = turn;
    }
}

void next_move()
{
    if (turn == 1)
        printf("It's Black's turn!\nmove : ");
    else
        printf("It's White's turn!\nmove : ");
    
    char c;
    int i, j;
    
    while (1) {
        getchar();
        scanf("%c%d", &c, &j);
        i = c-'a';
        j--;
        if (i >= 0 && i < 8 && j >= 0 && j < 8 && board[i][j] == -1) {
            break;
        }
        else {
            printf("wrong position!\n");
            printf("move : ");
        }
    }
    board[i][j] = turn;
    reverse(i, j);
    turn = 3 - turn;
}

void start_game()
{
    init_board();
    while (!gameover) {
        if (!move_pos()) {
            turn = 3 - turn;
            continue;
        }       
        print_board();
        next_move();
    }
}






