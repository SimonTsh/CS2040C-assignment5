#include "Graph.h"
//uncomment this to include your own "heap.h"
//we will assume that you use the same code in your previous assignment
#include "heap.h"

std::ostream& operator<<(std::ostream& os, nodeWeightPair const& n) {
	return os << " (idx:" << n._node << " w:" << n._weight << ")";
}


Graph::Graph(int n)
{
	_al = new List<nodeWeightPair> [n];
	_nv = n;
}

int Graph::shortestDistance(int s, int d)
{
	// s is the source; d is the destination
	int inf = 1000000;

	bool *visited = new bool[_nv]; // create an array of visited vertices/nodes
	int *dist = new int[_nv]; // create an output array that stores shortest distanceS
	int *parent = new int[_nv]; // store parent nodes
	List<int>* path = new List<int>; // to store path from source to destination

	Heap<int> pq; // create priority queue using heap implemented in assignment 4 for every query
	for (int v = 0; v < _nv; v++) {
		visited[v] = false;
		if (v == s) {
			dist[v] = 0;
			parent[v] = -1; // source node has no parent
		}
		else
			dist[v] = inf;
		pq.insert(-dist[v]); // priority queue will sort in order of distance
	}

	while (!pq.empty()) {
		int weight = pq.extractMax();
		weight = -weight; // to convert max to min heap

		for (int i = 0; i < _nv; i++) {
			if (!visited[i] && dist[i] == weight) {
				visited[i] = true;

				for (_al[i].start(); !_al[i].end(); _al[i].next()) { // else continue updating the neighbouring nodes
					int w = _al[i].current().nodeIndex(); // destination "to" i.e. adjacent nodes
					int n_w = _al[i].current().weight(); // desination nodes' weight e.g. 9, 8, 5

					if (!visited[w] && dist[w] > (dist[i] + n_w)) { // if neighbour has not been extracted and prev neighbour distance is more than node + actual weight
						pq.deleteItem(-dist[w]);
						dist[w] = dist[i] + n_w; // e.g. dist[1] = 5, etc.
						pq.insert(-dist[w]); // to overcome decreaseKey that is node-node instead of key-node pair
						parent[w] = i; // stores predecessor node of neighbour
					}
				}
			}
		}
	}
	
	//int dist_weight = dist[d];
	//delete[] dist, visited;

	if (dist[d] != inf) {
		int desti = d;

		while (desti != -1) { // until the source node is reached
			path->insertHead(desti);
			desti = parent[desti];
		};
		
		cout << "Path: ";
		for (path->start(); !path->end(); path->next()) { // printing function
			if (path->current() == d)
				cout << path->current();
			else
				cout << path->current() << " ";
		}
		cout << endl;

		//path->print(); // built in list print function

		return dist[d];
	}
	else return -1;
}

void Graph::addEdge(int s, int d, int w)
{
	_al[s].insertHead(nodeWeightPair(d, w)); // insert to each array slot a node-weight pair
}

void Graph::printGraph()
{
	for (int i=0; i < _nv; i++)
	{
		cout << "Node " << i << ": ";
		for (_al[i].start(); !_al[i].end(); _al[i].next())
			cout << " (" << _al[i].current().nodeIndex() << "," << _al[i].current().weight() << ")";
		cout << endl;

	}

}
Graph::~Graph()
{

	delete[] _al;

}