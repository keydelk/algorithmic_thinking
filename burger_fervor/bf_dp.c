/*================================================================================================================
                                            Burger Fervor Dynamic Programming
                                            
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

This is the dynamic programming solution from "Algorithmic Thinking: A Problem Based Introduction" by Daniel Zingaro
================================================================================================================*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 10000

int max(int a, int b);
void solve(int m, int n, int t);

int main() {
    int m, n, t;
    while (scanf("%d %d %d", &m, &n, &t) != -1)
        solve(m, n, t);
    return EXIT_SUCCESS;
}

int max(int a, int b) {
    if (a > b)
        return a;
    return b;
}

void solve(int m, int n, int t) {
    int result, i, first, second;
    int dp[MAX];
    dp[0] = 0;
    for (i = 1; i <=t; i++) {
        if (i >= m)
            first = dp[i-m];
        else
            first = -1;
        if (i >= n)
            second = dp[i-n];
        else
            second = -1;
        if (first == -1 && second == -1)
            dp[i] = -1;
        else
            dp[i] = max(first, second) + 1;
    }
    result = dp[t];
    if (result >= 0) {
        printf("%d\n", result);
    } else {
        i = t-1;
        result = dp[i];
        while (result == -1) {
            i--;
            result = dp[i];
        }
        printf("%d %d\n", result, t - i);
    }
    return;
}