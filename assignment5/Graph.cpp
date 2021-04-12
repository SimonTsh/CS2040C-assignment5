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
	int inf = 4294967294 / 2;
	int current = s;
	if (current == d)
		return 0; // base case

	bool *visited = new bool[_nv]; // create an array of visited vertices
	int *dist = new int[_nv];
	//Graph* parent = new Graph[_nv]; // store parent nodes
	
	Heap<int> pq; // create priority queue using heap implemented in assignment 4 for every query
	for (int v = 0; v < _nv; v++) {
		visited[v] = false;
		if (v == current)
			dist[v] = 0;
		else
			dist[v] = inf;
		//cout << "Node: " << v << ", Node status: " << visited[v] << ", Node dist: " << dist[v] << endl;
		pq.insert(-dist[v]);
		//cout << "Insert " << -dist[i] << " into priority queue" << endl;
	}

	//for (_al[v].start(); !_al[v].end(); _al[v].next()) {
	//	pq.insert(_al[v].current().weight()); // pq sorted by weight/distance
	//	//cout << "Insert " << _al[v].current().nodeIndex() << " into priority queue with weight " << _al[v].current().weight() << endl;
	//}

	while (!pq.empty()) {
		int weight = pq.extractMax();
		weight = -weight; // to convert max to min heap e.g. extracting w_1 = 0 for s
		cout << weight << endl;
		for (int i = 0; i < _nv; i++) {
			if (_al[i].current().weight() == weight) {
				current = _al[i].current().nodeIndex(); // how to find the index corresponding to next min? hash table?
				cout << "index is: " << current << endl;
				visited[current] = true;
			}
		}

		_al[current].start();
		int v = _al[current].current().nodeIndex(); // origin e.from()
		while (!_al[current].end()) {
			int w = _al[current].current().nodeIndex(); // destination e.to()
			cout << v << ", " << w << endl;

			if (w == d) return dist[w];

			// relax edges
			if (!visited[w] && dist[w] > dist[v] + weight) {
				//dist[w] = dist[v] + weight;
				pq.decreaseKey(dist[w], dist[v]+weight);
			}

			_al[current].next();

		//for (_al[current].start(); !_al[current].end(); _al[current].next()) { // first node should be s
		//	visited[current] = true;
		//	int w = _al[current].current().nodeIndex(); // destination e.to()
		//	cout << current << ", " << w << endl;
		//	
		//	if (w == d)
		//		return dist[w];

		//	// relaxation algorithm
		//	if (dist[w] > _al[current].current().weight() + weight) { // 10000 > 5 + 0
		//		dist[w] = _al[current].current().weight() + weight; // = 5
		//		cout << current << ", " << dist[w] << endl;
		//		pq.decreaseKey(w, dist[w]); // decrease infinity to 5; should be both values instead?
		//	}

		}
	}

	// return infinity (-1 in this case) for nodes that are not connected
	// adding linked list into each slot of an array/vector
	// print path by following the train of parent nodes
	delete[] visited, dist;
	
	return -1;
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