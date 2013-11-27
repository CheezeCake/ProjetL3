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
	public:
		enum Croisement { SLICING, KSLICING };
		enum Selection { ROULETTE, RANG, TOURNOI, ELITISME };
		enum Remplacement { STATIONNAIRE, ELITISTE };

		Solver(const std::vector<std::string>&, const std::vector<std::vector<double> >&, int, Selection, Croisement, Remplacement);
		Solver(const std::string&);

		void afficher();
		void afficherSelection() const;
		void selectionRoulette();
		void selectionRang();
		void selectionTournoi();
		void selectionElitisme();
		void reproduction();
		void remplacement(const std::vector<Solution>&);

		static inline double roundDistance(double);

		void resoudre();
		
		int meilleureSol();

	private:
		std::vector<std::string> villes;
		std::vector<std::vector<double> > distances;
		int taillePI;
		std::vector<Solution> population;
		std::vector<int> selection;
		Croisement tCroisement;
		Selection tSelection;
		Remplacement tRemplacement;
		double moyennePrec;

		void genererPI();
		inline bool presente(const std::vector<int>&, int) const;
		inline bool presente(const std::vector<Solution>&, const Solution&) const;

		template<typename T>
		static int getSecteurId(const std::vector<Secteur<T> >&, T);

		void remplacementStationnaire(const std::vector<Solution>&);
		void remplacementElitiste(const std::vector<Solution>&);

		double fitnessMoyen();
		void iteration();
};

#endif
