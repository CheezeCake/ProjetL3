#include <iostream>
#include "solution.hpp"
using namespace std;

Solution::Solution(int* parcours, int N, Solver &S)
{
	this->N = N;
	
	this->parcours = new int[N];

	for(int i = 0; i < N; i++)
		this->parcours[i] = parcours[i];

	fitness(S);
}

void Solution::fitness(Solver &S)
{
	for(int i = 0; i < N-1; i++)
		 score += S.getDistance(parcours[i], parcours[i+1]);
}

Solution::Solution()
{
	delete [] parcours;
}
