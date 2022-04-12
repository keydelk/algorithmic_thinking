/* =========================================================
                    Baby Names

    Given N distinct baby name suggestions (each babyName 
    string consists of only UPPERCASE alphabet characters of 
    no more than 30 characters) and the genderSuitability of 
    that name (integer 1 for male or integer 2 for female) 
    and given Q queries, tell Kattis how many baby names 
    start with a prefix that is inside a given query interval 
    [start…end), where start<end, and both are strings.

    There will be 4 types of commands:
Stop: This will be indicated by a 0. Stop your program upon 
    encountering this.
Add Suggestion: This will be indicated by a starting integer 
    1 followed by a string babyName and an integer 
    genderSuitability, e.g. 1 SIMBA 1.
Remove Suggestion: This will be indicated by a starting integer 
    2 followed by a string: babyName, e.g. 2 SIMBA. The babyName 
    is guaranteed to have already been suggested earlier.
Query: This will be indicated by a starting integer 3 followed 
       by two strings: start, end, and an integer genderSuitability. 
       Your job is to return the number of names that is inside the 
       interval [start…end) subject to the following criteria.
    If genderSuitability = 0: report number of names for both genders
    If genderSuitability = 1: report number of male names
    If genderSuitability = 2: report number of female names

Input: Each line will be a certain command. The program terminates 
       when it encounters 0. There are up to 200000 babyName 
       suggestions and Q is up to 500000.

Output: Each time the Query command is encountered, the number of 
        suitable names should be printed.
        
==========================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STOP              '0'
#define ADD_SUGGESTION    '1'
#define REMOVE_SUGGESTION '2'
#define QUERY             '3'
#define MAX_NAMES         200000
#define MAX_QUERIES       500000
#define SIZE              16
#define INDEX_ADJ         65

typedef struct name_node {
    char *name;
    int gender;
    struct name_node *next;
} name_node;

char *read_name(int size);
void add_name(name_node *node, name_node *list[], int total);

int main(){
    static name_node *name_list[MAX_NAMES] = {NULL};
    name_node *node;
    char command, temp;
    int total = 0;

    while ((command = getchar()) != EOF) {
        temp = getchar();
        switch (command) {
            case STOP:
                return EXIT_SUCCESS;
            case ADD_SUGGESTION:
                node = malloc(sizeof(name_node));
                if (node == NULL){
                    fprintf(stderr, "malloc error\n");
                    exit(1);
                }
                node->name = read_name(SIZE);
                node->gender = getchar() - '0';
                temp = getchar();
                printf("You entered Add Suggestion with name: %s with a gender of %d\n", node->name, node->gender);
                printf("The index of the name is %d\n", (int)(node->name[0]) - INDEX_ADJ);
                //add_name(node, name_list, total);
                break;
            case REMOVE_SUGGESTION:
                printf("You entered Remove Suggestion\n");
                break;
            case QUERY:
                printf("You entered Query\n");
                break;
            default:
                fprintf(stderr, "Invalid command: %c\n", command);
                return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

char *read_name(int size) {
    char *str;
    int ch;
    int len = 0;
    str = malloc(size);
    if (str == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(1);
    }
    while ((ch = getchar()) != EOF && (ch != '\n') && (ch != ' ')) {
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

void add_name(name_node *node, name_node *list[], int total) {
    int i;
    for (i = 0; i < total; i++) {

    }
}