#include <algorithm>
#include <unordered_map>

#include "../include/utility.h"
#include "../include/disjointset.h"
#include "../include/generators/kruskal.h"

std::unique_ptr<Generator> Kruskal::instantiate() const {

	return std::make_unique<Kruskal>();
}

void Kruskal::doGenerate(std::vector<std::vector<Room>> &rooms) {

	const int width = maze->getWidth();
	const int height = maze->getHeight();

	std::vector<RoomIndexPair> walls;
	DisjointSet<std::pair<int, int>, hashPair> roomSets;

	// Generate list of walls, represented as pairs of (x,y) coordinates, as
	// well as an initial set of cells (starts out as one set per cell)
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {

			if (x < width - 1) {
				walls.push_back({{x, y}, {x + 1, y}});
			}

			if (y < height - 1) {
				walls.push_back({{x, y}, {x, y + 1}});
			}

			// Create set containing just the one room
			roomSets.insert({x, y});
		}
	}

	// Shuffle the list of walls so we can visit them in a random order
	std::random_shuffle(walls.begin(), walls.end());

	for (auto wall: walls) {

		// If the rooms divided by this wall belong to two distinct sets,
		// tear it down and record the merger by joining the two sets
		if (roomSets.find(wall.first) != roomSets.find(wall.second)) {

			// We're tearing down a bottom/top wall
			if (wall.first.first == wall.second.first) {
				rooms[wall.first.second][wall.first.first].removeWalls(BOTTOM_WALL);
				rooms[wall.second.second][wall.second.first].removeWalls(TOP_WALL);
			}

			// We're tearing down a left/right wall
			else {
				rooms[wall.first.second][wall.first.first].removeWalls(RIGHT_WALL);
				rooms[wall.second.second][wall.second.first].removeWalls(LEFT_WALL);
			}

			roomSets.merge(wall.first, wall.second);
		}
	}
}