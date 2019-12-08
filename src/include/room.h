#ifndef ROOM_H
#define ROOM_H

#include <utility>

// Each wall is represented by a bit flag
constexpr int LEFT_WALL   = 0b1000;
constexpr int TOP_WALL    = 0b0100;
constexpr int RIGHT_WALL  = 0b0010;
constexpr int BOTTOM_WALL = 0b0001;
constexpr int ALL_WALLS = LEFT_WALL | TOP_WALL | RIGHT_WALL | BOTTOM_WALL;

class Room {

	private:

		// The room's (x, y) coordinates
		std::pair<int, int> coordinates;

	protected:

		// Bit flags representing which walls are present
		int walls;

	public:

		/*
			Constructor

			Input:
				Whether or not to turn all walls on by default
		*/
		inline Room(std::pair<int, int> c, bool addWallsByDefault = true):
		coordinates(c), walls(0) {

			// Turn all walls on by default
			if (addWallsByDefault) {
				addWalls(ALL_WALLS);
			}
		}

		/*
			Returns the room's X and Y coordinates.

			Input:
				(none)

			Output:
				X and Y coordinates (std::pair<int, int>)
		*/
		inline const std::pair<int, int> getCoordinates() const {return coordinates;}

		/*
			Returns the room's wall flags.

			Input:
				(none)

			Output:
				Wall flags (const int)
		*/
		inline const int getWalls() const {return walls;}

		/*
			Turns on the specified walls.

			Input:
				Wall flags (int)

			Output:
				(none)
		*/
		inline void addWalls(int wallFlags) {

			walls |= wallFlags;
		}

		/*
			Turns off the specified walls.

			Input:
				Wall flags (int)

			Output:
				(none)
		*/
		inline void removeWalls(int wallFlags) {

			walls &= ~wallFlags;
		}
};

#endif
