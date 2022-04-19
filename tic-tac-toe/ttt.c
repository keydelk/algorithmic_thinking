/*=============================================================================
                                   Tic-Tac-Toe

This is a simple console tic-tac-toe game I'm doing to practice coding in C.

=============================================================================*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void print_board(char board[3][3]);
int get_player_move(char board[3][3]);

int main()
{
    int i, j, mov;
    char board[3][3];
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            board[i][j] = '0' + 3*i + j + 1;

    print_board(board);

    mov = get_player_move(board);
    board[mov / 3][mov % 3] = 'X';

    print_board(board);
    return EXIT_SUCCESS;
}

void print_board(char board[3][3])
{
    int i;
    for (i = 0; i < 3; i++)
    {
        printf("%c|%c|%c\n", board[i][0], board[i][1], board[i][2]);
        if (i < 2)
            printf("-+-+-\n");
    }
    return;
}

int get_player_move(char board[3][3])
{
    int mov;
    while (1)
    {
        printf("Your move: ");
        mov = getc(stdin) - '1';
        if (mov > 0 && mov < 9)
            return mov;
        else
            printf("Invalid input, try again. \n");
    }
}