/* ===========================================================
                    Halloween Haul

    You want to collect all the candy from a particular
    neighborhood as efficiently as possible. The neihborhood
    is a binary tree

URL: https://dmoj.ca/problem/dwite12c1p4
Input: The input will contain 5 test cases. Each test case 
       is a line containing a single string, less than 256 
       characters long, describing the tree your neighbourhood 
       forms. 

Output: The output will contain 5 lines of output, each a pair 
        of integers  and .  is the minimum number of roads 
        needed to be traversed to get all the candy (starting 
        from the root (top) of the tree, and not needing to 
        return).  represents the total amount of candy you'll 
        collect.
        
=============================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 256
#define TEST_CASES 5

typedef struct node {
    int candy;
    struct node *left, *right;
} node;

node *new_house(int candy);
node *new_nonhouse(node *left, node *right);
node *read_tree(char *line);
node *read_tree_helper(char *line, int* pos);
int tree_candy(node *tree);
int tree_nodes(node *tree);
int tree_leaves(node *tree);
int tree_edges(node *tree);
int tree_height(node *tree);
int max(int a, int b);
void tree_solve(node *tree);
void tree_free(node *tree);


int main(){
    int i;
    char line[SIZE];
    node *tree;

    for (i = 0; i < TEST_CASES; i++) {
        fgets(line, SIZE, stdin); 
        tree = read_tree(line);
        tree_solve(tree);
        tree_free(tree);
    }

    return EXIT_SUCCESS;
}

node *new_house(int candy) {
    node *house = malloc(sizeof(node));
    if (house == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(EXIT_FAILURE);
    }
    house->candy = candy;
    house->left = NULL;
    house->right = NULL;
    return house;
}

node *new_nonhouse(node *left, node *right) {
    node *nonhouse = malloc(sizeof(node));
    if (nonhouse == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(EXIT_FAILURE);
    }
    nonhouse->candy = 0;
    nonhouse->left = left;
    nonhouse->right = right;
    return nonhouse;
}

int tree_candy(node *tree) {
    if (!tree->left && !tree->right)
        return tree->candy;
    return tree_candy(tree->left) + tree_candy(tree->right);
}

int tree_nodes(node *tree) {
    if (!tree->left && !tree->right)
        return 1;
    return tree_nodes(tree->left) + tree_nodes(tree->right) + 1;
}

int tree_leaves(node *tree) {
    if (!tree->left && !tree->right)
        return 1;
    return tree_leaves(tree->left) + tree_leaves(tree->right);
}

int tree_edges(node *tree) {
    if (!tree->left && !tree->right)
        return 0;
    return tree_edges(tree->left) + tree_edges(tree->right) + 2;
}

int tree_height(node *tree) {
    if (!tree->left && !tree->right)
        return 0;
    return max(tree_height(tree->left), tree_height(tree->right)) + 1;
}

void tree_solve(node *tree) {
    int candy = tree_candy(tree);
    int num_streets = 2 * tree_edges(tree) - tree_height(tree);
    printf("%d %d\n", num_streets, candy);
    return;
}

void tree_free(node *tree) {
    if (tree->left && tree->right){
        tree_free(tree->left);
        tree_free(tree->right);
    }
    free(tree);
    return;
}

int max(int a, int b) {
    if (a > b)
        return a;
    return b;
}

node *read_tree(char *line) {
    int pos = 0;
    return read_tree_helper(line, &pos);
}

node *read_tree_helper(char *line, int *pos) {
    node *tree;
    tree = malloc(sizeof(node));
    if (tree == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(EXIT_FAILURE);
    }
    if (line[*pos] == '(') {
        (*pos)++;
        tree->left = read_tree_helper(line, pos);
        (*pos)++;
        tree->right = read_tree_helper(line, pos);
        (*pos)++;
        return tree;
    } else {
        tree->left = NULL;
        tree->right = NULL;
        tree->candy = line[*pos] - '0';
        (*pos)++;
        if (line[*pos] != ')' && line[*pos] != ' ' && line[*pos] != '\0' && line[*pos] != '\n') {
            tree->candy = tree->candy * 10 + line[*pos] - '0';
            (*pos)++;
        }
        return tree;
    }
}