#ifndef DFS_H
#define DFS_H

#include <unordered_map>
#include <unordered_set>

#include "../utility.h"
#include "../generator.h"

class DFS: public Generator {

	private:

		// The room we're currently visiting
		std::pair<int, int> curRoom;

		// Rooms with neighbors we might still have to visit
		std::vector<std::pair<int, int>> roomStack;

		// Tracks which rooms have already been visited
		std::unordered_set<std::pair<int, int>, hashPair> visited;

		// Records the neighbors of each room
		std::unordered_map<std::pair<int, int>, std::vector<std::pair<int, int>>, hashPair> neighbors;

		/*
			Returns all unvisited neighbors of the given room.

			Input:
				Room whose unvisited neighbors we want (std::pair<int, int>)

			Ouput:
				Vector of unvisited neighbors (std::vector<std::pair<int, int>>)
		*/
		std::vector<std::pair<int, int>> getUnvisitedNeighbors(
		std::pair<int, int> room);

	protected:

		/*
			Implements maze generation using a depth first search.

			Input:
				2D vector of maze's rooms

			Ouput:
				(none)
		*/
		virtual void doGenerate(std::vector<std::vector<Room>> &rooms);

	public:

		/*
			Creates and returns a new instance of DFS.

			Input:
				(none)

			Ouput:
				Pointer to Generator instance (std::unique_ptr<Generator>)
		*/
		virtual std::unique_ptr<Generator> instantiate() const;
};

#endif