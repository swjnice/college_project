#include "HW4_Prim.h"

void prim(int n_node, int* n_edge, Edge** adjList, int start_node) {

	// Initialization
	int* S = new int[n_node];
	Edge* T = new Edge[n_node];
	Node* W = new Node[n_node];
	int* W_pos = new int[n_node];

	// TODO : Implement prim algorithm

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