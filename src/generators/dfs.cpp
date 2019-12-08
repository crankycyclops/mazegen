#include <algorithm>
#include "../include/generators/dfs.h"

std::unique_ptr<Generator> DFS::instantiate() const {

	return std::make_unique<DFS>();
}

std::vector<std::pair<int, int>> DFS::getUnvisitedNeighbors(std::pair<int, int> room) {

	std::vector<std::pair<int, int>> unvisitedNeighbors;

	for (auto neighbor: neighbors[room]) {
		if (visited.end() == visited.find(neighbor)) {
			unvisitedNeighbors.push_back(neighbor);
		}
	}

	return unvisitedNeighbors;
}

void DFS::doGenerate(std::vector<std::vector<Room>> &rooms) {

	const unsigned width = maze->getWidth();
	const unsigned height = maze->getHeight();
	const unsigned numRooms = width * height;

	for (unsigned y = 0; y < height; y++) {
		for (unsigned x = 0; x < width; x++) {

			// Construct a list of neighbors for each room
			if (neighbors.end() == neighbors.find({x, y})) {
				neighbors[{x, y}] = {};
			}

			if (y > 0) {
				neighbors[{x, y}].push_back({x, y - 1});
			}

			if (y < height - 1) {
				neighbors[{x, y}].push_back({x, y + 1});
			}

			if (x > 0) {
				neighbors[{x, y}].push_back({x - 1, y});
			}

			if (x < width - 1) {
				neighbors[{x, y}].push_back({x + 1, y});
			}

			// Ensure we select neighbors in a random order
			std::random_shuffle(neighbors[{x, y}].begin(), neighbors[{x, y}].end());
		}
	}

	curRoom = maze->getStart().getCoordinates();
	visited.insert(curRoom);

	// Continue building the maze until we have no unvisited rooms left
	while (visited.size() < numRooms) {

		std::vector<std::pair<int, int>> unvisitedNeighbors =
			getUnvisitedNeighbors(curRoom);

		if (unvisitedNeighbors.size()) {

			std::pair<int, int> neighbor = unvisitedNeighbors.back();
			unvisitedNeighbors.pop_back();

			if (unvisitedNeighbors.size()) {
				roomStack.push_back(curRoom);
			}

			// We're tearing down a top/bottom wall
			if (curRoom.first == neighbor.first) {
				if (curRoom.second < neighbor.second) {
					rooms[curRoom.second][curRoom.first].removeWalls(BOTTOM_WALL);
					rooms[neighbor.second][neighbor.first].removeWalls(TOP_WALL);
				} else {
					rooms[curRoom.second][curRoom.first].removeWalls(TOP_WALL);
					rooms[neighbor.second][neighbor.first].removeWalls(BOTTOM_WALL);
				}
			}

			// We're tearing down a left/right wall
			else {
				if (curRoom.first < neighbor.first) {
					rooms[curRoom.second][curRoom.first].removeWalls(RIGHT_WALL);
					rooms[neighbor.second][neighbor.first].removeWalls(LEFT_WALL);
				} else {
					rooms[curRoom.second][curRoom.first].removeWalls(LEFT_WALL);
					rooms[neighbor.second][neighbor.first].removeWalls(RIGHT_WALL);
				}
			}

			visited.insert(neighbor);
			curRoom = neighbor;
		}

		else if (roomStack.size()) {

			std::pair<int, int> nextRoom({-1, -1});

			while (roomStack.size()) {

				nextRoom = roomStack.back();
				roomStack.pop_back();

				std::vector<std::pair<int, int>> unvisitedNeighbors =
					getUnvisitedNeighbors(nextRoom);

				if (unvisitedNeighbors.size()) {
					break;
				}
			}

			if (nextRoom.first >= 0) {
				curRoom = nextRoom;
			}
		}
	}
}
