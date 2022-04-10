/* snowflakes.c
For the DMOJ problem cco07p2
https://dmoj.ca/problem/cco07p2

We’re given a collection of snowflakes, and we have to determine whether any of the snowflakes in the collection are identical.
A snowflake is represented by six integers, where each integer gives the length of one of the snowflake’s arms.
Snowflakes can also have repeated integers.
Two snowflakes are identical if they are the same, if we can make them the same by moving rightward through one of the snowflakes, 
or if we can make them the same by moving leftward through one of the snowflakes.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NO_IDENTICAL_SNOWFLAKES "No two snowflakes are alike.\n"
#define IDENTICAL_SNOWFLAKES_FOUND "Twin snowflakes found.\n"
#define SIZE 100000

typedef struct snowflake_node {
    int snowflake[6];
    struct snowflake_node *next;
} snowflake_node;

int identical_right(int snow1[], int snow2[], int start);
int identical_left(int snow1[], int snow2[], int start);
int are_identical(int snow1[], int snow2[]);
void identify_identical(snowflake_node *snowflakes[]);
int code(int snowflake[6]);

int main(){
    static snowflake_node *snowflakes[SIZE] = {NULL};
    snowflake_node *snow;
    int n, snowflake_code;

    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        snow = malloc(sizeof(snowflake_node));
        if (snow == NULL) {
            fprintf(stderr, "malloc error\n");
            exit(1);
        }
        for(int j = 0; j < 6; j++)
            scanf("%d", &snow -> snowflake[j]);
        snowflake_code = code(snow -> snowflake);
        snow -> next = snowflakes[snowflake_code];
        snowflakes[snowflake_code] = snow;
    }
    
    identify_identical(snowflakes);

    // free memory
    for(int i = 0; i < n; i++){
        snow = snowflakes[i];
        while (snow != NULL){
            snowflakes[i] = snow -> next;
            free(snow);
            snow = snowflakes[i];
        }
    }

    return EXIT_SUCCESS;
}

int identical_right(int snow1[], int snow2[], int start){
    for(int i = 0; i < 6; i++){
        if(snow1[i] != snow2[(start + i) % 6]){
            return 0;
        }
    }
    return 1;
}

int identical_left(int snow1[], int snow2[], int start){
    for(int i = 0; i < 6; i++){
        if(snow1[i] != snow2[(start + 6 - i) % 6]){
            return 0;
        }
    }
    return 1;
}

int are_identical(int snow1[], int snow2[]){
    for(int i = 0; i < 6; i++){
        if(identical_right(snow1, snow2, i)){
            return 1;
        }
        if(identical_left(snow1, snow2, i)){
            return 1;
        }
    }
    return 0;
}

void identify_identical(snowflake_node *snowflakes[]){
    snowflake_node *node1, *node2;

    for(int i = 0; i < SIZE; i++){
        node1 = snowflakes[i];
        while (node1 != NULL) {
            node2 = node1 -> next;
            while (node2 != NULL) {
                if (are_identical(node1 -> snowflake, node2 -> snowflake)) {
                    printf(IDENTICAL_SNOWFLAKES_FOUND);
                    return;
                }
                node2 = node2 -> next;
            }
            node1 = node1 -> next;
        }
    }
    printf(NO_IDENTICAL_SNOWFLAKES);
    return;
}

int code(int snowflake[6]){
    return (snowflake[0] + snowflake[1] + snowflake[2] + snowflake[3] + snowflake[4] + snowflake[5]) % SIZE;
}