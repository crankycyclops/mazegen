#include "include/maze.h"

Maze::Maze(int w, int h, bool addWallsByDefault): width(w), height(h) {

	for (int y = 0; y < height; y++) {

		rooms.push_back(std::vector<Room>());

		for (int x = 0; x < width; x++) {
			rooms[y].push_back(Room({x, y}, addWallsByDefault));
		}
	}
}
