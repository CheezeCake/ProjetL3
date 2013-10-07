#ifndef SOLUTION_HPP
#define SOLUTION_HPP

class Solution
{
	private:
		int *parcours;
		int N;
		int score;

	public:
		Soltuion(int*, int);
		~Soltuion();

		void fitness();
};

#endif
