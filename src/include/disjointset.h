#ifndef DSU_H
#define DSU_H

#include <unordered_map>
#include <vector>
#include <stdexcept>

// Naive implementation of a disjoint set
template <class dataType, class hasher = std::hash<dataType>>
class DisjointSet {

	private:

		std::unordered_map<dataType, dataType, hasher> parents;

	public:

		/*
			Inserts a single item into the disjoint set.

			Input:
				Item to insert (dataType)

			Output:
				(none)
		*/
		void insert(dataType item) {

			parents[item] = item;
		}

		/*
			Inserts multiple items into the disjoint set.

			Input:
				Item to insert (dataType)

			Output:
				(none)
		*/
		void insert(std::vector<dataType> const &items) {

			for (auto item: items) {
				insert(item);
			}
		}

		/*
			Finds and returns an item's root value (which basically
			identifies the specific subset it belongs to.) Throws an
			exception when the item doesn't belong to any contained subset.

			Input:
				Item to insert (dataType)

			Output:
				Root value that identifies the subset item belongs to (dataType)
		*/
		dataType find(dataType item) {

			if (parents.end() == parents.find(item)) {
				throw std::invalid_argument("not in set");
			}

			dataType parent = parents[item];

			while (parent != parents[parent]) {
				parent = parents[parent];
			}

			return parent;
		}

		/*
			Merges two subsets within the disjoint set.

			Input:
				Item belonging to one set (dataType)
				Item belonging to another set (dataType)

			Output:
				(none)
		*/
		void merge(dataType a, dataType b) {

			parents[find(a)] = find(b);
		}
};

#endif