#include "HW4_Dijkstra.h"

void dijkstra(int n_node, int* n_edge, Edge** adjList, int start_node) {

	// Initialization
	int* N = new int[n_node];
	Edge* T = new Edge[n_node];
	Node* D = new Node[n_node];
	int* D_pos = new int[n_node];

	// TODO : Implement dijkstra algorithm
	
	// Initialize
	// Default
	for (int i = 0; i < n_node; i++) {
		N[i] = NULL;
		D[i].setIdx(i);
		D[i].setDist(INF);
		D_pos[i] = i;
	}
	int N_size = 0;
	int T_size = 0;
	// include Source
	N[0] = start_node;
	N_size++;
	D[start_node].setDist(0);
	
	// Step A,B

	while (N_size < n_node) {

		// update D[] by N[] (Step B)
		int upd_node_idx = N[N_size - 1]; // idx of updated node just before
		for (int i = 0; i < n_edge[upd_node_idx]; i++) {
			if (D[D_pos[adjList[upd_node_idx][i].getDest()]].getDist() > D[D_pos[upd_node_idx]].getDist() + adjList[upd_node_idx][i].getDist()) {
				D[D_pos[adjList[upd_node_idx][i].getDest()]].setDist(D[D_pos[upd_node_idx]].getDist() + adjList[upd_node_idx][i].getDist());
			}
		}
		

		// find the node to append to N[]
		heapSort<Node>(D, D_pos, n_node);
		N[N_size] = D[N_size].getIdx();
		N_size++;

		// update T[]
		upd_node_idx = N[N_size - 1];
		for (int i = 0; i < N_size; i++) {
			int node_index = N[i];
			for (int j = 0; j < n_edge[node_index]; j++) {
				if (adjList[node_index][j].getDest() == upd_node_idx) {
					if (D[N_size - 1].getDist() == D[D_pos[node_index]].getDist() + adjList[node_index][j].getDist()) {
						T[T_size] = adjList[node_index][j];
						T_size++;
					}
				}
			}	
		}
	}

	delete[] N;


	// DO NOT MODIFY - Print the result
	cout << endl << "Result : " << endl;

	cout << endl << "D : " << endl;
	for (int i = 0; i < n_node; i++) {
		D[D_pos[i]].print(); cout << endl;
	}

}
