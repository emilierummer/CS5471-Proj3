#ifndef TREEUTILS_H
#define TREEUTILS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    char hash[64];
    struct TreeNode *left;
    struct TreeNode *right;
    struct TreeNode *parent;
} TreeNode;

unsigned char *hash(const char *data);

void printTree(TreeNode *root, int level);
void freeTree(TreeNode *root);

TreeNode **generateLeaves(int numTx);
TreeNode **createNextLevel(TreeNode **currentLevel, int currentLevelSize);

TreeNode *getSibling(TreeNode *node);

#endif