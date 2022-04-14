/*================================================================================================================
                                            Burger Fervor Memoization

URL: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=16&page=show_problem&problem=1406

Homer has t minutes that he’ll spend eating burgers and drinking beer. There are two kinds of burgers. One of 
them takes m minutes to eat, and the other takes n minutes to eat. Homer likes burgers more than beer, so he’d 
like to spend the entire t minutes eating burgers. However, doing so isn’t always possible. If that’s the case, 
he’ll spend as much time as possible eating burgers and then fill the rest of the time drinking beer. Our task is 
to determine the maximum number of burgers that Homer can eat, while spending as little time possible drinking.

Input:  We read test cases until there is no more input. Each test case is represented by a line of three 
        integers: m, the number of minutes it takes to eat the first kind of burger; n, the number of minutes it 
        takes to eat the second kind of burger; and t, the number of minutes that Homer will spend eating burgers 
        and drinking beer. Each m, n, and t value is less than 10,000.

Output: For each test case:
            * If Homer can spend exactly t minutes eating burgers, then output the maximum number of burgers that 
                he can eat.
            * Otherwise, output the maximum number of burgers that Homer can eat when maximizing his time eating 
                burgers, a space, and the number of remaining minutes (during which he’ll drink beer).
        The time limit for solving the cases is 3 seconds.

This is the memoization solution from "Algorithmic Thinking: A Problem Based Introduction" by Daniel Zingaro
================================================================================================================*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 10000
unsigned long long total_calls;

int solve_t(int m, int n, int t, int memo[]);
int max(int a, int b);
void solve(int m, int n, int t);

int main() {
    int m, n, t;
    while (scanf("%d %d %d", &m, &n, &t) != -1)
        solve(m, n, t);
    return EXIT_SUCCESS;
}

int solve_t(int m, int n, int t, int memo[]) {
    int first, second;
    total_calls++;
    if (memo[t] != -2)
        return memo[t];
    if (t == 0) {
        memo[t] = 0;
        return memo[t];
    }
    if (t >= m)
        first = solve_t(m, n, t-m, memo);
    else
        first = -1;
    if (t >= n)
        second = solve_t(m, n, t-n, memo);
    else
        second = -1;
    if (first == -1 && second == -1) {
        memo[t] = -1;
        return memo[t];
    }
    memo[t] = max(first, second) + 1;
    return memo[t];
}

int max(int a, int b) {
    if (a > b)
        return a;
    return b;
}

void solve(int m, int n, int t) {
    int result, i;
    int memo[MAX];
    for (i = 0; i <=t; i++)
        memo[i] = -2;
    total_calls = 0;
    result = solve_t(m, n, t, memo);
    if (result >= 0) {
        printf("%d\n", result);
    } else {
        i = t-1;
        result = solve_t(m, n, i, memo);
        while (result == -1) {
            i--;
            result = solve_t(m, n, i, memo);
        }
        printf("%d %d\n", result, t - i);
    }
    printf("Total calls to solve_t: %llu\n", total_calls);
    return;
}