/* The "Nearly Impossible" Chess Puzzle Solver
 * YouTube Video: https://youtu.be/as7Gkm7Y7h4
 * 
 * The Board
 * "┏━━┳━━┳━━┳━━┳━━┳━━┳━━┳━━┓\n"\
 * "┃00┃01┃02┃03┃04┃05┃06┃07┃\n"\
 * "┣━━╋━━╋━━╋━━╋━━╋━━╋━━╋━━┫\n"\
 * "┃08┃09┃10┃11┃12┃13┃14┃15┃\n"\
 * "┣━━╋━━╋━━╋━━╋━━╋━━╋━━╋━━┫\n"\
 * "┃16┃17┃18┃19┃20┃21┃22┃23┃\n"\
 * "┣━━╋━━╋━━╋━━╋━━╋━━╋━━╋━━┫\n"\
 * "┃24┃25┃26┃27┃28┃29┃30┃31┃\n"\
 * "┣━━╋━━╋━━╋━━╋━━╋━━╋━━╋━━┫\n"\
 * "┃32┃33┃34┃35┃36┃37┃38┃39┃\n"\
 * "┣━━╋━━╋━━╋━━╋━━╋━━╋━━╋━━┫\n"\
 * "┃40┃41┃42┃43┃44┃45┃46┃47┃\n"\
 * "┣━━╋━━╋━━╋━━╋━━╋━━╋━━╋━━┫\n"\
 * "┃48┃09┃10┃11┃12┃13┃14┃15┃\n"\
 * "┣━━╋━━╋━━╋━━╋━━╋━━╋━━╋━━┫\n"\
 * "┃08┃09┃10┃11┃12┃13┃14┃15┃\n"\
 * "┗━━┻━━┻━━┻━━┻━━┻━━┻━━┻━━┛\n"\
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#define TOP_ROW    "┏━━┳━━┳━━┳━━┳━━┳━━┳━━┳━━┓\n"
#define SEPARATOR  "┣━━╋━━╋━━╋━━╋━━╋━━╋━━╋━━┫\n"
#define BOTTOM_ROW "┗━━┻━━┻━━┻━━┻━━┻━━┻━━┻━━┛\n"

void print_board(int board[64]) {
	int i;
	
	printf(TOP_ROW);
	for (i = 0; i < 64; i++) {
		if (board[i] == 1)
			printf("┃🪙 ");
		else
		    printf("┃%2d", i);
		
		if (i % 8 == 7) {
			printf("┃\n");
			if (i < 63)
			    printf(SEPARATOR);
		}
	}
	printf(BOTTOM_ROW);
}
    

int main() {
	int board[64];
	int i;
	
	for (i = 0; i < 64; i++)
	    board[i] = 0;
	
	board[51] = 1;
	    
	print_board(board);
	return EXIT_SUCCESS;
}
