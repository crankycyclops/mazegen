#include <cstdlib> 
#include <ctime>
#include <memory>
#include <unordered_map>
#include <stdexcept>

#include "include/generator.h"
#include "include/generators/kruskal.h"
#include "include/generators/dfs.h"

// See comment above destructor definition in include/generator.h
Generator::~Generator() {}

std::unique_ptr<Generator> Generator::make(std::string type) {

	// Maps type names to their prototypical objects
	// Note: I can't use std::unique_ptr (yet) if I want to initialize this via
	// the constructor and curly braces. For an explanation of why, see:
	// https://stackoverflow.com/questions/47483791/c-map-brace-initialization-and-unique-ptr
	static std::unordered_map<std::string, std::shared_ptr<Generator>> prototypes({
		{"dfs", std::make_shared<DFS>()},
		{"kruskal", std::make_shared<Kruskal>()}
	});

	if (prototypes.end() != prototypes.find(type)) {
		return prototypes[type]->instantiate();
	} else {
		throw std::invalid_argument("undefined algorithm");
	}
}

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

	maze = std::make_unique<Maze>(width, height);

	// Randomly pick a starting room somewhere on the edge of the maze
	maze->start = getRandomEdgeRoom(maze);

	// Randomly pick a finishing room somewhere else on the edge of the maze
	do {
		maze->finish = getRandomEdgeRoom(maze);
	} while (maze->start == maze->finish);

	doGenerate(maze->rooms);
	return std::move(maze);
}
