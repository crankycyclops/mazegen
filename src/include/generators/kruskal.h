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

	public:

		/*
			Creates and returns a new instance of Kruskal.

			Input:
				(none)

			Ouput:
				Pointer to Generator instance (std::unique_ptr<Generator>)
		*/
		virtual std::unique_ptr<Generator> instantiate() const;
};

#endif