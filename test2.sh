#!/bin/bash

echo -e "\n\n\n\n\n\n"

echo "./MerkleGen 2 Tx3"
./MerkleGen 2 Tx3
echo "./VerifyTx root.txt branch.txt Tx3"
./VerifyTx root.txt branch.txt Tx3
echo "./VerifyTx root.txt branch.txt Tx2"
./VerifyTx root.txt branch.txt Tx2

echo -e "\n\n\n\n\n\n"

echo "./MerkleGen 10 Tx2"
./MerkleGen 10 Tx2
echo "./VerifyTx root.txt branch.txt Tx3"
./VerifyTx root.txt branch.txt Tx3
echo "./VerifyTx root.txt branch.txt Tx2"
./VerifyTx root.txt branch.txt Tx2

echo -e "\n\n\n\n\n\n"

echo "./MerkleGen 11 Tx100"
./MerkleGen 11 Tx100
echo "./VerifyTx root.txt branch.txt Tx100"
./VerifyTx root.txt branch.txt Tx100
echo "./VerifyTx root.txt branch.txt Tx2"
./VerifyTx root.txt branch.txt Tx2

echo -e "\n\n\n\n\n\n"
