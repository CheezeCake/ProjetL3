#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "solver.hpp"

using namespace std;

Solver::Solver(const vector<string> &villes, const vector<vector<int> > &distances, int N, int taillePI)
{
	this->N = N;
	this->taillePI = taillePI;
	this->villes = villes;
	this->distances = distances;

	population.resize(taillePI);
}

void Solver::genererPI()
{
	vector<int> liste(N);
	for(int i = 0; i < N; i++)
		liste[i] = i;
	
	srand(time(NULL));

	vector<int> parcours(N);
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
	{
		population[i].afficher();
	}
}

bool Solver::presente(const vector<int> &parcours, int n) const
{
	Solution s(parcours, N, distances);
	for(int i = 0; i < n; i++)
	{
		//if(population[i] == parcours)
		if(population[i] == s)
			return true;
	}

	return false;
}
