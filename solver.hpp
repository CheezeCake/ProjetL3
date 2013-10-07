#ifndef	SOLVER_HPP
#define SOLVER_HPP

#include <string>
#include "solution.hpp"

class Solver
{
	private:
		std::string *villes;
		int **distances;
		int N;

		Solution *population;

	public:
		Solver();
		Solver(std::string*, int**, int);
		~Solver();
};

#endif
