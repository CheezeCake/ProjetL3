#include <iostream>
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
	
	

