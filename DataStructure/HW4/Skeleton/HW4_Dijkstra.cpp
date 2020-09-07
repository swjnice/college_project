#include "HW4_Dijkstra.h"

void dijkstra(int n_node, int* n_edge, Edge** adjList, int start_node) {

	// Initialization
	int* N = new int[n_node];
	Edge* T = new Edge[n_node];
	Node* D = new Node[n_node];
	int* D_pos = new int[n_node];

	// TODO : Implement dijkstra algorithm

	// DO NOT MODIFY - Print the result
	cout << endl << "Result : " << endl;

	cout << endl << "D : " << endl;
	for (int i = 0; i < n_node; i++) {
		D[D_pos[i]].print(); cout << endl;
	}

}
