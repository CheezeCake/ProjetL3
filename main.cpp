#include <iostream>
#include <vector>
#include "solver.hpp"
using namespace std;

int main()
{
	vector<string> villes(6);
	vector<vector<double> > distances(6);
	for(int i = 0; i < 6; i++)
	{
		distances[i].resize(6, 0);
	}

	villes[0] = "Marseille";
	villes[1] = "Paris";
	villes[2] = "Avignon";
	villes[3] = "Lille";
	villes[4] = "Lyon";
	villes[5] = "Loriol";

	distances[0][1] = 500;
	distances[0][2] = 100;
	distances[0][3] = 1000;
	distances[0][4] = 300;
	distances[0][5] = 150;

	distances[1][0] = 500;
	distances[1][2] = 400;
	distances[1][3] = 200;
	distances[1][4] = 300;
	distances[1][5] = 450;
	
	distances[2][0] = 100;
	distances[2][1] = 400;
	distances[2][3] = 500;
	distances[2][4] = 450;
	distances[2][5] = 100;

	Solver S(villes, distances, 5);
	S.afficher();

	return 0;
}
