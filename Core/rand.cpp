#include "rand.hpp"

int Rand::cnt = 0;

void Rand::checkSeed()
{
	if(cnt > 10000 || cnt == 0)
	{
		srand(time(NULL));
		cnt = 0;
	}

	++cnt;
}

int Rand::randi()
{
	checkSeed();
	return rand();
}

int Rand::randi(int max)
{
	checkSeed();
	return (max == 0) ? 0 : rand()%max;
}

int Rand::randi(int min, int max)
{
	checkSeed();
	return (max == 0) ? 0 : (rand()%(max-min+1))+min;
}
