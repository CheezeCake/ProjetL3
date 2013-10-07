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
		int taillePI;
		Solution *population;

		void genererPI();

	public:
		Solver(std::string*, int**, int, int);
		~Solver();

};

#endif
