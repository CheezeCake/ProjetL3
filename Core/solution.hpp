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
		Solution(const std::vector<int>&, const std::vector<std::vector<double> >&);
		Solution(const Solution&);
		void afficher() const;
		double getScore() const;
		void calculerScore(const std::vector<std::vector<double> >&);
		bool operator==(const Solution&) const;
		bool operator==(const std::vector<int>&) const;
		bool operator<(const Solution&) const;
		Solution& operator=(const Solution&);
		void slicingCrossover(const Solution&, Solution&, Solution&) const;
		void slicingCrossover(unsigned int, const Solution&, Solution&, Solution&) const;
		void mutation(Solution&) const;

		void getParcours(std::vector<int>&);
};

#endif
