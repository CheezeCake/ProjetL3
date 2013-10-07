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
		Solution(const int*, int, Solver&);
		~Solution();
		bool operator==(const Solution&);

		void fitness(Solver&);
};

#endif
