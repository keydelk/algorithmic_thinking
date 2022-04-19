/*=============================================================================
                               Ways To Pass

URL: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=21&page=show_problem&problem=1851
UVa problem ID: 10910

Passing a course requires at least p marks. (p isn’t necessarily 50 or 60 or 
whatever is needed in school; it could be any positive integer.) A student took 
n courses and passed them all.
Adding up all of the student’s marks in these n courses gives a total of t 
marks that the student earned, but we don’t know how many marks the student 
earned in each course. So we ask the following: in how many distinct ways could 
the student have passed all of the courses?
For example, suppose that the student took two courses and earned a total of 
nine marks and that each course requires at least three marks to pass. Then, 
there are four ways in which the student could have passed these courses:
    - three marks in course 1 and six marks in course 2
    - four marks in course 1 and five marks in course 2
    - five marks in course 1 and four marks in course 2
    - six marks in course 1 and three marks in course 2

Input:  The first line of input is an integer k indicating the number of test 
        cases to follow. Each of the k test cases is on its own line and 
        consists of three integers: n (the number of courses taken, all of 
        which the student passed), t (total marks earned), and p (marks needed 
        to pass each course). Each n, t, and p value is between 1 and 70.

Output: For each test case, output the number of ways that the marks can be 
        distributed so that the student passes all courses. For the above 
        example, the output would be the integer 4 .

=============================================================================*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SIZE 70

int solve(int p, int n, int t, int memo[SIZE +1][SIZE + 1]);

int main()
{
    return EXIT_SUCCESS;
}

int solve(int p, int n, int t, int memo[SIZE + 1][SIZE + 1])
{
    int total, m;
    if (memo[n][t] != -1)
        return memo[n][t];
    if (n == 0 && t == 0)
    {
        memo[n][t] = 0;
        return memo[n][t];
    }
    if (n == 0 || t == 0)
    {
        memo[n][t] = 0;
        return memo[n][t];
    }
    total = 0;
    for (m = p; m <=t; m++)
        total = total + solve(n - 1, t - m, p, memo);
    memo[n][t] = total;
    return memo[n][t];
}