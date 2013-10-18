#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "solver.hpp"

using namespace std;

Solver::Solver(const vector<string> &villes, const vector<vector<double> > &distances, int taillePI)
{
	this->taillePI = taillePI;
	this->villes = villes;
	this->distances = distances;

	population.resize(taillePI);
	genererPI();
}

void Solver::genererPI()
{
	int N = villes.size();
	vector<int> liste(N);
	for(int i = 0; i < N; i++)
		liste[i] = i;
	
	srand(time(NULL));

	vector<double> parcours(N);
	int i = 0;
	int j, val;

	while(i < taillePI)
	{
		j = 0;
		while(j < N)
		{
			val = rand()%(N-j-1);
			parcours[j] = liste[val];
			liste.erase(liste.begin()+j);
			j++;
		}

		if(!presente(parcours, i))
		{
			population[i] = Solution(parcours, N, distances);
			i++;
		}
	}
}

void Solver::afficher() const
{
	for(int i = 0; i < taillePI; i++)
		population[i].afficher();
}

bool Solver::presente(const vector<double> &parcours, int n) const
{
	for(int i = 0; i < n; i++)
	{
		if(population[i] == parcours)
			return true;
	}

	return false;
}
