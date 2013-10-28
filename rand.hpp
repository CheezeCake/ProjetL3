#ifndef	RAND_HPP
#define RAND_HPP

#include <cstdlib>
#include <ctime>

class Rand
{
	private:
		static int cnt;
		static void checkSeed();

	public:
		static int randi();
		static int randi(int max);
};	

#endif
