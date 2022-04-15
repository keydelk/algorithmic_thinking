/*=============================================================================
                               Moneygrubbers

URL: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=21&page=show_problem&problem=1921

The store has a price for buying one apple—for example, $ 1.75. The store also 
has m pricing schemes, where each pricing scheme gives a number n and a price 
p for buying n apples. For example, one pricing scheme might state that three 
apples cost a total of $ 4.00; another might state that two apples cost a total 
of $ 2.50. You want to buy at least k apples and to do so as cheaply as possible.

Input:  Read test cases until there's no more input. Each test case consists of
        the following lines:
            - A line containing the price for one apple, followed by the number
                m of pricing schemes for this test case. m is at most 20.
            - m lines, each of which gives a number n and a total price p for 
                buying n apples. n is between 1 and 100.
            - A line containing integers, where each integer k is between 0 and
                100 and gives the desired number of apples to buy.
        Each price is a floating-point number with exactly two decimal digits.

Output: For each test case, output the following:
            - A line containing "Case: c:" where c is the test case number
                starting at 1.
            - For each integer k, a line containing "Buy k for $ d" where d is 
                the cheapest way we can buy at least k apples.

This is the recursion solution from Algorithmic Thinking
Trying Allman style braces for this problem rather than the Kernel style.
=============================================================================*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_PRICING_SCHEMES 20

double min(double a, double b);

double solve_k(int num[], double price[], int num_schemes, 
                    double unit_price, int num_items);
double solve(int num[], double price[], int num_schemes,
                    double unit_price, int num_items);

int main()
{
    return EXIT_SUCCESS;
}

double min(double a, double b)
{
    if (a < b)
        return a;
    else
        return b;
}

double solve_k(int num[], double price[], int num_schemes,
                    double unit_price, int num_items)
{
    double best, result;
    int i;

    if (num_items == 0)
        return 0;
    else
    {
        result = solve_k(num, price, num_schemes,
                            unit_price, num_items - 1);
        best = result + unit_price;

        for (i = 0; i < num_schemes; i++)
            if (num_items - num[i] >= 0)
            {
                result = solve_k(num, price, num_schemes, 
                                   unit_price, num_items - num[i]);
                best = min(best, result + price[i]);
            }
        return best;
    }
}