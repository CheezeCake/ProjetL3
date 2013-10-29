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
		void calculerScore(const std::vector<std::vector<double> >&);
		Solution(const std::vector<int>&, const std::vector<std::vector<double> >&);
		bool operator==(const Solution&) const;
		bool operator==(const std::vector<int>&) const;
		bool operator<(const Solution&) const;
		void slicingCrossover(const Solution&, Solution&, Solution&) const;
		void slicingCrossover(unsigned int, const Solution&, Solution&, Solution&) const;
};

#endif
