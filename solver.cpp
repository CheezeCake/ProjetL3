#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "solver.hpp"

Solver::Solver(string *villes, int **distances, int N, int taillePI)
{
	this->N = N;
	this->taillePI = taillePI;
	this->villes = new string[N];
	this->distances = new int*[N];
	for(int i = 0; i < N; i++)
	{
		this->villes[i] = villes[i];
		
		this->distances[i] = new int[N];
		for(int j = 0; j < N; j++)
			this->distances[i][j] = distances[i][j];
	}

	population = NULL;
}

Solver::~Solver()
{
	for(int i = 0; i < N; i++)
		delete [] distances[i];

	if(population != NULL)
		delete [] population;

	delete [] villes;
	delete [] distances;
}

void Solver::genererPI()
{
	vector<int> liste(N);
	for(int i = 0; i < N; i++)
		liste[i] = i;
	
	
	srand(time(NULL));

	int i = 0;
	int val;
	int *parcours = new int[N];
	int j = 0;

	while(i < taillePI)
	{
		while(j < N)
		{
			val = rand()%(N-j-1);
			parcours[j] = liste[j];
			liste.erase(liste.begin()+j);
			j++;
		}

		if(!presente(parcours, i))
		{
			Solution s(parcours, N, *this);
			population[i] = s;
			i++;
		}
	}

	delete [] parcours;
}

bool Solver::presente(int *parcours, int n)
{
	Solution s(parcours, N, *this);
	for(int i = 0; i < n; i++)
	{
		if(population[i] == s)
			return true;
	}

	return false;
}
