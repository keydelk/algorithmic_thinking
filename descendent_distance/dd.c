/*===============================================================================
                           Descendent Distance

URL: https://dmoj.ca/problem/ecna05b

Ann Sister owns a genealogical database service, which maintains family tree 
history for her clients. When clients login to the system, they are presented 
with a variety of services: searching, printing, querying, etc. One recent 
question that came up which the system was not quite prepared for was the 
following: "Which member of my family had the most grandchildren?" The client 
who posed this question eventually had to answer it by manually searching the 
family tree database herself. Ann decided to have software written in case this 
question (or ones similar to it asking for great-grandchildren, or 
great-great-grandchildren, etc.) is asked in the future.

Input: Input will consist of multiple test cases. The first line of the input 
       will contain a single integer indicating the number of test cases. Each 
       test case starts with a single line containing two positive integers n 
       and d, where n indicates the number of lines to follow containing 
       information about the family tree, and d indicates the specific question 
       being asked about the tree: if d=1, then we are interested in persons 
       with the most children (1 generation away); if d=2, then we are 
       interested in persons with the most grandchildren (2 generations away), 
       and so on. The next n lines are of the form: name m dname1, ... dnamem,
       where name is one of the family members' names, m is the number of 
       his/her children, and dname1 through dnamem are the names of the 
       children. These lines will be given in no particular order. You may 
       assume that all n lines describe one single, connected tree. There will 
       be no more than 1000 people in any one tree, and all names will be at 
       most 10 characters long.

Output: For each test case, output the three names with the largest number of 
        specified descendants in order of number of descendants. If there are 
        ties, output the names within the tie in alphabetical order. Print fewer 
        than three names if there are fewer than three people who match the 
        problem criteria (you should not print anyone's name who has 0 of the 
        specified descendants), and print more than three if there is a tie near 
        the bottom of the list. Print each name one per line, followed by a single 
        space and then the number of specified descendants. The output for each 
        test case should start with the line: "Tree i:" where i is the test case.

================================================================================*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_NAME 11
#define MAX_NODES 1000

typedef struct node { //will need a next element for hashing
    char *name;
    int num_children;
    struct node ** children;
    int score;
} node;

void *malloc_safe(int size);
node *find_node(node *nodes[], int num_nodes, char *name);
node *new_node(char *name);
int read_tree(node *nodes[], int num_lines);
int score_node(node *n, int d);
void score_all(node ** nodes, int num_nodes, int d);
int compare(const void *v1, const void *v2);
void print_scores(node *nodes[], int num_nodes);

int main() {
    int d, num_cases, num_lines, num_nodes, case_num;
    node ** nodes = malloc_safe(sizeof(node) * MAX_NODES);

    scanf("%d", &num_cases);
    for (case_num = 1; case_num <= num_cases; case_num++){
        printf("Tree %d:\n", case_num);
        scanf("%d %d", &num_lines, &d);
        num_nodes = read_tree(nodes, num_lines);
        score_all(nodes, num_nodes, d);
        qsort(nodes, num_nodes, sizeof(node*), compare);
        print_scores(nodes, num_nodes);
        if (case_num < num_cases)
            printf("\n");
    }

    return EXIT_SUCCESS;
}

node *find_node(node *nodes[], int num_nodes, char *name) {
    //TO DO: replace this linear search with a hash
    int i;
    for (i = 0; i < num_nodes; i++)
        if (strcmp(nodes[i]->name, name) == 0)
            return nodes[i];
    return NULL;
}

node *new_node(char *name) { //will need to initialize next to NULL;
    node *n = malloc_safe(sizeof(node));
    n->name = name;
    n->num_children = 0;
    return n;
}

int read_tree(node *nodes[], int num_lines) { //this function will need updates when changing search to a hash based search
    node *parent_node, *child_node;
    char *parent_name, *child_name;
    int i, j, num_children;
    int num_nodes = 0;

    for (i = 0; i < num_lines; i++) {
        parent_name = malloc_safe(MAX_NAME);
        scanf("%s", parent_name);
        scanf("%d", &num_children);
        parent_node = find_node(nodes, num_nodes, parent_name);
        if (parent_node == NULL) {
            parent_node = new_node(parent_name);
            nodes[num_nodes] = parent_node; //for hash, run oaat on parent node and store at appropriate index - break this into a function call
            num_nodes++;
        } else {
            free(parent_name);
        }
        parent_node->children = malloc_safe(sizeof(node) * num_children);
        parent_node->num_children = num_children;
        for (j = 0; j < num_children; j++) {
            child_name = malloc_safe(MAX_NAME);
            scanf("%s", child_name);
            child_node = find_node(nodes, num_nodes, child_name);
            if (child_node == NULL) {
                child_node = new_node(child_name);
                nodes[num_nodes] = child_node; // for hash, use a function call add_node(node *nodes[]; node *node_to_add )
                num_nodes++;
            } else {
                free(child_name);
            }
            parent_node->children[j] = child_node;
        }
    }
    return num_nodes;
}

int score_node(node *n, int d) {
    int i, score = 0;
    if (d == 1)
        return n->num_children;
    for (i = 0; i < n->num_children; i++)
        score += score_node(n->children[i], d-1);
    return score;
}

void score_all(node ** nodes, int num_nodes, int d) {
    int i;
    for (i = 0; i < num_nodes; i++)
        nodes[i]->score = score_node(nodes[i], d);
    return;
}

int compare(const void *v1, const void *v2) {
    const node *n1 = *(const node ** )v1;
    const node *n2 = *(const node ** )v2;
    if (n1->score > n2->score)
        return -1;
    if (n1->score < n2->score)
        return 1;
    return strcmp(n1->name, n2->name);
}

void print_scores(node *nodes[], int num_nodes) {
    int i = 0;
    while (i < 3 && i < num_nodes && nodes[i]->score > 0) {
        printf("%s %d\n", nodes[i]->name, nodes[i]->score);
        i++;
        while (i < num_nodes && nodes[i]->score == nodes[i-1]->score && nodes[i]->score > 0){
            printf("%s %d\n", nodes[i]->name, nodes[i]->score);
            i++;
        }
    }
}

void *malloc_safe(int size) {
    char *mem = malloc(size);
    if (mem == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(EXIT_FAILURE);
    }
    return mem;
}