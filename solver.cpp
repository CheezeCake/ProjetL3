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
	int n = N/2;

	selection.resize(n);

	vector<Secteur> secteurs(N);
	secteurs[0].bi = 0;
	secteurs[0].bs = population[0].getScore()/N;
	secteurs[0].indice = 0;

	for(int i = 1; i < N; i++)
	{
		secteurs[i].bi = secteurs[i-1].bs+1;
		secteurs[i].bs = secteurs[i].bi+(population[i].getScore()/N);
		secteurs[i].indice = i;
	}

	srand(time(NULL));

	for(int i = 0; i < n; i++)
	{
		int id = getSecteurId(secteurs, rand()%(secteurs.back().bs+1));
		selection[i] = secteurs[id].indice;
		secteurs.erase(secteurs.begin()+id);
	}
}

int Solver::getSecteurId(const vector<Secteur> &secteurs, int val)
{
	int d = 0;
	int f = secteurs.size()-1;
	int m = 0;
	bool trouve = false;

	while(f >= d && !trouve)
	{
		m = (d+f)/2;

		if(secteurs[m].bi > val)
			f = m-1;
		else if(secteurs[m].bs < val)
			d = m+1;
		else
			trouve = true;
	}

	return m;
}
