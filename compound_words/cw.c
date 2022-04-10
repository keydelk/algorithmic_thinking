/* =====================================================
                    Compound Words

    Given a wordlist in which each word is a lowercase
    string. The task is to determine the strings in the
    list that are compound words: the concatenation of
    exactly two other strings in the list.

Input: one string (word) per line in alphabetical order.
       Max 120,000 strings.

Output: each compound word, one per line, in alphabetical
        order.
=======================================================*/

#import <stdio.h>
#import <stdlib.h>
#import <string.h>

#define WORD_LENGTH 16
#define NUM_BITS 17

typedef struct word_node {
    char **word;
    struct word_node *next;
} word_node;

char *read_line(int size);

int main() {

    return EXIT_SUCCESS;
}

char *read_line(int size) {
    char *str;
    int ch;
    int len = 0;
    str = malloc(size);
    if (str == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(1);
    }
    while ((ch = getchar()) != EOF && (ch != '\n')) {
        str[len++] = ch;
        if (len == size) {
            size = size * 2;
            str = realloc(str, size);
            if (str == NULL) {
                fprintf(stderr, "realloc error\n");
                exit(1);
            }
        }
    }
    str[len] = '\0';
    return str;
}

