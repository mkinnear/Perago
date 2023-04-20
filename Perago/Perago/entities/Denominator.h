#pragma once

#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <sstream>
#include "Combination.h"

class	Denominator
{
	private:
		int											_money;
		std::vector<int>							_denominator;
		std::vector<Combination>					_combination;
		std::string									_heading;
		std::map<int, std::function< void() > >		_options;
		std::map<int, std::string>					_optionHeadings;
		std::ofstream								ofile;

		void	configurations();
		void	print();
		int		getInput();
		void	processInput(int option);
		void	captureAmount();
		bool	identifyDuplicateCoins(int);
		bool	validateCoins(std::string);
		void	captureAvailableCoins();

	public:
		std::string									pdfFilename;
		std::string									txtFilename;

		Denominator();
		~Denominator();
		std::string 	getTime();
		std::string		getDateTime();
		void			clearMoney();
		void			clearDenominator();
		void			printCombinations();
		void			run();
};
