#include <iostream>
#include <string>
#include <sstream>


/**
 * A class describing a hash table that uses linear probing for collision resolution.
 */
class LinearProbingTable {
};


/**
 * A class describing a hash table using double hashing.
 */
class DoubleHashTable {
};


int main() {
	// Loop through each data source
	std::string hashLine;
	while (std::getline(std::cin, hashLine)) {
		std::stringstream lineStream(hashLine);

		// Get size of hash table
		int m;
		lineStream >> m;
		lineStream.ignore();

		// Get prime used for open addressing with double hashing
		int p;
		lineStream >> p;
		lineStream.ignore();

		// Loop through hash keys
		for (int i; lineStream >> i;) {
			std::cout << i << std::endl;

			if (lineStream.peek() == ',')
				lineStream.ignore();
		}
	}

	return 0;
}
