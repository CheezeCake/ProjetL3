#ifndef	SOLVER_HPP
#define SOLVER_HPP

#include <vector>
#include <string>
#include "solution.hpp"

class Solver
{
	private:
		std::vector<std::string> villes;
		std::vector<std::vector<double> > distances;
		int taillePI;
		std::vector<Solution> population;

		void genererPI();
		bool presente(const std::vector<double>&, int) const;

	public:
		Solver(const std::vector<std::string>&, const std::vector<std::vector<double> >&, int);
		void afficher() const;
};

#endif
