#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <iomanip>

class	Combination
{
	private:
		std::vector<std::vector<int> >	_combinations;
		// int					_sum = 0;

	public:
		void	combinationAssistant(int&, std::vector<int>&);
		std::vector<std::vector<int> >	getCombinations();
		Combination();
		~Combination();
};
