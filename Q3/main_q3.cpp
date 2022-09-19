#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>


/**
 * Digraph of integers.
 */
class Digraph {
private:
	int order; // Order of the graph
	std::vector<int>* graph; // Array of vectors, describing the arcs of a each node

public:
	/**
	 * @bried The constructor.
	 *
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
	 * @return 1 if a cycle is found, 0 if not.
	*/
	int containsCycle() {
		if (this->order == 0) return 0;

		// Initialise paths with arcs of first node
		std::vector<std::vector<int>> paths;
		for (int nextNode : this->graph[0]) {
			std::vector<int> path{ 0, nextNode };
			paths.push_back(path);
		}

		// Process each path
		while (paths.size() > 0) {
			std::vector<int> path = paths.at(0);

			// Add each child path to the paths vector
			int lastNode = path.back();
			for (int childNode : this->graph[lastNode]) {
				if (std::find(path.begin(), path.end(), childNode) != path.end()) {
					// Child node already exists in the path, cycle exists
					return 1;
				}
				else {
					// Create new path with this child node
					std::vector<int> newPath(path);
					newPath.push_back(childNode);

					paths.push_back(newPath); // Add child's path to paths vector
				}
			}

			paths.erase(paths.begin()); // Delete proessed path
		}

		return 0;
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
		std::cout << dg.containsCycle();
		i++;
	}

	return 0;
}
