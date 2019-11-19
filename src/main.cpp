#include <memory>
#include <cstdlib>
#include <iostream>
#include <string>
#include <stdexcept>

#include "include/maze.h"
#include "include/imagebuilder.h"
#include "include/generators/kruskal.h"

void printHelp() {

	std::cout << "\nUsage: mazegen <width> <height> <output filename>\n" << std::endl;
}

int main(int argc, char *argv[]) {

	int width;
	int height;
	std::string output;

	if (argc != 4) {
		printHelp();
		return EXIT_FAILURE;
	}

	try {
		width = std::stoi(argv[1]);
		height = std::stoi(argv[2]);
		output = argv[3];
	}

	catch (const std::invalid_argument &e) {
		printHelp();
		return EXIT_FAILURE;
	}

	if (width < 1 || height < 1) {
		std::cerr << "\nError: Invalid dimensions. Width and height must be greater than 0." << std::endl;
		printHelp();
		return EXIT_FAILURE;
	}

	ImageBuilder::initialize(argv);

	Kruskal generator;
	std::unique_ptr<Maze> maze = generator.generate(width, height);

	try {
		ImageBuilder img(maze);
		img.draw();
		img.save(output);
	}

	catch (const Magick::ErrorFileOpen &e) {
		std::cerr << "\nUnable to open " << output << ".\n" << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
