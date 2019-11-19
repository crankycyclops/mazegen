#ifndef ROOM_H
#define ROOM_H

// Each wall is represented by a bit flag
constexpr int LEFT_WALL   = 0b1000;
constexpr int TOP_WALL    = 0b0100;
constexpr int RIGHT_WALL  = 0b0010;
constexpr int BOTTOM_WALL = 0b0001;
constexpr int ALL_WALLS = LEFT_WALL | TOP_WALL | RIGHT_WALL | BOTTOM_WALL;

class Room {

	protected:

		// Bit flags representing which walls are present
		int walls;

	public:

		/*
			Constructor

			Input:
				Whether or not to turn all walls on by default
		*/
		inline Room(bool addWallsByDefault = true) {

			// Turn all walls on by default
			if (addWallsByDefault) {
				addWalls(ALL_WALLS);
			} else {
				walls = 0;
			}
		}

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