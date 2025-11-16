#include "TreeUtils.h"

int main(int argc, char *argv[]) {
    // Process command-line arguments
    if (argc != 3) {
        printf("Usage: MerkleGen <n> <Txi>\n");
        return 1;
    }

    int n = atoi(argv[1]);
    if (n < 1 || n > 12) {
        printf("Error: n must be between 1 and 12.\n");
        return 1;
    }
    int numTx = 1 << n; // 2^n transactions

    if (argv[2][0] != 'T' || argv[2][1] != 'x') {
        printf("Error: Transactions must be in the format Txi where i is the transaction number.\n");
        return 1;
    }
    int txIndex = atoi(&argv[2][2]);
    if (txIndex < 1 || txIndex > numTx) {
        printf("Error: Txi must be between 1 and %d.\n", numTx);
        return 1;
    }


    // Generate leaf node for each Tx
    TreeNode **leaves = generateLeaves(numTx);

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