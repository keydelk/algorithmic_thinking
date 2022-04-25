/* The Square and Multiply Algorithm
Youtube: https://youtu.be/cbGB__V8MNk
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static long int num_calls = 0;

long int exponentiation(long int base, long int exp, long int mod)
{
    num_calls++;
    if (exp == 0)
        return 1;
    if (exp == 1)
        return base % mod;
    
    long int t = exponentiation(base, exp / 2, mod);
    t = (t * t) % mod;

    if (exp % 2 == 0)
        return t;
    else
        return (t * (base % mod)) % mod;
}

int main()
{
    long int x;
    x = exponentiation(23, 373, 747);
    printf("Answer: %ld\n", x);
    printf("Number of calls: %ld\n", num_calls);
    return EXIT_SUCCESS;
}