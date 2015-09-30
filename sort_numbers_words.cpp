/*

    Sort a string of words and integers. Keeping the same type positions.

    eg; "2 pizza cat -1"
    order of numbers -1, 2
    order of words cat, pizza
    maintain type positions of number, word, word, number
    final output "-1 cat pizza 2"

*/



#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>

bool isNumber(std::string word);
std::string typeSort(std:: string input_string);

int main(int argc, char** argv)
{
	std::string input_string ("11 one 5 abe 3 kelly -1 pizza 7 3 4 ape -350");

	std::cout << typeSort(input_string);
}

std::string typeSort(std::string input_string)
{
	// Turn our input into a vector of strings
	std::vector<std::string> values;

	split(values, input_string, boost::is_any_of(" "));

	// Create a copy to sort the numbers and words
	std::vector<std::string> partitioned = values;
	auto partition = std::partition(partitioned.begin(), partitioned.end(), isNumber);

	// Sort
	std::sort(partitioned.begin(), partition,
				[](std::string a, std::string b){ return std::stoi(a) <= std::stoi(b); } );

	std::sort(partition, partitioned.end(),
				[](std::string a, std::string b){ return a <= b; } );

	// Write the words and numbers back in correct type order.
	// ie; first sorted number to first unsorted number position,etc
	auto it_numbers = partitioned.begin();
	auto it_words = partition;

	for(std::string &s : values)
	{
		if(isNumber(s))
			s = *it_numbers++;
		else
			s= *it_words++;
	}

	// Turn back into string
	std::string output = boost::join(values, " ");

	return output;
}



bool isNumber(std::string word)
{
    bool isNumber = true;

    for(std::string::const_iterator it = word.begin(); it != word.end(); ++it)
	{
        isNumber = isNumber && isdigit(*it) ||
		( it == word.begin() && *it == '-' && it != word.end() && isdigit(*(it + 1) ) );
	}

    return isNumber;

}

