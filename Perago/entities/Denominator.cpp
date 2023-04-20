#include "Denominator.h"

void	Denominator::configurations()
{
	_options.clear();
	_options[0] = std::bind(&Denominator::captureAmount, this);
	_options[1] = std::bind(&Denominator::captureAvailableCoins, this);
	// _options[2] = std::bind(&Denominator::mainMenu, this);

	_optionHeadings[0] = "Enter Amount";
	_optionHeadings[1] = "Enter Available Coins";
	// _optionHeadings[2] = "Back to Main Menu";
}

void	Denominator::print()
{
	system("CLS");
	std::cout << std::string(_heading.length(), '*') << std::endl;
	std::cout << _heading << std::endl;
	std::cout << std::string(_heading.length(), '*') << std::endl;

	std::cout << "Available Options" << std::endl;

	for(std::pair<int, std::function<void()>> option : _options)
	{
		std::cout << "\t" << option.first << "\t-\t";
		std::cout << _optionHeadings[option.first] << std::endl;
	}
	std::cout << std::string(_heading.length(), '*') << std::endl;
	std::cout << "Select an Option: ";
}

int		Denominator::getInput()
{
	int		input;

	std::cin >> input;

	return(input);
}

void	Denominator::processInput(int option)
{
	int		chosenOption = option;
	while(_options.find(chosenOption) == _options.end())
	{
		std::cout << "No such Option Available. Please retry!: ";
		chosenOption = getInput();
	}
	while (_optionHeadings[chosenOption] != "Back to Main Menu")
	{
		_options[chosenOption]();
		chosenOption++;
	}
}

void	Denominator::captureAmount()
{
	std::string money;
	size_t		found;
	while (_money == 0)
	{
		std::cout << "\nPlease Enter the Amount in Cent (i.e: 10c): ";
		std::cin >> money;
		ofile << "\n" << "[" << getTime() << "]:\tPlease Enter the Amount in Cent (i.e: 10c): " << money << std::endl;
		found = money.find('c');
		if (found == std::string::npos || found ==0)
		{
			continue;
		}
		std::stringstream extraction(money);
		extraction >> _money;
		if (_money > 0)
		{
			break;
		}
	}
}

bool	Denominator::identifyDuplicateCoins(int availableCoins)
{
	bool	duplicate = false;
	for (auto d : _denominator)
	{
		if (availableCoins == d)
		{
			duplicate = true;
		}
	}
	return (duplicate);
}

bool	Denominator::validateCoins(std::string availableCoins)
{
	bool	validCoins = true;
	for(auto c : availableCoins)
		{
			if (c < '0' && c > '9')
			{
				std::cout << "Invalid entry. Please retry!: ";
				ofile << "[" <<  getTime() << "]:\tInvalid entry. Please retry!: ";
				validCoins = false;
				break;
			}
		}
		return (validCoins);
}
void	Denominator::clearMoney(void)
{
	_money = 0;
}

void	Denominator::clearDenominator(void)
{
	_denominator.clear();
}

void	Denominator::captureAvailableCoins()
{
	std::string denominations;
    int         convertedDenominations;
    int			i = 1;

    std::cout << "(Enter 0 to exit) - Enter Denominator [" << i++ << "]: ";
	ofile << "[" <<  getTime() << "]:\t(Enter 0 to exit) - Enter Denominator [" << i << "]: ";
    while (std::cin >> denominations)
    {
        std::stringstream   sstream(denominations);
        sstream >> convertedDenominations;
		ofile << denominations << std::endl;
        if (convertedDenominations > 0)
        {
            _denominator.push_back(convertedDenominations);
			std::cout << "(Enter 0 to exit) - Enter Denominator [" << i++ << "]: ";
			ofile << "[" <<  getTime() << "]:\tEnter 0 to exit) - Enter Denominator [" << i << "]: ";
        }
        else
        {
            break;
        }
    }
    std::cout << std::endl;
	ofile << std::endl;
}


Denominator::Denominator()
{
	_heading = "Capture Amount & Denominations Menu";
	_money = 0;
	configurations();
	txtFilename = "Logs/txt_log_files/log_" + getDateTime() + ".txt";
	pdfFilename = "Logs/pdf_log_files/log_" + getDateTime() + ".pdf";
	ofile.open(txtFilename);
	if (!ofile.is_open())
	{
		std::cout << "Couldn't open log file" << std::endl;
	}
}

Denominator::~Denominator()
{
	ofile.close();
}

std::string	Denominator::getTime()
{
	auto in_time_t = std::time(nullptr);
	auto time = *std::localtime(&in_time_t);
	std::ostringstream oss;
	oss << std::put_time(&time, "%H:%M:%S");
	return (oss.str());
}

std::string	Denominator::getDateTime()
{
	auto now = std::chrono::system_clock::now();

    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream datetime;
    datetime << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
	return (datetime.str());
}

void	Denominator::printCombinations()
{
	for (auto comb : _combination.back().getCombinations())
	{
		std::cout << "[";
		ofile << "[" <<  getTime() << "]:\t[";
		for (auto coins : comb)
		{
			std::cout << " " << coins << "c, ";
			ofile << " " << coins << "c, ";
		}
		std::cout << "]" << std::endl;
		ofile << "]" << std::endl;
	}
}

void	Denominator::run()
{
	captureAmount();
	captureAvailableCoins();
	Combination obj;

	_combination.push_back(obj);
	_combination.back().combinationAssistant(_money, _denominator);
	// obj.printCombination();
	printCombinations();
	// mainMenu();
}
// 