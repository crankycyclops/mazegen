#include <string>
#include <memory>
#include <Magick++.h>

#include "maze.h"

// Allows color components to be expressed in a range from 0 - FF regardless
// of how ImageMagick was compiled
constexpr int MAX_RGB_SCALE = MaxRGB / 256;

// Transforms color components ranging from 0 - FF into a value ImageMagick
// understands
constexpr int RGBVal(int component) {

	return component * MAX_RGB_SCALE;
}

class ImageBuilder {

	protected:

		// How many pixels of width each room uses in the image
		int roomWidth = 20;

		// How many pixels of height each room uses in the image
		int roomHeight = 20;

		// How many pixels thick the walls should be drawn
		int wallThickness = 5;

		// The colors we use to paint rooms
		Magick::Color roomColor;
		Magick::Color startRoomColor;
		Magick::Color finishRoomColor;

		// The color we use to paint walls
		Magick::Color wallColor;

		// The maze we're going to draw
		Maze *maze;

		// The resulting image
		Magick::Image image;

	public:

		/*
			Initializes the Image Builder. Should only be called once.

			Input:
				Command line arguments (const char **)

			Output:
				(none)
		*/
		static void initialize(char **argv);

		/*
			Constructor
		*/
		ImageBuilder(std::unique_ptr<Maze> &m);

		/*
			Draws an image of the Maze.

			Input:
				(none)

			Output:
				(none)
		*/
		void draw();

		/*
			Saves the image to a file. The format of the file is determined
			by the file extension.

			Input:
				Filename (string)

			Output:
				(none)
		*/
		void save(std::string filename);
};