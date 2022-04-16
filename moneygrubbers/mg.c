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

This is the memoization solution from Algorithmic Thinking
Trying Allman style braces for this problem rather than the Kernel style.
=============================================================================*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_PRICING_SCHEMES 20
#define SIZE 201

double min(double a, double b);

double solve_k(int num[], double price[], int num_schemes, 
                    double unit_price, int num_items, double memo[]);
double solve(int num[], double price[], int num_schemes,
                    double unit_price, int num_items, double memo[]);
int get_number(int *num);
long long unsigned int num_calls;

int main()
{
    int test_case, num_schemes, num_items, more, i;
    double unit_price, result;
    int num[MAX_PRICING_SCHEMES];
    double price[MAX_PRICING_SCHEMES];
    double memo[SIZE];
    test_case = 0;

    while (scanf("%lf %d", &unit_price, &num_schemes) == 2)
    {
        test_case++;
        for (i = 0; i < SIZE; i++)
            memo[i] = -1;
        for (i = 0; i < num_schemes; i++)
            scanf("%d %lf", &num[i], &price[i]);
        scanf(" ");
        printf("Case %d:\n", test_case);
        more = get_number(&num_items);
        while (more)
        {
			result = solve(num, price, num_schemes, unit_price,
			                num_items, memo);
			printf("Buy %d for $%.2f\n", num_items, result);
			more = get_number(&num_items);
		}
		result = solve(num, price, num_schemes, unit_price,
		                num_items, memo);
		printf("Buy %d for $%.2f\n", num_items, result);
    }
    
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
                    double unit_price, int num_items, double memo[])
{
    double best, result;
    int i;

    if (memo[num_items] != -1)
        return memo[num_items];
    if (num_items == 0)
    {
		memo[num_items] = 0;
        return memo[num_items];
	}
    else
    {
        result = solve_k(num, price, num_schemes,
                            unit_price, num_items - 1, memo);
        best = result + unit_price;

        for (i = 0; i < num_schemes; i++)
            if (num_items - num[i] >= 0)
            {
                result = solve_k(num, price, num_schemes, 
                                 unit_price, num_items - num[i], memo);
                best = min(best, result + price[i]);
            }
        memo[num_items] = best;
        return memo[num_items];
    }
}

double solve(int num[], double price[], int num_schemes,
                double unit_price, int num_items, double memo[])
{
    double best;
    int i;
    int largest_scheme = 0;
    for (i = 0; i < num_schemes; i++)
        if (num[i] > largest_scheme)
            largest_scheme = num[i];
    
    best = solve_k(num, price, num_schemes, unit_price, 
                   num_items, memo);
    for (i = num_items + 1; i <= num_items + largest_scheme; i++)
        {
			best = min(best, solve_k(num, price, num_schemes, 
                                 unit_price, i, memo));
		}
    return best;
}

int get_number(int *num)
{
	int ch;
	int ret = 0;
	ch = getchar();
	while (ch != ' ' && ch != '\n')
	{
		ret = ret * 10 + ch - '0';
		ch = getchar();
	}
	*num = ret;
	return (ch == ' '); 
}
