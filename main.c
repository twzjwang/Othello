#include <stdio.h>
#include "game.h"

int main()
{
    int input = 1;
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
    }

}


