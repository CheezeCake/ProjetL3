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

	vector<int> parcours(N);
	int i = 0;
	int val;

	while(i < taillePI)
	{
		for(int j = 0; j < N; j++)
		{
			val = rand()%(N-j);
			parcours[j] = liste[val];
			liste.erase(liste.begin()+val);
		}

		for(int k = 0; k < N; k++)
			cout << parcours[k] << " ";
		cout << endl;

		if(!presente(parcours, i))
		{
			population[i] = Solution(parcours, distances);
			i++;
			cout << "new sol ds pop: ";
			population[i].afficher();
		}
	}
}

void Solver::afficher() const
{
	for(int i = 0; i < taillePI; i++)
		population[i].afficher();
}

bool Solver::presente(const vector<int> &parcours, int n) const
{
	for(int i = 0; i < n; i++)
	{
		if(population[i] == parcours)
			return true;
	}

	return false;
}
