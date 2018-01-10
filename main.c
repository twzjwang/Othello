#include <stdio.h>
#include "game.h"

int main()
{
    int input = 1;
    int d;
    char c;
    printf("Black : (1) Player (2) AI\n");
    //scanf("%d", &input);
    //getchar();
    if (input == 1)
        is_black_ai = 0;
    else
        is_black_ai = 1;
    printf("White : (1) Player (2) AI\n");
    //scanf("%d", &input);
    //getchar();
    if (input == 1)
        is_white_ai = 0;
    else
        is_white_ai = 1;

    init_board();

    while (!is_gameover) {
        print_board();
        if (!turn && !is_black_ai) {
            printf("Input move (e.x. 'd3') : ");
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
    print_board();
    if (black_score > white_score)
        printf("Black Win!\n");
    else if (black_score < white_score)
        printf("White Win!\n");
    else
        printf("Even!\n");
}


