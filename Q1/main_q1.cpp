#include <iostream>
#include <string>
#include <sstream>


/**
 * Hash table.
 */
class HashTable {
protected:
	int size; // Size of the hash table
	int* table; // Hash table as an array
	int collisions; // Total keys that collide upon insertion
	int finalProbes; // Probes required to look up the final item

public:
	/**
	 * The constructor.
	 *
	 * \param size Size of the hash table.
	 */
	HashTable(int size) {
		this->size = size;
		this->table = new int[size]();
		this->collisions = 0;
		this->finalProbes = 0;
	}

	/**
	 * The destructor.
	 */
	~HashTable() {
		delete[] this->table;
	}

	/**
	 * Gets collisions.
	 *
	 * \return Total keys that collide upon insertion.
	 */
	int getCollisions() {
		return this->collisions;
	}

	/**
	 * Gets finalProbes.
	 *
	 * \return Probes required to look up the final item.
	 */
	int getFinalProbes() {
		return this->finalProbes;
	}

protected:
	/**
	 * Hashes a key.
	 *
	 * \param key Key to hash.
	 * \return Hashed value.
	 */
	int hash(int key) {
		return key % this->size;
	}
};


/**
 * Hash table that uses linear probing for collision resolution.
 */
class LinearProbingTable : public HashTable {
	using HashTable::HashTable; // Inherit HashTable constructor

public:
	/**
	 * Adds a key to the hash table.
	 *
	 * \param key Key to add to the hash table.
	 */
	void addKey(int key) {
		this->finalProbes = 0; // Track probes of this addition 

		// Fill first empty address with key
		int i = hash(key);
		while (true) {
			this->finalProbes++;

			// Fill empty address and break
			if (this->table[i] == 0) {
				this->table[i] = key;
				break;
			}

			// Check address to the left
			if (i == 0)
				i = size;
			i--;
		}

		if (i != hash(key))
			collisions++;
	}
};


/**
 * Hash table using double hashing for collision resolution.
 */
class DoubleHashTable {
};


int main() {
	// Loop through each data source
	std::string hashLine;
	while (std::getline(std::cin, hashLine)) {
		std::stringstream lineStream(hashLine);

		// Get size of hash table
		int size;
		lineStream >> size;
		lineStream.ignore();

		// Get prime used for open addressing with double hashing
		int p;
		lineStream >> p;
		lineStream.ignore();

		LinearProbingTable lpTable(size);

		// Loop through hash keys
		for (int i; lineStream >> i;) {
			lpTable.addKey(i);

			// Ignore next comma
			if (lineStream.peek() == ',')
				lineStream.ignore();
		}

		std::cout << lpTable.getCollisions() << ',' << lpTable.getFinalProbes() << std::endl;
	}

	return 0;
}
