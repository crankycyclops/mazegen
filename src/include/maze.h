#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include "room.h"

class Maze {

	protected:

		int width;
		int height;

		Room *start = nullptr;
		Room *finish = nullptr;

		// 2D vector representing grid of "rooms"
		std::vector<std::vector<Room>> rooms;

		// Generator will need to access our members to actually build the
		// maze
		friend class Generator;

	public:

		/*
			Constructor

			Input:
				Width (int)
				Height (int)
				Whether or not to add walls to each "room" by default (bool)
		*/
		Maze() = delete;
		Maze(int width, int height, bool addWallsByDefault = true);

		/*
			Returns the width of the maze

			Input:
				(none)

			Output:
				Width (const int)
		*/
		inline const int getWidth() const {return width;}

		/*
			Returns the height of the maze

			Input:
				(none)

			Output:
				Height (const int)
		*/
		inline const int getHeight() const {return height;}

		/*
			Returns a const reference to the start and finishing rooms.

			Input:
				(none)

			Output:
				const Room &
		*/
		inline const Room &getStart() const {return *start;}
		inline const Room &getFinish() const {return *finish;}

		/*
			Returns a const reference to the Room at the specified 2D index.

			Input:
				X coordinate (int)
				Y coordinate (int)

			Output:
				const Room &
		*/
		inline const Room &getRoom(int x, int y) const {return rooms[y][x];}
};

#endif