#include "Combination.h"

void		Combination::combinationAssistant(int &n, std::vector<int>& _denominations)
{
    std::vector<int> 		                newCombo;
    std::vector<std::vector<int> >   		newCombinations;
    const   int                     		root_id = n;
    int                                     answer;
    static  int                             coinIndex = 0;

	std::cout << "[amount]: " << root_id << std::endl;
    newCombo.clear();
    newCombinations.clear();
    for (int i = 0; i < _denominations.size(); i++)
    {
        if (_denominations[i] > root_id)
            _denominations.erase(_denominations.begin() + i);
    }
    if (_denominations.size() == 0)
    {
        _denominations[0] = 0;
		_combinations.push_back(_denominations);
    }
    for (coinIndex = 0; coinIndex < _denominations.size(); coinIndex++)
    {
        if (((root_id % _denominations[coinIndex]) == 0))
        {
            bool isEqual = false;
            answer = root_id / _denominations[coinIndex];
            for (int i = 0; i < answer; i++)
            {
                newCombo.push_back(_denominations[coinIndex]);
            }
            std::sort(newCombo.begin(), newCombo.end());
            if (!newCombinations.empty())
            {
                for (auto nc : newCombinations)
                {
                    if (nc == newCombo)
                    {
                        isEqual = true;
                    }
                }
            }
            if (!isEqual)
                newCombinations.push_back(newCombo);
            newCombo.clear();
        }
        else
        {
            bool isEqual = false;
            answer = root_id - _denominations[coinIndex];
            if (answer == 0)
            {
                newCombo.push_back(_denominations[coinIndex]);
                newCombinations.push_back(newCombo);
                newCombo.clear();
            }
            else {
                for (auto c : _denominations)
                {
                    if (answer == c)
                    {
                        // std::cout << "[answer found in array]: " << std::endl;
                        newCombo.push_back(_denominations[coinIndex]);
                        newCombo.push_back(answer);
                        std::sort(newCombo.begin(), newCombo.end());
                        if (!newCombinations.empty())
                        {
                            for (auto nc : newCombinations)
                            {
                                if (nc == newCombo)
                                {
                                    isEqual = true;
                                }
                            }
                        }
                        if (!isEqual)
                            newCombinations.push_back(newCombo);
                        newCombo.clear();
                    }
                }
            }
        }
    }
    _combinations = newCombinations;
    newCombinations.clear();
    for (int    i = 0; i < _denominations.size(); i++)
    {
        for (int    argc = 0; argc < _combinations.size(); argc++)
        {
            for (int argv = 0; argv < _combinations[argc].size(); argv++)
            {
                if (_combinations[argc][argv] > _denominations[i])
                {
                    bool isFound = false;
                    answer = _combinations[argc][argv] - _denominations[i];
                    for (auto coins : _denominations)
                    {
                        if (coins == answer)
                            isFound = true;
                    }
                    if (isFound)
                    {
                        newCombo = _combinations[argc];
                        newCombo.erase(newCombo.begin() + argv);
                        newCombo.push_back(answer);
                        newCombo.push_back(_denominations[i]);
                        std::sort(newCombo.begin(), newCombo.end());
                        bool    isequal = false;
                        for (auto comp : _combinations)
                        {
                            std::sort(comp.begin(), comp.end());
                            if (comp == newCombo)
                            {
                                isequal = true;
                            }
                        }
                        if (!isequal)
                        _combinations.push_back(newCombo);
                    newCombo.clear();
                    }
                }
            }
        }
    }
    std::sort(_combinations.begin(), _combinations.end());
}

std::vector<std::vector<int> >	Combination::getCombinations()
{
	return (_combinations);
}

Combination::Combination()
{
	_combinations.clear();
}

Combination::~Combination()
{
}
