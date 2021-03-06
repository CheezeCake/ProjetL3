#include <iostream>
#include <algorithm>
#include "rand.hpp"
#include "solution.hpp"
using namespace std;

Solution::Solution()
{
	score = 0;
}

Solution::Solution(const Solution &source)
{
	parcours = source.parcours;
	score = source.score;
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

void Solution::calculerScore(const vector<vector<double> > &distances)
{
	int N = parcours.size();

	score = 0;
	for(int i = 0; i < N-1; i++)
		score += distances[parcours[i]][parcours[i+1]];

	score += distances[parcours[N-1]][parcours[0]];
}

bool Solution::operator==(const Solution &s) const
{
	if(score != s.score)
		return false;

	return (*this == s.parcours);
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
	unsigned int N = this->parcours.size();
	if(N != parcours.size())
		return false;

	for(unsigned int i = 0; i < N; i++)
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

Solution& Solution::operator=(const Solution &s)
{
	if(this != &s)
	{
		parcours = s.parcours;
		score = s.score;
	}

	return *this;
}

void Solution::slicingCrossover(const Solution &s, Solution &fils1, Solution &fils2) const
{
	int N = parcours.size();
	fils1.parcours.resize(N);
	fils2.parcours.resize(N);

	vector<bool> used1(N, false);
	vector<bool> used2(N, false);

	int ptCoupure = Rand::randi(1, N-1);
	int v;
	for(int i = 0; i < ptCoupure; i++)
	{
		v = parcours[i];
		fils1.parcours[i] = v;
		used1[v] = true;

		v = s.parcours[i];
		fils2.parcours[i] = v;
		used2[v] = true;
	}

	int j1 = ptCoupure;
	int j2 = ptCoupure;
	for(int i = 0; i < N; i++)
	{
		v = s.parcours[i];
		if(!used1[v])
			fils1.parcours[j1++] = v;

		v = parcours[i];
		if(!used2[v])
			fils2.parcours[j2++] = v;
	}
}

void Solution::slicingCrossover(unsigned int k, const Solution &s, Solution &fils1, Solution &fils2) const
{
	unsigned int N = parcours.size();
	if(k >= N)
		return;

	fils1.parcours.resize(N);
	fils2.parcours.resize(N);

	vector<int> ptsCoupure(N+1);
	for(unsigned int i = 0; i < N; i++)
		ptsCoupure[i] = i;

	int (*gen)(int) = Rand::randi;
	random_shuffle(ptsCoupure.begin()+1, ptsCoupure.end()-1, gen);
	sort(ptsCoupure.begin()+1, ptsCoupure.begin()+k+1);
	ptsCoupure[k+1] = N;

	vector<bool> used1(N, false);
	vector<bool> used2(N, false);

	int v;
	int j, l;
	for(unsigned int i = 0; i <= k; i++)
	{
		bool pthis = ((i+1)%2 == 0);
		j = ptsCoupure[i];
		l = 0;

		while(j < ptsCoupure[i+1])
		{
			v = (pthis) ? parcours[l] : s.parcours[l];
			if(!used1[v])
			{
				used1[v] = true;
				fils1.parcours[j++] = v;
			}

			l++;
		}

		j = ptsCoupure[i];
		l = 0;

		while(j < ptsCoupure[i+1])
		{
			v = (pthis) ? s.parcours[l] : parcours[l];
			if(!used2[v])
			{
				used2[v] = true;
				fils2.parcours[j++] = v;
			}

			l++;
		}
	}
}

void Solution::mutation(Solution &result) const
{
	result = *this;
	int N = parcours.size();
	int tirage1 = Rand::randi(1, N-1);
	int tirage2 = tirage1;
	while(tirage1 == tirage2)
		tirage2 = Rand::randi(1, N-1);
	swap(result.parcours[tirage1], result.parcours[tirage2]);
	//calculer score
}
	
void Solution::getParcours(vector<int> &p)
{
	p = parcours;
}
