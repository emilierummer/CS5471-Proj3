#include "TreeUtils.h"
#include <string.h>
#include <openssl/sha.h>

// Prints the tree nodes in order
void printTree(TreeNode *root, int level) {
    if (root == NULL) {
        return;
    }
    printf("%*s%s\n", level * 4, "", root->hash);
    printTree(root->left, level + 1);
    printTree(root->right, level + 1);
}

// Frees the memory allocated for the tree nodes
void freeTree(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// Generates leaf nodes for the given number of transactions
TreeNode **generateLeaves(int numTx) {
    TreeNode **leaves = malloc(numTx * sizeof(TreeNode *));
    for (int i = 0; i < numTx; i++) {
        leaves[i] = malloc(sizeof(TreeNode));
        snprintf(leaves[i]->hash, 64, "Tx%d", i + 1);
        leaves[i]->left = NULL;
        leaves[i]->right = NULL;
    }
    return leaves;
}

// Creates the next level of the tree from the current level
// Combines pairs of nodes to create parent nodes
TreeNode **createNextLevel(TreeNode **currentLevel, int currentLevelSize) {
    int nextLevelSize = currentLevelSize / 2;
    TreeNode **nextLevel = malloc(nextLevelSize * sizeof(TreeNode *));
    for (int i = 0; i < nextLevelSize; i++) {
        nextLevel[i] = malloc(sizeof(TreeNode));
        snprintf(nextLevel[i]->hash, 64, "%s+%s", currentLevel[2 * i]->hash, currentLevel[2 * i + 1]->hash);
        nextLevel[i]->left = currentLevel[2 * i];
        nextLevel[i]->right = currentLevel[2 * i + 1];
    }
    return nextLevel;
}
