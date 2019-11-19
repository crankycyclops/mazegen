#include "include/imagebuilder.h"

void ImageBuilder::initialize(char **argv) {

	Magick::InitializeMagick(*argv);
}

ImageBuilder::ImageBuilder(std::unique_ptr<Maze> &m) {

	maze = m.get();

	// TODO: make these configurable
	roomColor = Magick::Color(0, RGBVal(100), RGBVal(255), 0);
	startRoomColor = Magick::Color(0, RGBVal(255), RGBVal(50), 0);
	finishRoomColor = Magick::Color(RGBVal(255), RGBVal(50), 0, 0);
	wallColor = Magick::Color(0, 0, 0, 0);

	image = Magick::Image(Magick::Geometry(
		maze->getWidth() * roomWidth + (wallThickness * (maze->getWidth() + 1)),
		maze->getHeight() * roomHeight + (wallThickness * (maze->getHeight() + 1))
	), roomColor);
}

void ImageBuilder::draw() {

	// TODO: potential optimization: adjascent rooms have left/right wall pairs
	// that are identical, so I really only need to draw those once, not twice.
	for (int y = 0; y < maze->getHeight(); y++) {
		for (int x = 0; x < maze->getWidth(); x++) {

			const Room &room = maze->getRoom(x, y);
			int walls = room.getWalls();

			if (&maze->getStart() == &room) {
				for (int roomY = 0; roomY < roomHeight + wallThickness; roomY++) {
					for (int roomX = 0; roomX < roomWidth + wallThickness; roomX++) {
						image.pixelColor(roomX + x * (roomWidth + wallThickness), roomY + y * (roomHeight + wallThickness), startRoomColor);
					}
				}
			}

			else if (&maze->getFinish() == &room) {
				for (int roomY = 0; roomY < roomHeight + wallThickness; roomY++) {
					for (int roomX = 0; roomX < roomWidth + wallThickness; roomX++) {
						image.pixelColor(roomX + x * (roomWidth + wallThickness), roomY + y * (roomHeight + wallThickness), finishRoomColor);
					}
				}
			}

			if (LEFT_WALL & walls) {
				for (int wallY = 0; wallY < roomHeight + 2 * wallThickness; wallY++) {
					for (int t = 0; t < wallThickness; t++) {
						image.pixelColor(x * (roomWidth + wallThickness) + wallThickness - t - 1, wallY + y * (roomHeight + wallThickness), wallColor);
					}
				}
			}

			if (TOP_WALL & walls) {
				for (int wallX = 0; wallX < roomWidth + 2 * wallThickness; wallX++) {
					for (int t = 0; t < wallThickness; t++) {
						image.pixelColor(wallX + x * (roomWidth + wallThickness), y * (roomHeight + wallThickness) + wallThickness - t - 1, wallColor);
					}
				}
			}

			if (RIGHT_WALL & walls) {
				for (int wallY = 0; wallY < roomHeight + 2 * wallThickness; wallY++) {
					for (int t = 0; t < wallThickness; t++) {
						image.pixelColor(x * (roomWidth + wallThickness) + roomWidth + (2 * wallThickness) - t - 1, wallY + y * (roomHeight + wallThickness), wallColor);
					}
				}
			}

			if (BOTTOM_WALL & walls) {
				for (int wallX = 0; wallX < roomWidth + 2 * wallThickness; wallX++) {
					for (int t = 0; t < wallThickness; t++) {
						image.pixelColor(wallX + x * (roomWidth + wallThickness), y * (roomHeight + wallThickness) + roomHeight + (2 * wallThickness) - t - 1, wallColor);
					}
				}
			}
		}
	}
}

void ImageBuilder::save(std::string filename) {

	image.write(filename);
}