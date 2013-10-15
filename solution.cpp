#include <iostream>
#include "solution.hpp"
using namespace std;

Solution::Solution()
{
	N = 0;
	score = 0;
}

Solution::Solution(const vector<int> &parcours, int N, const vector<vector<int> > &distances)
{
	this->N = N;
	this->parcours = parcours;

	score = 0;
	for(int i = 0; i < N-1; i++)
		score += distances[parcours[i]][parcours[i+1]];
}

bool Solution::operator==(const Solution &s) const
{
	if(score != s.score || N != s.N)
		return false;

	for(int i = 0; i < N; i++)
	{
		if(parcours[i] != s.parcours[i])
			return false;
	}

	return true;
}

bool Solution::operator==(const vector<int> &parcours) const
{
	if(N != parcours.size())
		return false;

	for(int i = 0; i < N; i++)
	{
		if(this->parcours[i] != parcours[i])
			return false;
	}

	return true;
}
