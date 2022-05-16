/*=============================================================================
                                   Tic-Tac-Toe

This is a simple console tic-tac-toe game I'm doing to practice coding in C.

=============================================================================*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void print_board(char board[9]);
int get_player_move(char board[9]);
int is_win(char board[9]);
int cpu_move(char board[9]);

int main()
{
    int i, mov;
    char board[9];
    for (i = 0; i < 9; i++)
        board[i] = '0' + i;
    srand(time(NULL));

    /* Clear the screen */
    printf("\e[1;1H\e[2J");
    printf("Here is the starting board. Indicate your move by typing the number of the space. \n");
    print_board(board);
    
    for (i = 0; i < 5; i++) {
        mov = get_player_move(board);
        board[mov] = 'X';
        
        printf("\e[1;1H\e[2JCurrent Board:\n");
        print_board(board);
        if (is_win(board)) {
            printf("You win!\n");
            return EXIT_SUCCESS;
        }
        
        if (i < 4) {
            printf("CPU's turn...\n");
            sleep(2);
            mov = cpu_move(board);
            board[mov] = 'O';
            printf("\e[1;1H\e[2JCurrent Board:\n");
            print_board(board);
            if (is_win(board)) {
                printf("CPU wins!\n");
                return EXIT_SUCCESS;
            }
        }
    }   

    printf("Cat's Game\n");
    return EXIT_SUCCESS;
}

void print_board(char board[9])
{
    int i;
    for (i = 0; i < 9; i += 3)
    {
        printf("%c┃%c┃%c\n", board[i], board[i + 1], board[i + 2]);
        if (i < 5)
            printf("━╋━╋━\n");
    }
    return;
}

int get_player_move(char board[9])
{
    int mov;
    while (1)
    {
        printf("Your move: ");
        scanf("%d", &mov);
        if (mov >= 0 && mov < 9 && board[mov] != 'X' && board[mov] != 'O')
            return mov;
        else
            printf("Invalid input, try again. \n");
    }
}

int is_win(char board[9])
{
    if ((board[0] == board[1] && board[1] == board[2]) ||
        (board[3] == board[4] && board[4] == board[5]) ||
        (board[6] == board[7] && board[7] == board[8]) ||
        (board[0] == board[3] && board[3] == board[6]) ||
        (board[1] == board[4] && board[4] == board[7]) ||
        (board[2] == board[5] && board[5] == board[8]) ||
        (board[0] == board[4] && board[4] == board[8]) ||
        (board[6] == board[4] && board[4] == board[2]))
            return 1;
    return 0;
}

int cpu_move(char board[9])
{
    int i, r;
    char hypo_board[9];
    for (i = 0; i < 9; i++)
        hypo_board[i] = board[i];
    
    /* Check each space, if moving there is a win, move there */    
    for (i = 0; i < 9; i++) {
        if (board[i] == 'X' || board[i] == 'O')
            continue;
        hypo_board[i] = 'O';
        if (is_win(hypo_board))
            return i;
        hypo_board[i] = '0' + i;
    }
    
    /* Check each space, if the opponent would win there, move there */
    for (i = 0; i < 9; i++) {
        if (board[i] == 'X' || board[i] == 'O')
            continue;
        hypo_board[i] = 'X';
        if (is_win(hypo_board))
            return i;
        hypo_board[i] = '0' + i;
    }
    
    /* Take the middle if it's free */
    if (board[4] == '4')
        return 4;
    
    /* Otherwise, just take a random free space */
    r = rand() % 9;
    while (1) {
        if (board[r] == '0' + r)
            return r;
        r = (r + 1) % 9;
    }
}
