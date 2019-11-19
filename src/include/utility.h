#ifndef UTILITY_H
#define UTILITY_H

#include <algorithm>

// Hashes instances of std::pair
struct hashPair {

	template <class T1, class T2>
	size_t operator()(const std::pair<T1, T2> &pair) const {

		auto hash1 = std::hash<T1>{}(pair.first);
		auto hash2 = std::hash<T2>{}(pair.second);

		return hash1 ^ hash2;
	}
};

#endif