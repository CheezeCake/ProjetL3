#include <iostream>
#include "solution.hpp"
using namespace std;

Solution::Solution()
{
	score = 0;
}

Solution::Solution(const vector<int> &parcours, const vector<vector<double> > &distances)
{
	this->parcours = parcours;
	score = 0;

	int N = parcours.size();
	for(int i = 0; i < N-1; i++)
		score += distances[parcours[i]][parcours[i+1]];
}

bool Solution::operator==(const Solution &s) const
{
	int N = parcours.size();
	if(score != s.score || N != s.parcours.size())
		return false;

	for(int i = 0; i < N; i++)
	{
		if(parcours[i] != s.parcours[i])
			return false;
	}

	return true;
}

void Solution::afficher() const
{
	int taille = parcours.size();
	for(int i = 0; i < taille-1; i++)
	{
		cout << parcours[i] << " -> ";
	}
	cout << parcours[taille-1] << endl;
}

bool Solution::operator==(const vector<int> &parcours) const
{
	if(this->parcours.size() != parcours.size())
		return false;

	int N = this->parcours.size();
	for(int i = 0; i < N; i++)
	{
		if(this->parcours[i] != parcours[i])
			return false;
	}

	return true;
}
