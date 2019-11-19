#include <cstdlib> 
#include <ctime>
#include <memory>

#include "include/generator.h"

Room *Generator::getRandomEdgeRoom(std::unique_ptr<Maze> &maze) {

	srand((unsigned int)time(0));

	switch (rand() % 4) {

		// Start on the left
		case 0:
			return &maze->rooms[rand() % maze->height][0];

		// Start on the top
		case 1:
			return &maze->rooms[0][rand() % maze->width];

		// Start on the right
		case 2:
			return &maze->rooms[rand() % maze->height][maze->width - 1];

		// Start on the bottom
		default:
			return &maze->rooms[maze->height - 1][rand() % maze->width];
	}
}

std::unique_ptr<Maze> Generator::generate(int width, int height) {

	std::unique_ptr<Maze> maze = std::make_unique<Maze>(width, height);

	// Randomly pick a starting room somewhere on the edge of the maze
	maze->start = getRandomEdgeRoom(maze);

	// Randomly pick a finishing room somewhere else on the edge of the maze
	do {
		maze->finish = getRandomEdgeRoom(maze);
	} while (maze->start == maze->finish);

	doGenerate(maze->rooms);
	return maze;
}
