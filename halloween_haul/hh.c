/* =========================================================
                    Halloween Haul

    You want to collect all the candy from a particular
    neighborhood as efficiently as possible. The neihborhood
    is a binary tree

Input: 

Output: 
        
==========================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

int main(){
    node *four = new_house(4);
    node *nine = new_house(9);
    node *B = new_nonhouse(four, nine);
    node *fifteen = new_house(15);
    node *C = new_nonhouse(B, fifteen);
    
    printf("C->left->right->candy: %d\n", C->left->right->candy);
    printf("Node 4 candy: %d\nTree candy: %d\n", tree_candy(four), tree_candy(C));
    printf("Tree nodes: %d\n", tree_nodes(C));
    printf("Tree leaves: %d\n", tree_leaves(C));
    printf("Tree edges: %d\n", tree_edges(C));
    printf("Tree height: %d\n", tree_height(C));
    printf("Shortest path: %d\n", 2*tree_edges(C) - tree_height(C));

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

}