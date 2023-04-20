#include "Menu.h"

void	Menu::configurations()
{
	_options.clear();
	_optionHeadings.clear();

	_options[0] = std::bind(&Menu::quit, this);
	_options[1] = std::bind(&Menu::denominatorMenu, this);
	_options[2] = std::bind(&Menu::displayLogs, this);
	_options[3] = std::bind(&Menu::exportLogs, this);
	_options[4] = std::bind(&Menu::quitAndExportLogs, this);

	_optionHeadings[0] = "Exit";
	_optionHeadings[1] = "Capture Amount and Denominations";
	_optionHeadings[2] = "Display Logs";
	_optionHeadings[3] = "Export Logs to PDF";
	_optionHeadings[4] = "Export Logs to PDF & Exit Program";
}

void	Menu::print()
{
	system("CLS");
	std::cout << std::string(_heading.length(), '*') << std::endl;
	std::cout << _heading << std::endl;
	std::cout << std::string(_heading.length(), '*') << std::endl;

	std::cout << "Available Options" << std::endl;
	
	for(std::pair<int, std::function< void() > > option : _options)
	{
		std::cout << "\t" << option.first << "\t-\t"; 
		std::cout << _optionHeadings[option.first] << std::endl;
	}

	std::cout << std::string(_heading.length(), '*') << std::endl;
	std::cout << "Please make your selection: ";
}

int	Menu::getInput()
{
	int	option;
	std::cin >> option;
	return(option);
}

void	Menu::processInput(int option)
{
	int	chosenOption = option;
	while(_options.find(chosenOption) == _options.end())
	{
		std::cout << "No such option available. Please retry; ";
		chosenOption = getInput();
	}
	_options[chosenOption]();
}

void	Menu::quit()
{
	_quit = 1;
}

void	Menu::denominatorMenu()
{
	_denominator.run();
	_denominator.clearDenominator();
	_denominator.clearMoney();
}

void	Menu::displayLogs()
{
	std::ifstream	ifile;
	std::string		line;
	std::cout << "\n[FILENAME]: " << _denominator.txtFilename << std::endl;
	ifile.open(_denominator.txtFilename, std::ios::in);
	if (!ifile.is_open())
	{
		std::cout << "[ERROR]: Failed To Opening Log File!\n" << std::endl;
	}
	else if (ifile.peek() == std::ifstream::traits_type::eof())
	{
		std::cout << "[WARNING]: Log File is EMPTY!\n" << std::endl;
	}
	else 
	{
		while (std::getline(ifile, line))
		{
			std::cout << line << std::endl;
		}
		std::cout << "\n" << std::endl;
	}
	ifile.close();
}

void	Menu::exportLogs()
{
	std::ifstream	ifile, ifile2;
	std::ofstream	ofile;
	std::string		line;
	std::cout << "\n[FILENAME]: " << _denominator.txtFilename << std::endl;
	ifile.open(_denominator.txtFilename);
	ofile.open(_denominator.pdfFilename);
	ifile2.open(_denominator.pdfFilename);
	if (!ifile.is_open())
	{
		std::cout << "[ERROR]: Failed To Opening Log File!\n" << std::endl;
	}
	else if (ifile.peek() == std::ifstream::traits_type::eof())
	{
		std::cout << "[WARNING]: Log File is EMPTY!\n" << std::endl;
	}
	else if (!ofile.is_open())
	{
		std::cout << "[ERROR]: Failed To Open PDF File!\n" << std::endl;
	}
	else if (ifile2.peek() == std::ifstream::traits_type::eof())
	{
		std::cout << "[WARNING]: Log File is EMPTY!\n" << std::endl;
	}
	else 
	{
		while (std::getline(ifile, line))
		{
			ofile << line << std::endl;
		}
		std::cout << "\n" << std::endl;
		std::cout << "PDF File Has Been Exported!\n" << std::endl;
	}
	ifile.close();
	ofile.close();
}

void	Menu::quitAndExportLogs()
{
	exportLogs();
	quit();
}

Menu::Menu()
{
	_heading = "Perago's Default Menu";
	_quit = 0;

	configurations();
}

Menu::Menu(std::string heading)
{
	_heading = heading;
	_quit = 0;

	configurations();
}

Menu::~Menu()
{
	std::cout << "Quitting Program..." << std::endl;
}

void	Menu::run()
{
	do {
		print();
		processInput(getInput());
	} while (_quit == 0);
}
