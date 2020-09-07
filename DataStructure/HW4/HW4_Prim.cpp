#include "HW4_Prim.h"

void prim(int n_node, int* n_edge, Edge** adjList, int start_node) {

	// Initialization
	int* S = new int[n_node];
	Edge* T = new Edge[n_node];
	Node* W = new Node[n_node];
	int* W_pos = new int[n_node];

	// TODO : Implement prim algorithm
	
	// Initialization
	// Default
	for (int i = 0; i < n_node; i++) {
		S[i] = NULL;
		W[i].setIdx(i);
		W[i].setDist(INF);
		W_pos[i] = i;
	}
	int S_size = 0;
	int T_size = 0;
	// include Source
	S[0] = start_node;
	S_size++;
	W[start_node].setDist(0);

	// Step A, B
	
	while (S_size < n_node) {

		// update distance(W[]) between S[], not S[]
		int updated_node_idx = S[S_size - 1]; 	// idx of updated Node just Before
		for (int i = 0; i < n_edge[updated_node_idx]; i++) {
			if (W[W_pos[adjList[updated_node_idx][i].getDest()]].getDist() > adjList[updated_node_idx][i].getDist()) {
				W[W_pos[adjList[updated_node_idx][i].getDest()]].setDist(adjList[updated_node_idx][i].getDist());
			}
		}

		// find the node to append to S[]
		heapSort<Node>(W, W_pos, n_node);
		S[S_size] = W[S_size].getIdx();
		S_size++;

		// update T[]
		updated_node_idx = S[S_size - 1];
		for (int i = 0; i < S_size; i++) {
			int node_index = S[i];
			for (int j = 0; j < n_edge[node_index]; j++) {
				if (adjList[node_index][j].getDest() == updated_node_idx) {
					if (adjList[node_index][j].getDist() == W[S_size - 1].getDist()) {
						T[T_size] = adjList[node_index][j];
						T_size++;
					}
				}
			}
		}

		// Make distance of Nodes in S[] '0'
		W[S_size - 1].setDist(0);
	}

	delete[] S;


	// DO NOT MODIFY - Print the result
	cout << endl << "Result : " << endl;
	cout << "T : " << endl;
	for (int i = 0; i < n_node - 1; i++) {
		if (T[i].getSrc() > T[i].getDest()) {
			int temp = T[i].getSrc();
			T[i].setSrc(T[i].getDest());
			T[i].setDest(temp);
		}
		cout << T[i].getSrc() << " - " << T[i].getDest() << " (" << T[i].getDist() << ")" << endl;
	}

}