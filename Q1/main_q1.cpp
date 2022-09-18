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
	 * Adds a key to the hash table.
	 *
	 * \param key The key to add to the hash table.
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

			// Check next address to the left
			i = this->nextAddress(i, key);
		}

		if (i != hash(key))
			this->collisions++;
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
	 * \param key The key to hash.
	 * \return The hashed value.
	 */
	int hash(int key) {
		return key % this->size;
	}

private:
	/**
	 * Calculates the next address to probe.
	 *
	 * \param i The current address.
	 * \param key The key to be inserted.
	 * \return The next address.
	 */
	virtual int nextAddress(int i, int key) = 0;
};


/**
 * Hash table that uses linear probing for collision resolution.
 */
class LinearProbingTable : public HashTable {
	using HashTable::HashTable; // Inherit HashTable constructor

private:
	/**
	 * Calculates the next address to probe.
	 *
	 * \param i The current address.
	 * \return The next address.
	 */
	int nextAddress(int i, int) {
		i--;
		if (i < 0)
			i += this->size;
		return i;
	}
};


/**
 * Hash table using double hashing for collision resolution.
 */
class DoubleHashTable : public HashTable {
private:
	int p; // Number used for open addressing

public:
	/**
	 * The constructor.
	 *
	 * \param size Size of the hash table.
	 * \param p Number used for open addressing.
	 */
	DoubleHashTable(int size, int p) : HashTable(size) {
		this->p = p;
	}

private:
	/**
	 * Calculates the next address to probe.
	 *
	 * \param i The current address.
	 * \param key The key to be inserted.
	 * \return The next address.
	 */
	int nextAddress(int i, int key) {
		i -= (key % p) + 1;
		if (i < 0)
			i += this->size;
		return i;
	}
};


int main() {
	// Loop through each set of keys
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
		DoubleHashTable dhTable(size, p);

		// Loop through hash keys
		for (int i; lineStream >> i;) {
			lpTable.addKey(i);
			dhTable.addKey(i);

			// Ignore next comma
			if (lineStream.peek() == ',')
				lineStream.ignore();
		}

		std::cout << lpTable.getCollisions() << ',' << lpTable.getFinalProbes() << ',';
		std::cout << dhTable.getCollisions() << ',' << dhTable.getFinalProbes() << std::endl;
	}

	return 0;
}
