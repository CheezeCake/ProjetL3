#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
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

Solver::Solver(string nomFichier)
{
	ifstream flux(nomFichier.c_str());

	int nb, a, b;
	double dist;
	flux >> nb;
	taillePI = 10;

	population.resize(taillePI);
	distances.resize(nb);
	villes.resize(nb);

	for(int i = 0; i < nb; i++)
	{
		villes[i] = i;
		distances[i].resize(nb);
	}
	while(!flux.eof())
	{
		flux >> a;
		flux >> b;
		flux >> dist;
		distances[a][b] = dist;
		distances[b][a] = dist;
	}
	genererPI();
}

void Solver::genererPI()
{
	int N = villes.size();
	vector<int> parcours(N);
	int val;
	int i = 0;

	srand(time(NULL));

	while(i < taillePI)
	{
		vector<int> liste(N);
		for(int j = 0; j < N; j++)
			liste[j] = j;

		for(int j = 0; j < N; j++)
		{
			val = rand()%(N-j);
			parcours[j] = liste[val];
			liste.erase(liste.begin()+val);
		}

		if(!presente(parcours, i))
			population[i++] = Solution(parcours, distances);
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
