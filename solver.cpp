#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include <fstream>
#include "solver.hpp"
#include "config.hpp"

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

	vector<Secteur<double> > secteurs(N);
	for(int i = 0; i < N; i++)
		secteurs[i].indice = i;

	srand(time(NULL));

	secteurs[0].bi = 0;
	secteurs[0].bs = roundDistance(population[0].getScore());
	int id = 1;

	for(int i = 0; i < n; i++)
	{
		for(int j = id; j < N-i; j++)
		{
			int indice = secteurs[j].indice;
			secteurs[j].bi = secteurs[j-1].bs+DIST_MIN_NN;
			secteurs[j].bs = roundDistance(secteurs[j].bi+population[indice].getScore());
		}

		double dRand = (static_cast<double>(rand())/RAND_MAX)*secteurs.back().bs;
		dRand = roundDistance(dRand);

		id = getSecteurId(secteurs, dRand);
		selection[i] = secteurs[id].indice;
		secteurs.erase(secteurs.begin()+id);
	}
}

void Solver::selectionRang()
{
	int N = population.size();
	int n = N/2;

	selection.resize(n);

	vector<pair<int, Solution> > cpop(N);
	for(int i = 0; i < N; i++)
	{
		cpop[i].first = i;
		cpop[i].second = population[i];
	}

	sort(cpop.begin(), cpop.end(), cmp);

	vector<Secteur<int> > secteurs(N);
	for(int i = 0; i < N; i++)
		secteurs[i].indice = i;

	srand(time(NULL));

	secteurs[0].bi = 0;
	secteurs[0].bs = N;
	int id = 1;

	for(int i = 0; i < n; i++)
	{
		for(int j = id; j < N-i; j++)
		{
			int indice = secteurs[j].indice;
			secteurs[j].bi = secteurs[j-1].bs+1;
			secteurs[j].bs = secteurs[j].bi+N-indice;
		}

		int iRand = rand()%(secteurs.back().bs+1);

		id = getSecteurId(secteurs, iRand);
		selection[i] = secteurs[id].indice;
		secteurs.erase(secteurs.begin()+id);
	}
}

template<typename T>
int Solver::getSecteurId(const vector<Secteur<T> > &secteurs, T val)
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

double Solver::roundDistance(double v)
{
	int dixPn = pow(10.0, DECIMALES_DISTANCES);
	return (floor(v*dixPn+0.5)/dixPn);
}

bool Solver::cmp(const pair<int, Solution> &a, const pair<int, Solution> &b)
{
	return (a.second.getScore() < b.second.getScore());
}
