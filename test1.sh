 #!/bin/bash

 n_array=(0 2 4 6 8 10 11)
 tx_array=(0 Tx1 Tx3 Tx10 Tx20 Tx31 Tx100)

 for i in {1..6}; do
	rm -rf Results/test$i
	mkdir -p Results/test$i
	./MerkleGen ${n_array[i]} ${tx_array[i]}
	mv branch.txt Results/test$i
	mv root.txt Results/test$i
done
