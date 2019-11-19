#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "../generator.h"

class Kruskal: public Generator {

	protected:

		/*
			Implements maze generation using Kruskal's algorithm.

			Input:
				2D vector of maze's rooms

			Ouput:
				(none)
		*/
		virtual void doGenerate(std::vector<std::vector<Room>> &rooms);
};

#endif