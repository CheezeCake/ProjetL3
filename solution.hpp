#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include "solver.hpp"

class Solution
{
	private:
		int *parcours;
		int N;
		int score;
		
	public:
		Soltuion(int*, int, Solver&);
		~Soltuion();

		void fitness(Solver&);
};

#endif
