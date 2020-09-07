#include "HW4_Adj.h"

void tokenize(const string& str, vector<string>& tokens, const string& delimiters = " ")
{
	tokens.clear();
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	string::size_type pos = str.find_first_of(delimiters, lastPos);

	while (string::npos != pos || string::npos != lastPos)
	{
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		lastPos = str.find_first_not_of(delimiters, pos);
		pos = str.find_first_of(delimiters, lastPos);
	}
}

void adjReader(string filename, int& n_node, int**& adj) {

	ifstream file(filename);
	stringstream buffer;
	buffer << file.rdbuf();
	string input = buffer.str();

	vector<string> vInput;
	tokenize(input, vInput, "\n");

	n_node = vInput.size();
	adj = new int*[n_node];
	for (int i = 0; i < n_node; i++)
		adj[i] = new int[n_node];

	vector<string> vLine;
	for (int i = 0; i < n_node; i++) {
		tokenize(vInput[i], vLine, ",");

		for (int j = 0; j < n_node; j++)
			adj[i][j] = stoi(vLine[j]);

	}

}

void matrixToList(int n_node, int** adjMatrix, int* n_edge, Edge** adjList) {
	// TODO : Build an adjacency list from given adjacency matrix
	
	// Complete n_edge array
	for (int i = 0; i < n_node; i++) {
		int counter = 0;
		for (int j = 0; j < n_node; j++) {
			if (adjMatrix[i][j] != 0) {
				counter++;
			}
		}
		n_edge[i] = counter;
	}
	
	// Complete adjList array
	int edge_counter = 0; // to count idx of edge
	for (int i = 0; i < n_node; i++) {
		adjList[i] = new Edge[n_edge[i]];
		int num_adjNode = 0;
		for (int j = 0; j < n_node; j++) {
			if (adjMatrix[i][j] != 0) {
				adjList[i][num_adjNode] = Edge(edge_counter, i, j, adjMatrix[i][j]);
				edge_counter++;
				num_adjNode++;
			}
		}
	}
}