#ifndef HW4_DIJKSTRA_H
#define HW4_DIJKSTRA_H

#include "HW4_Adj.h"
#include "HW4_Heap.h"
#include "HW4_Node.h"
#include <iostream>

#define INF 10000
using namespace std;

void dijkstra(int n_node, int* n_edge, Edge** adjList, int start_node);

#endif