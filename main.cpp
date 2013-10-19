#include <iostream>
#include <vector>
#include <cstdlib>
#include "solver.hpp"
using namespace std;

int main(int argc, char **argv)
{
	if(argc == 1)
		return 1;

	/*int n = atoi(argv[1]);
	vector<string> villes(n);
	vector<vector<double> > distances(n);
	for(int i = 0; i < n; i++)
	{
		distances[i].resize(n, 0);
	}

	Solver S(villes, distances, n/2);
	S.afficher();
	*/

	Solver S(argv[1]);
	S.afficher();
	return 0;
}
