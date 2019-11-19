#ifndef GENERATOR_H
#define GENERATOR_H

#include <vector>
#include <utility>
#include <memory>

#include "maze.h"

// Represents a pair of room coordinates (essentially a means to label walls.)
// First value of each pair is x, second value of each pair is y.
struct RoomIndexPair {
	std::pair<int, int> first;
	std::pair<int, int> second;
};

class Generator {

	private:

		/*
			Returns a random room from the edge of the maze.

			Input:
				Reference to the maze's pointer

			Output:
				Pointer to the randomly selected room (Room *)
		*/
		Room *getRandomEdgeRoom(std::unique_ptr<Maze> &maze);

	protected:

		// Maze object that we're going to be operating on
		std::unique_ptr<Maze> maze;

		/*
			Specific maze generation algorithm.

			Input:
				2D vector of maze's rooms

			Output:
				(none)
		*/
		virtual void doGenerate(std::vector<std::vector<Room>> &rooms) = 0;

	public:

		/*
			Generates a maze of the specified width and height.

			Input:
				Width (int)
				Height (int)

			Ouput:
				Maze (Maze)
		*/
		std::unique_ptr<Maze> generate(int width, int height);
};

#endif
