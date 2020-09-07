#include "HW4_Adj.h"
#include "HW4_Heap.h"
#include <iostream>
using namespace std;

int main()
{
	int n_node;
	int** adjMatrix;
	adjReader("adj_matrix1.txt", n_node, adjMatrix);

	int* n_edge = new int[n_node];
	Edge** adjList = new Edge*[n_node];
	matrixToList(n_node, adjMatrix, n_edge, adjList);

	int cnt_edge = 0;
	for (int i = 0; i < n_node; i++) {
		cnt_edge += n_edge[i];
	}
	cnt_edge /= 2;
	Edge* edgeHeap = new Edge[cnt_edge];

	cnt_edge = 0;
	for (int i = 0; i < n_node; i++) {
		for (int j = 0; j < n_edge[i]; j++) {
			if (adjList[i][j].getDest() > i) {
				edgeHeap[cnt_edge] = adjList[i][j];
				cnt_edge++;
			}
		}
	}

	int* pos = new int[cnt_edge];
	for (int i = 0; i < cnt_edge; i++) {
		pos[i] = i;
		edgeHeap[i].setIdx(i);
	}

	cout << "Before : " << endl;
	for (int i = 0; i < cnt_edge; i++) {
		edgeHeap[i].print(); cout << ", pos : " << pos[edgeHeap[i].getIdx()] << endl;
	}

	heapSort<Edge>(edgeHeap, pos, cnt_edge);

	cout << "After : " << endl;
	for (int i = 0; i < cnt_edge; i++) {
		edgeHeap[i].print(); cout << ", pos : " << pos[edgeHeap[i].getIdx()] << endl;
	}

}