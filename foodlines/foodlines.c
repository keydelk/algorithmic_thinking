/*
 * ============================================================================
 *
 *       Filename:  Foodlines.c
 *
 *           Prob:  Foodlines - There are n lines of people waiting for food, 
 *                  and the number of people waiting in each line is known. Then, 
 *                  each of m new people will arrive, and they will join the 
 *                  shortest line (the line with the fewest number of people). 
 *                  Our task is to determine the number of people in each line 
 *                  that each of the m people joins.
 *
 *          Input:  The input contains one test case. The first line contains 
 *                  two positive integers, n and m, giving the number of lines 
 *                  and number of new people, respectively. n and m are at most 
 *                  100. The second line contains n positive integers, giving 
 *                  the number of people in each line before the new people arrive. 
 *                  Each of these integers is at most 100. Example:
 *                  3 4
 *                  3 2 5
 *
 *         Output:  For each of the m new people, output a line containing the 
 *                  number of people in the line that they join. Example:
 *                  2
 *                  3
 *                  3
 *                  4
 *
 *        Created:  03/24/2016 19:40:56
 *
 *         Author:  Keith Keydel
 *
 * ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_PEOPLE 200

int index_of_shortest(int* lines, int num_lines);

int main () {
    int n = 0, m = 0;
    int lines[MAX_LINES];

    scanf("%d %d", &n, &m);

    for(int i = 0; i < n; i++) {
        scanf("%d", lines + i);
    }

    for(int i = 0; i < m; i++) {
        int ind = 0, len = 0;
        ind = index_of_shortest(lines, n);
        len = lines[ind];
        printf("%d\n", len);
        lines[ind]++;
    }

    return EXIT_SUCCESS;
}

int index_of_shortest(int* lines, int num_lines){
    int index = 0, shortest = MAX_PEOPLE;
    for(int i = 0; i < num_lines; i++){
        if(lines[i] < shortest){
            shortest = lines[i];
            index = i;
        }
    }
    return index;
}