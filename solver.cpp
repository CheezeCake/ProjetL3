#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <set>
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

Solver::Solver(const string &nomFichier)
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

void Solver::selectionRoulette()
{
	int N = population.size();
	selection.resize(N/2);

	vector<int> bornesSup(N);
	bornesSup[0] = population[0].getScore()/N;
	for(int i = 0; i < N; i++)
		bornesSup[i] = (bornesSup[i-1]+population[i].getScore())/N;

	set<int> selectedSet;
	int i = 0;

	srand(time(NULL));

	while(i < N/2)
	{
		int v = getSecteurId(bornesSup, rand());

		if(selectedSet.insert(v).second)
			selection[i++] = v;
	}
}

int Solver::getSecteurId(const vector<int> &bornesSup, int val)
{
	int n = bornesSup.size();
	int d = 0;
	int f = n-1;
	int m;
	bool trouve = false;

	while(f >= d && !trouve)
	{
		m = (d+f)/2;
		int bi = (m == 0) ? 0 : bornesSup[m-1];

		if(val >= bi && val <= bornesSup[m])
			trouve = true;
		else if(bornesSup[m] > val)
			f = m-1;
		else
			d = m+1;
	}

	return trouve ? m : -1;
}
