#pragma once

#include "entities/Denominator.h"

class	Menu
{
	private:
		std::string								_heading;
		std::map<int, std::function< void() > >	_options;
		std::map<int, std::string>				_optionHeadings;
		int										_quit;
		Denominator								_denominator;

		void	configurations();
		void	print();
		int		getInput();
		void	processInput(int option);
		void	quit();
		void	denominatorMenu();
		void	displayLogs();
		void	exportLogs();
		void	quitAndExportLogs();

	public:
		Menu();
		Menu(std::string heading);
		~Menu();
		void	run();
};
