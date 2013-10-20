#ifndef	SOLVER_HPP
#define SOLVER_HPP

#include <vector>
#include <string>
#include "solution.hpp"

struct Secteur
{
	int bi;
	int bs;
	int indice;
};

class Solver
{
	private:
		std::vector<std::string> villes;
		std::vector<std::vector<double> > distances;
		int taillePI;
		std::vector<Solution> population;
		std::vector<int> selection;

		void genererPI();
		bool presente(const std::vector<int>&, int) const;
		static int getSecteurId(const std::vector<Secteur>&, int);

	public:
		Solver(const std::vector<std::string>&, const std::vector<std::vector<double> >&, int);
		Solver(const std::string &);

		void afficher() const;
		void selectionRoulette();
		void selectionRang();
		void selectionTournoi();
		void selectionElitisme();
};

#endif
