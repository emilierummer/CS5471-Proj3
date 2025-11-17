#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "TreeUtils.h"

int getTreeHeight(const char *branchFilename) {
    // Open file
    FILE *file = fopen(branchFilename, "r");
    if (file == NULL) {
        printf("Error: Could not open branch file.\n");
        return -1;
    }

    // Count lines to determine height
    int height = 0;
    char buf;
    while ((buf = fgetc(file)) != EOF) {
        if (buf == '\n') {
            height++;
        }
    }
    fclose(file);
    return height;
}

void execMerkleGen(int treeHeight, char *txIdentifier) {
    // Set up args
    char filename[] = "./MerkleGen";
    char treeHeightString[10];
    snprintf(treeHeightString, sizeof(treeHeightString), "%d", treeHeight);
    char *const args[] = { filename, treeHeightString, txIdentifier, NULL };

    // Redirect output
    FILE *outputFile = fopen("/dev/null", "w");
    if (outputFile == NULL) {
        printf("Error: Could not open output file for MerkleGen.\n");
        return;
    }
    dup2(fileno(outputFile), STDOUT_FILENO);
    dup2(fileno(outputFile), STDERR_FILENO);
    fclose(outputFile);

    // Run MerkleGen
    execv(filename, args);
}

int main(int argc, char *argv[]) {
    // Process command-line arguments
    if (argc != 4) {
        printf("Usage: VerifyTx <root.txt> <branch.txt> Txi\n");
        return 1;
    }
    char *rootFilename = argv[1];
    char *branchFilename = argv[2];
    char *txIdentifier = argv[3];

    int treeHeight = getTreeHeight(branchFilename);
    if (treeHeight == -1) {
        printf("Error: Could not determine tree height.\n");
        return 1;
    }

    // Run MerkleGen as a child process
    if (fork() == 0) {
        execMerkleGen(treeHeight, txIdentifier);
    } else {
        // Wait for child process to complete
        int status;
        wait(&status);

        switch (WEXITSTATUS(status)) {
            case 0:
                printf("Yes\n");
                break;
            case 1:
                printf("Error checking transaction (Not valid Tx)\n");
                break;
            case 2:
                printf("No\n");
                break;
            default:
                printf("Unexpected exit status: %d (Not valid Tx)\n", WEXITSTATUS(status));
        }

        return 0;
    }
}
