/*=============================================================================+
                                Knight Chase
URL: https://dmoj.ca/problem/ccc99s4

A knight an a pawn are on a board with r rows (1 to r) and c columns (1 to c).
The knight's objective is to catch the pawn (land on the pawn's square) in as 
few moves as possible. The pawn wins if it makes it to the top. If the knight
lands on the square immediately above the pawn, it is a stalemate.
The pawn moves first, and on each turn moves up one square.
The knight makes a usual knights move (change 2 columns and 1 row, or 2 rows and
one column) each turn.

Input:  The first line indicates the number of test cases. For each test case,
there are 6 lines:
            1. The number of rows on the board, between 3 and 99.
            2. The number of columns on the board, between 2 and 99.
            3. The starting row of the pawn.
            4. The starting column of the pawn.
            5. The starting row of the knight.
            6. The starting column of the knight.
        It is guaranteed that the pawn and the knight have different starting
        positions and the knight starts at a position where it has at least one
        available move.

Output: For each test case, output a line with one of three messages:
            1. If the knight can win, output: "Win in m knight move(s)."
            2. Knight can't win, but can stalemate: "Stalemate in m knight move(s)."
            3. Knight can't win or stalemate: "Loss in m knight move(s)."
        Where m is the minimum number of moves made by the knight.

Solution based on the Breadth-first search algorithm from "Algorithmic Thinking"
===============================================================================*/
#include <stdlib.h>
#include <stdio.h>

#define MAX_ROWS 99
#define MAX_COLS 99

typedef struct position {
    int row, col;
} position;

typedef int board[MAX_ROWS + 1][MAX_COLS + 1];

typedef position positions[MAX_ROWS * MAX_COLS];

int find_distance(int knight_row, int knight_col, int dest_row, int dest_col,
                    int num_rows, int num_cols);

int main() {
    return EXIT_SUCCESS;
}

int find_distance(int knight_row, int knight_col, int dest_row, int dest_col,
                    int num_rows, int num_cols) {
    positions cur_positions, new_positions;
    int num_cur_positions, num_new_positions;
    int i, j, from_row, from_col;
    board min_moves;
    
    for (i = 1; i <= num_rows; i++)
        for (j = i; j <= num_cols; j++)
            min_moves[i][j] = -1;
    
    min_moves[knight_row][knight_col] = 0;
    cur_positions[0] = (position){knight_row, knight_col};
    num_cur_positions = 1;
    
    while (num_cur_positions > 0) {
		num_new_positions = 0;
		for (i = 0; i < num_cur_positions; i++) {
			from_row = cur_positions[i].row;
			from_col = cur_positions[i].col;
			if (from_row == dest_row && from_col == dest_col)
			    return min_moves[dest_row][dest_col];
			add_position(from_row, from_col, from_row + 1, from_col + 2,
			             num_rows, num_cols, new_positions,
			             &num_new_positions, min_moves);
			add_position(from_row, from_col, from_row + 1, from_col - 2,
			             num_rows, num_cols, new_positions,
			             &num_new_positions, min_moves);
			add_position(from_row, from_col, from_row - 1, from_col + 2,
			             num_rows, num_cols, new_positions,
			             &num_new_positions, min_moves);
			add_position(from_row, from_col, from_row - 1, from_col - 2,
			             num_rows, num_cols, new_positions,
			             &num_new_positions, min_moves);
			add_position(from_row, from_col, from_row + 2, from_col + 1,
			             num_rows, num_cols, new_positions,
			             &num_new_positions, min_moves);
			add_position(from_row, from_col, from_row + 2, from_col - 1,
			             num_rows, num_cols, new_positions,
			             &num_new_positions, min_moves);
			add_position(from_row, from_col, from_row - 2, from_col + 1,
			             num_rows, num_cols, new_positions,
			             &num_new_positions, min_moves);
			add_position(from_row, from_col, from_row - 2, from_col - 1,
			             num_rows, num_cols, new_positions,
			             &num_new_positions, min_moves);
		}
		num_cur_positions = num_new_positions;
		for (i = 0; i < num_cur_positions; i++) {
			cur_positions[i] = new_positions[i];
	}
	return -1;		
}
