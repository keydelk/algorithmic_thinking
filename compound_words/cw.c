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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define hashsize(n) ((unsigned long)1 << (n))
#define hashmask(n) (hashsize(n) - 1);
#define WORD_LENGTH 16
#define NUM_BITS 17

typedef struct word_node {
    char **word;
    struct word_node *next;
} word_node;

char *read_line(int size);
unsigned long oaat(char *key, unsigned long len, unsigned long bits);
int in_hash_table(word_node *hash_table[], char *find, unsigned find_len);
void indentify_compound_words(char *words[], word_node *hash_table[], int total_words);

int main() {
    static char *words[1 << NUM_BITS] = {NULL};
    static word_node *hash_table[1 << NUM_BITS] = {NULL};
    int i, total = 0;
    char *word;
    word_node *wordptr;
    unsigned length, word_code;

    do {
        word = read_line(WORD_LENGTH);
        words[total] = word;
        wordptr = malloc(sizeof(word_node));
        if (wordptr == NULL){
            fprintf(stderr, "malloc error\n");
            exit(1);
        }
        length = strlen(word);
        word_code = oaat(word, length, NUM_BITS);
        wordptr->word = &words[total];
        wordptr->next = hash_table[word_code];
        hash_table[word_code] = wordptr;
        total++;
    } while(*word);

    indentify_compound_words(words, hash_table, total);

    for(i = 0; i < total; i++) {
        free(words[i]);
    }

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

unsigned long oaat(char *key, unsigned long len, unsigned long bits) {
    unsigned long hash, i;

    for (hash = 0, i = 0; i < len; i++) {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash & hashmask(bits);
}

int in_hash_table(word_node *hash_table[], char *find, unsigned find_len) {
    unsigned word_code;
    word_node *wordptr;
    word_code = oaat(find, find_len, NUM_BITS);
    wordptr = hash_table[word_code];

    while (wordptr) {
        if ((strlen(*(wordptr->word)) == find_len) && (strncmp(*(wordptr->word), find, find_len) == 0))
            return 1;
        wordptr = wordptr->next;
    }
    return 0;
}

void indentify_compound_words(char *words[], word_node *hash_table[], int total_words) {
    unsigned len;
    int i, j;
    for (i = 0; i < total_words; i++) {
        len = strlen(words[i]);
        for (j = 1; j < len; j++) {
            if (in_hash_table(hash_table, words[i], j) && in_hash_table(hash_table, &words[i][j], len - j)) {
                printf("%s\n", words[i]);
                break;
            }
        }
    }
}