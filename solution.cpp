#include <iostream>
#include "rand.hpp"
#include "solution.hpp"
using namespace std;

Solution::Solution()
{
	score = 0;
}

Solution::Solution(const vector<int> &parcours, const vector<vector<double> > &distances)
{
	this->parcours = parcours;
	calculerScore(distances);
}

double Solution::getScore() const
{
	return score;
}

void Solution::calculerScore(const std::vector<std::vector<double> > &distances)
{
	int N = parcours.size();

	score = 0;
	for(int i = 0; i < N-1; i++)
		score += distances[parcours[i]][parcours[i+1]];

	score += distances[parcours[N-1]][parcours[0]];
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

	cout << parcours[taille-1] << " ( " << score << " ) " << endl;
}

bool Solution::operator==(const vector<int> &parcours) const
{
	int N = this->parcours.size();
	if(N != parcours.size())
		return false;

	for(int i = 0; i < N; i++)
	{
		if(this->parcours[i] != parcours[i])
			return false;
	}

	return true;
}

bool Solution::operator<(const Solution &s) const
{
	return (score < s.score);
}

void Solution::slicingCrossover(const Solution &s, Solution &fils1, Solution &fils2) const
{
	int N = parcours.size();
	fils1.parcours.resize(N);
	fils2.parcours.resize(N);

	int ptCoupure = Rand::randi(N-1)+1; //1 -> N-1
	for(int i = 0; i < ptCoupure; i++)
	{
		fils1.parcours[i] = parcours[i];
		fils2.parcours[i] = s.parcours[i];
	}

	for(int i = ptCoupure; i < N; i++)
	{
		fils1.parcours[i] = s.parcours[i];
		fils2.parcours[i] = parcours[i];
	}
}
