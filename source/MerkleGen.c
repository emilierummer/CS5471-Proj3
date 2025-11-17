#include "TreeUtils.h"


// Gets the Merkle branch for a given transaction index
TreeNode **getMerkleBranch(TreeNode *transactionNode, int branchLength) {
    TreeNode **branch = malloc(branchLength * sizeof(TreeNode *));
    TreeNode *currentNode = transactionNode;

    for (int i = 0; i < branchLength; i++) {
        TreeNode *sibling = getSibling(currentNode);
        if (sibling != NULL) {
            branch[i] = malloc(sizeof(TreeNode));
            snprintf(branch[i]->hash, 64, "%s", sibling->hash);
        } else {
            branch[i] = NULL;
        }
        currentNode = currentNode->parent;
    }
    return branch;
}


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
    int txIndex = atoi(&argv[2][2]) - 1; // Convert to 0-based index
    if (txIndex < 0 || txIndex >= numTx) {
        printf("Error: Txi must be between 1 and %d.\n", numTx);
        return 2;
    }


    // Generate leaf node for each Tx
    TreeNode **leaves = generateLeaves(numTx);
    TreeNode *txNode = leaves[txIndex];

    // Create the Merkle Tree (bottom-up)
    while (numTx > 1) {
        leaves = createNextLevel(leaves, numTx);
        numTx /= 2;
    }

    // Store Merkle root in root.txt
    FILE *rootFile = fopen("root.txt", "w");
    if (rootFile == NULL) {
        perror("Failed to open root.txt");
        return 1;
    }
    fprintf(rootFile, "%X\n", leaves[0]->hash);
    fclose(rootFile);

    // Print tree
    printTree(leaves[0], 0);

    // Store Merkle branch in branch.txt
    TreeNode **merkleBranch = getMerkleBranch(txNode, n);
    FILE *branchFile = fopen("branch.txt", "w");
    if (branchFile == NULL) {
        perror("Failed to open branch.txt");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        if (merkleBranch[i] != NULL) {
            fprintf(branchFile, "%X\n", merkleBranch[i]->hash);
            free(merkleBranch[i]);
        } else {
            fprintf(branchFile, "NULL\n");
        }
    }
    fclose(branchFile);
    free(merkleBranch);

    // Free allocated memory
    freeTree(leaves[0]);

    return 0;
}