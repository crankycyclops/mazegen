#include <memory>
#include <cstdlib>
#include <iostream>
#include <string>
#include <stdexcept>

#include "include/maze.h"
#include "include/imagebuilder.h"
#include "include/generators/kruskal.h"
#include "include/generators/dfs.h"

void printHelp() {

	std::cout << "\nUsage: mazegen <width> <height> <algorithm> <output filename>" << std::endl;
	std::cout << "Valid algorithms (case sensitive): \"dfs\", \"kruskal\"\n" << std::endl;
}

int main(int argc, char *argv[]) {

	int width;
	int height;
	std::string algorithm;
	std::string output;

	if (argc != 5) {
		printHelp();
		return EXIT_FAILURE;
	}

	try {
		width = std::stoi(argv[1]);
		height = std::stoi(argv[2]);
		algorithm = argv[3];
		output = argv[4];
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

	std::unique_ptr<Maze> maze;

	if (0 == algorithm.compare("kruskal")) {
		Kruskal generator;
		maze = generator.generate(width, height);
	}

	else if (0 == algorithm.compare("dfs")) {
		DFS generator;
		maze = generator.generate(width, height);
	}

	else {
		std::cerr << "\nError: Undefined algorithm." << std::endl;
		printHelp();
		return EXIT_FAILURE;
	}

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
