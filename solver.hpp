#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <vector>
#include <string>
#include "solution.hpp"

template<typename T>
struct Secteur
{
	T bi;
	T bs;
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
		inline bool presente(const std::vector<int>&, int) const;
		static bool cmp(const std::pair<int, Solution>&, const std::pair<int, Solution>&);

		template<typename T>
		static int getSecteurId(const std::vector<Secteur<T> >&, T);

	public:
		Solver(const std::vector<std::string>&, const std::vector<std::vector<double> >&, int);
		Solver(const std::string&);

		void afficher() const;
		void afficherSelection() const;
		void selectionRoulette();
		void selectionRang();
		void selectionTournoi();
		void selectionElitisme();

		static inline double roundDistance(double);
};

#endif
