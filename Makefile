CC := cc
CFLAGS := -O2

SRCDIR := source

all: TreeUtils MerkleGen VerifyTx

TreeUtils: $(SRCDIR)/TreeUtils.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/TreeUtils.c -o TreeUtils.o

MerkleGen: $(SRCDIR)/MerkleGen.c TreeUtils
	$(CC) $(CFLAGS) -o MerkleGen $(SRCDIR)/MerkleGen.c TreeUtils.o

VerifyTx: $(SRCDIR)/VerifyTx.c TreeUtils
	$(CC) $(CFLAGS) -o VerifyTx $(SRCDIR)/VerifyTx.c TreeUtils.o

clean:
	rm -rf MerkleGen VerifyTx TreeUtils.o root.txt branch.txt