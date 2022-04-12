/* =======================================================
         Spelling Check: Deleting a Letter

    Given two strings where the first string has one more
    character than the second. Our task is to determine
    the number of ways in which one character can be
    deleted from the first string to arrive at the second.

Input: two lines, with the first string on the first line
       and the second string on the second line.
       Each string is up to one-million characters

Output: If there is no way to remove a string from the
        first line to get the second, output 0. Otherwise,
        output 2 lines:
        1st line: number of ways to delete a letter from
        the first line to get the second.
        2nd line: space separated list of the indicies of
        the characters in the first string that can be 
        removed to get the second string.
========================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1000002

void find_difference(char *line1, char *line2);

int main(){
    static char line1[MAX_LEN], line2[MAX_LEN];

    if (fgets(line1, MAX_LEN, stdin) == NULL){
        fprintf(stderr, "fgets error\n");
        return EXIT_FAILURE;
    }
    
    if (fgets(line2, MAX_LEN, stdin) == NULL){
        fprintf(stderr, "fgets error\n");
        return EXIT_FAILURE;
    }

    find_difference(line1, line2);


    return EXIT_SUCCESS;
}

void find_difference(char *line1, char *line2) {
    int i, j, len, repeats = 0;
    len = strlen(line1);

    for (i = 0; i < len; i++) {
        if ((i == 0) || (line1[i] != line1[i - 1])){
            repeats = 0;
        } else {
            repeats++;
        }
        if (line1[i] != line2[i]) {
            if (strncmp(line1 + i + 1, line2 + i, len - i - 2) != 0){
                printf("0\n");
                return;
            }
            printf("%d\n", repeats + 1);
            for (j = 0; j <= repeats; j++){
                printf("%d ", i + 1 - repeats + j);
            }
            printf("\n");
            return;
        }
    }
    printf("0\n");
    return;
}