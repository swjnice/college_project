#include "HW4_Dijkstra.h"
#include <iomanip>

void main() {

	int n_node;
	int** adjMatrix;
	adjReader("adj_matrix3.txt", n_node, adjMatrix);

	cout << "Adjacency Matrix : " << endl;
	for (int i = 0; i < n_node; i++) {
		for (int j = 0; j < n_node; j++) {
			cout << setw(3) << adjMatrix[i][j] << " ";
		}
		cout << endl;
	}

	int* n_edge = new int[n_node];
	Edge** adjList = new Edge*[n_node];
	matrixToList(n_node, adjMatrix, n_edge, adjList);

	cout << endl << "Adjacency List : " << endl;
	for (int i = 0; i < n_node; i++) {
		for (int j = 0; j < n_edge[i]; j++) {
			adjList[i][j].print();
			cout << "\t";
		}
		cout << endl;
	}

	dijkstra(n_node, n_edge, adjList, 0);

}
