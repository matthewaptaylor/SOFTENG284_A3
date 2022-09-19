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
	std::vector<int>* graph; // Array of adjacency list vectors

public:
	/**
	 * @brief The constructor.
	 * @param order Order of the graph.
	 */
	Digraph(int order) {
		this->order = order;
		this->graph = new std::vector<int>[order];
	}

	/**
	 * @brief The destructor.
	 */
	~Digraph() {
		delete[] this->graph;
	}

	/**
	 * @brief Adds an edge to the graph.
	 * @param node Node of the edge.
	 * @param arc Arc node of the edge.
	*/
	void addEdge(int node, int arc) {
		this->graph[node].push_back(arc);
	}

	/**
	 * @brief Determines whether the digraph contains a cycle.
	 * @return Whether the digraph is cyclic.
	*/
	bool containsCycle() {
		bool* visitedNodes = new bool[order] {false};
		bool* inCurrentPath = new bool[order] {false};

		// Search first node, then nodes not reachable from the first
		for (int i = 0; i < order; i++) {
			if (visitedNodes[i] == false && cycleDfs(i, visitedNodes, inCurrentPath))
				return true;
		}

		delete[] visitedNodes;
		delete[] inCurrentPath;

		return false;
	}

private:
	/**
	 * @brief Checks a node via Depth-first search for a cycle.
	 * @param node The node to check.
	 * @param visitedNodes Nodes that have already been checked.
	 * @param inCurrentPath Nodes that have led to this node.
	 * @return Whether a cycle exists.
	*/
	bool cycleDfs(int node, bool visitedNodes[], bool inCurrentPath[]) {
		if (visitedNodes[node] == false) {
			// Node not already checked
			visitedNodes[node] = true;
			inCurrentPath[node] = true;

			// Check each adjacent node
			for (int adjNode : this->graph[node]) {
				if (visitedNodes[adjNode] == false && cycleDfs(adjNode, visitedNodes, inCurrentPath))
					return true;
				else if (inCurrentPath[adjNode])
					return true;
			}
		}
		inCurrentPath[node] = false; // No longer checking
		
		return false;
	}
};


int main() {
	// Loop through each graph
	int i = 0;
	while (true) {
		int order;
		std::cin >> order;
		std::cin.ignore(); // Ignore next newline
		if (order == 0) break;

		Digraph dg(order);

		// Loop through each adjacency list
		for (int j = 0; j < order; j++) {
			std::string nodeAdjs;
			std::getline(std::cin, nodeAdjs);
			std::stringstream adjStream(nodeAdjs);

			// Loop through each adjacency/edge of node i
			for (int adj; adjStream >> adj;) {
				dg.addEdge(j, adj);
			}
		}

		// Print result
		if (i > 0)
			std::cout << std::endl;
		std::cout << dg.containsCycle() ? '1' : '0';
		i++;
	}

	return 0;
}
