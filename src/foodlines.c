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

int main () {
    int n = 0, m = 0;
    int lines[100];
    int people[100];

    scanf("%d %d", &n, &m);

    for(int i = 0; i < n; i++) {
        scanf("%d", lines + i);
    }

//Debugging info
    printf("There are %d lines and %d people want to join.\n", n, m);

    printf("Lines: ");
    for(int i=0; i < n; i++) {
        printf("%d ", lines[i]);
    }
    printf("\n");

// for each person in m determine what line they will be in and write that to people[m]
    for(int i = 0; i < m; i++){
        //which line is the shortest
        int numPeople = 201; //max number of people in a line is 200, this is one greater so it is always replaced
        int linenum = 101; //max number of lines is 100
        for(int j = 0; j < n; j++){
            if (lines[j] < numPeople){
                numPeople = lines[j];
                linenum = j;
            }
        }
        //now line #linenum has the number of the shortest line with numPeople people
        //person i joins the line with #numPeople in front of them
        people[i] = numPeople;
        //and that line gets longer
        lines[linenum]++;
    }

    //print the output
    for(int i = 0; i < m; i++){
        printf("%d\n", people[i]);
    }

    return EXIT_SUCCESS;
}