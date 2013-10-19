#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <vector>

class Solution
{
	private:
		std::vector<int> parcours;
		double score;
		
	public:
		Solution();
		void afficher() const;
		double getScore() const;
		Solution(const std::vector<int>&, const std::vector<std::vector<double> >&);
		bool operator==(const Solution&) const;
		bool operator==(const std::vector<int>&) const;
};

#endif
