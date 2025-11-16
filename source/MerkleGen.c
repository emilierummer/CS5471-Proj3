#include "TreeUtils.h"

int main() {
    printf("MerkleGen program started.\n");
    int numTx = 4;

    // Generate leaf node for each Tx
    TreeNode **leaves = generateLeaves(numTx);

    // Print leaf nodes
    for (int i = 0; i < numTx; i++) {
        printf("Leaf %d Hash: %s\n", i + 1, leaves[i]->hash);
    }

    // Create the Merkle Tree (bottom-up)
    while (numTx > 1) {
        leaves = createNextLevel(leaves, numTx);
        numTx /= 2;
    }

    // Print tree
    printf("Merkle Root Hash: %s\n", leaves[0]->hash);
    printTree(leaves[0], 0);

    // Free allocated memory
    freeTree(leaves[0]);

    return 0;
}