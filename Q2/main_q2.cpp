#include <iostream>
#include <string>
#include <sstream>
#include <vector>


/**
 * Digraph of integers.
 */
class Digraph {
private:
	int order; // Order of the graph
	std::vector<int>* graph; // Array of vectors, describing the arcs of a each node

public:
	/**
	 * The constructor.
	 *
	 * \param order Order of the graph.
	 */
	Digraph(int order) {
		this->order = order;
		this->graph = new std::vector<int>[order];
	}

	/**
	 * The destructor.
	 */
	~Digraph() {
		delete[] this->graph;
	}

	/**
	 * Adds an edge to the graph.
	 *
	 * \param node Node of the edge.
	 * \param edge Arc node of the edge.
	 */
	void addEdge(int node, int arc) {
		this->graph[node].push_back(arc);
	}

	/**
	 * Adds an edge to the graph, reversed.
	 *
	 * \param node Node of the edge.
	 * \param edge Arc node of the edge.
	 */
	void addReversedEdge(int node, int arc) {
		this->addEdge(arc, node);
	}

	/**
	 * Prints the order of the graph, then the adjacency list for each node.
	 */
	void printGraph() {
		std::cout << this->order << std::endl;

		// Loop through each node
		for (int i = 0; i < this->order; i++) {
			std::vector<int> arcs = this->graph[i];

			// Print each arc of the node
			for (int j = 0; j < arcs.size(); j++) {
				if (j > 0)
					std::cout << ' '; // Add seperating space

				std::cout << arcs.at(j);
			}
			std::cout << std::endl;
		}
	}
};


int main() {
	// Loop through each graph
	while (true) {
		int order;
		std::cin >> order;
		std::cin.ignore(); // Ignore next newline
		if (order == 0) break;

		Digraph dg(order);

		// Loop through each adjacency list
		for (int i = 0; i < order; i++) {
			std::string nodeAdjs;
			std::getline(std::cin, nodeAdjs);
			std::stringstream adjStream(nodeAdjs);

			// Loop through each adjacency/edge of node i
			for (int adj; adjStream >> adj;) {
				dg.addReversedEdge(i, adj);
			}
		}

		dg.printGraph();
	}

	std::cout << '0';

	return 0;
}
