/*==============================================================================
 *                              Hockey Rivalry
 * 
 * URL: https://dmoj.ca/problem/cco18p1
 * 
 * Every hockey team played N N games this season. Each game was between two 
 * teams and the team that scored more points won. No game ended in a tie.
 * The Geese recorded the outcomes of all their games as a string S.
 * S[i] = W if the Geese won their i-th game, otherwise S[i] = L if they lost.
 * Their score for each game is recorded as A[i] for the i-th game.
 * The Hawks did used strint T, with T[j] = W if the Hawks won their j-th game.
 * Their score is recorded as B[j] for their points in their j-th game.
 * Which team each faced is not recorded.
 * A rivalry game is one where the Geese and the Hawks played each other.
 * The task is to determine the maximum possible points scored by BOTH teams
 * in ALL rivalry games for the season (all games recorded).
 * 
 * Input:   The first line contains one integer N indicating the number of games
 *               that each team played. N is between 1 nd 1 000 000.
 *          The second line contains a string S of N characters 'W' or 'L'
 *          The third line contains N integers A[1]...A[n] from 1 to 1 000 000
 *          The fourth line contains a string T of N characters 'W' or 'L'
 *          The fifth line contains N integers B[1]...B[n] from 1 to 1 000 000
 *          For 10 of the 25 available marks, N <= 10.
 * 
 * Output:  Print one line with one integer, the maximum possible sum of points
 *          scored in potential rivalry games.
 * 
 * This is the solution from the Algorithmic Thinking book.
 * ===========================================================================*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int max(int a, int b);
int solve(char outcome1[], char outcome2[], int goals1[],
            int goals2[], int i, int j);
            
int main()
{
	return EXIT_SUCCESS;
}

int max(int a, int b)
{
	if (a > b)
	    return a;
	return b;
}

int solve(char outcome1[], char outcome2[], int goals1[],
            int goals2[], int i, int j)
{
	int first, second, third, fourth;
