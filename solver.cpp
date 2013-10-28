#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include <fstream>
#include <algorithm>
#include "solver.hpp"
#include "rand.hpp"
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
	int N = distances.size();
	vector<int> parcours(N);
	int val;
	int i = 0;

	while(i < taillePI)
	{
		vector<int> liste(N-1);
		for(int j = 0; j < N-1; j++)
			liste[j] = j+1;

		parcours[0] = 0;
		for(int j = 0; j < N-1; j++)
		{
			val = Rand::randi(N-j-1);
			parcours[j+1] = liste[val];
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

void Solver::afficherSelection() const
{
	int taille = selection.size();
	for(int i = 0; i < taille; i++)
	{
		population[selection[i]].afficher();
	}
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

	double maxDistance = max_element(population.begin(),
	                                 population.end())->getScore()+DIST_MIN_NN;
	int id = 0;
	for(int i = 0; i < n; i++)
	{
		for(int j = id; j < N-i; j++)
		{
			int indice = secteurs[j].indice;
			secteurs[j].bi = (j == 0) ? 0 : secteurs[j-1].bs+DIST_MIN_NN;
			secteurs[j].bs = secteurs[j].bi+maxDistance-population[indice].getScore();
		}

		double dRand = (static_cast<double>(Rand::randi())/RAND_MAX)*secteurs.back().bs;
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
		secteurs[i].indice = cpop[i].first;

	int id = 0;
	for(int i = 0; i < n; i++)
	{
		for(int j = id; j < N-i; j++)
		{
			secteurs[j].bi = (j == 0) ? 0 : secteurs[j-1].bs+1;
			secteurs[j].bs = secteurs[j].bi+N-j-i;
		}

		int iRand = Rand::randi(secteurs.back().bs+1);

		id = getSecteurId(secteurs, iRand);
		selection[i] = secteurs[id].indice;
		secteurs.erase(secteurs.begin()+id);
	}
}

void Solver::selectionTournoi()
{
	int N = population.size();
	int n;
	if( N % 2 == 0) n = N/2;
	else n = (N-1)/2;
	selection.resize(n);
	int choix, min;

	for(int i = 0; i < n; i++)
	{
		min = population[i].getScore();
		choix = i;
		if(population[i+n].getScore() < min)
			choix = i + n;
		selection[i] = choix;
	}
}

void Solver::selectionElitisme()
{
	int N = population.size();
	int taille = N/2;
	vector<bool>select(N);
	int max = 0;
	for(int j = 0; j < N; j++)
	{
		select[j] = false;
		if(population[j].getScore() > max)
			max = population[j].getScore();
	}
	int i = 0;
	int choix = 0;


	int min = population[i].getScore();
	selection.resize(taille);

	while(i < taille)
	{
		min = max;
		for(int y = 0; y < N; y++)
		{
			if(!select[y])
			{
				if(population[y].getScore() < min)
				{
					min = population[y].getScore();
					choix = y;
				}
			}
		}
		select[choix] = true;
		selection[i] = choix;
		i++;
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
	return (a.second < b.second);
}
