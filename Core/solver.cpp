#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <fstream>
#include <algorithm>
#include "solver.hpp"
#include "rand.hpp"
#include "config.hpp"

using namespace std;

Solver::Solver(const vector<string> &villes, const vector<vector<double> > &distances, int taillePI, Selection selec, Croisement crois, Remplacement remp)
{
	this->taillePI = taillePI;
	this->villes = villes;
	this->distances = distances;

	population.resize(taillePI);
	tSelection = selec;
	tCroisement = crois;
	tRemplacement = remp;

	genererPI();
	moyennePrec = fitnessMoyen();
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
	int i = 0;

	while(i < taillePI)
	{
		for(int j = 0; j < N; j++)
			parcours[j] = j;

		int (*gen)(int) = Rand::randi;
		random_shuffle(parcours.begin()+1, parcours.end(), gen);

		if(!presente(parcours, i))
			population[i++] = Solution(parcours, distances);
	}
}

void Solver::afficher()
{
	for(int i = 0; i < taillePI; i++)
		population[i].afficher();
	cout << endl << "----Meilleure solution----" << endl;
	population[meilleureSol()].afficher();
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

	sort(population.begin(), population.end());

	vector<Secteur<int> > secteurs(N);
	for(int i = 0; i < N; i++)
		secteurs[i].indice = i;

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
	return (floor(v*DIX_P_DECIMALES+0.5)/DIX_P_DECIMALES);
}

bool Solver::presente(const vector<Solution> &V, const Solution &s) const
{
	int taille = V.size();
	for(int i = 0; i < taille; i++)
	{
		if(V[i] == s)
			return true;
	}
	return false;
}

void Solver::reproduction()
{
	int taille = selection.size();
	int moitie = taille/2;
	vector<Solution> enfants;
	Solution temp1, temp2;
	int k = Rand::randi(2, distances.size()-1);

	for(int i = 0; i < moitie; i += 2)
	{
		if(tCroisement == SLICING)
			population[selection[i]].slicingCrossover(population[selection[i+1]], temp1, temp2);
		else if(tCroisement == KSLICING)
			population[selection[i]].slicingCrossover(k, population[selection[i+1]], temp1, temp2);
		
		temp1.calculerScore(distances);
		temp2.calculerScore(distances);

		if(!presente(enfants, temp1))
			enfants.push_back(temp1);
		if(!presente(enfants, temp2))
			enfants.push_back(temp2);
	}
	
	for(int i = moitie; i < taille; i++)
	{
		population[selection[i]].mutation(temp1);
		temp1.calculerScore(distances);

		if(!presente(enfants, temp1))
			enfants.push_back(temp1);
	}
	remplacement(enfants);
}

void Solver::remplacement(const vector<Solution> &enfants)
{
	if(tRemplacement == STATIONNAIRE)
		remplacementStationnaire(enfants);
	else
		remplacementElitiste(enfants);
}

void Solver::remplacementStationnaire(const vector<Solution> &enfants)
{
	int N = enfants.size();
	int taille = selection.size();
	int i = 0;
	int y = 0;

	while(i < N && y < taille)
	{
		if(!presente(population, enfants[i]))
		{
			population[selection[y]] = enfants[i];
			y++;
		}
		i++;
	}	
}

void Solver::remplacementElitiste(const vector<Solution> &enfants)
{
	int N = population.size();
	int n = enfants.size();

	population.reserve(n+N);

	for(int i = 0; i < n; i++)
	{
		if(!presente(population, enfants[i]))
			population.push_back(enfants[i]);
	}

	sort(population.begin(), population.end());
	population.resize(N);
}

double Solver::fitnessMoyen()
{
	int temp = 0;
	int taille = population.size();
	for(int i = 0; i < taille; i++)
		temp += population[i].getScore();
	return (temp/taille);
}

void Solver::iteration()
{
	if(tSelection == ROULETTE)
		selectionRoulette();

	else if(tSelection == RANG)
		selectionRang();

	else if(tSelection == TOURNOI)
		selectionTournoi();

	else
		selectionElitisme();

	reproduction();
}

void Solver::resoudre()
{
	double temp = moyennePrec;
	bool ok = true;
	const int min = 5;
	int i = 0;

	while(ok || i < min)
	{
		iteration();
		moyennePrec = fitnessMoyen();
		temp *= 0.9;

		if(temp < moyennePrec)
			ok = false;
		else
			temp = moyennePrec;
		i++;
	}
}

int Solver::meilleureSol()
{
	int N = population.size();
	double min = population[0].getScore();
	int meilleure = 0;
	double temp;
	for(int i = 1; i < N; i++)
	{
		temp = population[i].getScore();
		if(temp < min)
		{
			min = temp;
			meilleure = i;
		}
	}
	return meilleure;
}
