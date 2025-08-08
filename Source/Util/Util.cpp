    ////////////////////////////////////////
   //        YourLife by sqrt(-1)        //
  //                                    //
 //  File: Util.cpp                    //
////////////////////////////////////////

#include "Util.h"

using namespace ylife;

int util::count_letters(const std::string& string, int from, int max) noexcept
{
	int n = 1;
	while (n < max && string[from + n] == string[from])
	{
		++n;
	}
	return n;
}

void util::append_up_to_two_digits(std::string& destination, int number, int digits) noexcept
{
	int first = number / 10 % 10;
	int second = number % 10;
	if (first != 0 || digits > 1)
	{
		destination.push_back('0' + first);
	}
	destination.push_back('0' + second);
}