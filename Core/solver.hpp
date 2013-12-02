#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <vector>
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

		Solver(const std::vector<std::vector<double> >&, int, Selection, Croisement, Remplacement);

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
		void iteration();
		bool fin();
		
		Solution meilleureSol();
        Solution getBestSol();

	private:
		std::vector<std::vector<double> > distances;
		int taillePI;
		int nbIteration;
		bool arret;
		std::vector<Solution> population;
		std::vector<int> selection;
		Croisement tCroisement;
		Selection tSelection;
		Remplacement tRemplacement;
        Solution bestSol;
		double moyennePrec;

		void genererPI();
		inline bool presente(const std::vector<int>&, int) const;
		inline bool presente(const std::vector<Solution>&, const Solution&) const;

		template<typename T>
		static int getSecteurId(const std::vector<Secteur<T> >&, T);

		void remplacementStationnaire(const std::vector<Solution>&);
		void remplacementElitiste(const std::vector<Solution>&);

		double fitnessMoyen();
		bool critereArret();
};

#endif
