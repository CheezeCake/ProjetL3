#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <vector>

class Solution
{
	private:
		std::vector<int> parcours;
		int N;
		int score;
		
	public:
		Solution();
		Solution(const std::vector<int>&, int, const std::vector<std::vector<int> >&);
		bool operator==(const Solution&) const;
		bool operator==(const std::vector<int>&) const;
};

#endif
