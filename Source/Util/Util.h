    ////////////////////////////////////////
   //        YourLife by sqrt(-1)        //
  //                                    //
 //  File: Util.h                      //
////////////////////////////////////////

#pragma once

#include <stdexcept>
#include <type_traits>

namespace ylife::util
{

// The default division operation rounds towards zero
// This uniform division always rounds to the closest lower (if b > 0) or greater (if b < 1) integer:
//  4 / 3 =  1         4 / -3 = -2
//  3 / 3 =  1         3 / -3 = -1
//  1 / 3 =  0         1 / -3 = -1
// -1 / 3 = -1        -1 / -3 =  0
// -3 / 3 = -1        -3 / -3 =  1
// -4 / 3 = -2        -4 / -3 =  1
template<typename T, typename U> requires std::is_integral_v<T> && std::is_integral_v<U>
auto uniform_div(T a, U b) -> decltype(a / b);

// The default modulo operation returns a result counted from zero
// This uniform modulo always counts from the lower (if b > 0) or greater (if b < 0) number,
//  and is always non-negative (if b > 0) or non-positive (if b < 0):
//  5 % 3 =  2         5 % -3 = -1
//  3 % 3 =  0         3 % -3 =  0
//  1 % 3 =  1         1 % -3 = -2
// -1 % 3 =  2        -1 % -3 = -1
// -3 % 3 =  0        -3 % -3 =  0
// -5 % 3 =  1        -5 % -3 = -2
template<typename T, typename U> requires std::is_integral_v<T> && std::is_integral_v<U>
auto uniform_mod(T a, U b) -> decltype(a % b);

// How many times in a row a string[from] char appears
// count_letters("some_ssstring", 5, 4) == 3
//                     ^
// count_letters("some_sssststring", 5, 4) == 4
//                     ^
// count_letters("some_sssssstring", 5, 4) == 4 // 4 is set as max
//                     ^
int count_letters(const std::string& string, int from, int max) noexcept;

// Converts a number to string and pushes it into the end of the destination string
// The number is supposed to be 2-digit, otherwise all digits but the last two will be discarded
// The digits argument designates how many digits needs to be pushed into the string
//  if the number is 1-digit: 1 or 2 (if 2, the first will be 0)
// append_up_to_two_digits(str, 15, 1) => str.append("15")
// append_up_to_two_digits(str, 15, 2) => str.append("15")
// append_up_to_two_digits(str,  5, 1) => str.append("5")
// append_up_to_two_digits(str,  5, 2) => str.append("05")
void append_up_to_two_digits(std::string& destination, int number, int digits) noexcept;

}


template<typename T, typename U> requires std::is_integral_v<T> && std::is_integral_v<U>
auto ylife::util::uniform_div(T a, U b) -> decltype(a / b)
{
	if (b == 0)
	{
		throw std::domain_error("Attempt to divide by zero");
	}
	else if (b < 0)
	{
		return uniform_div(-a, -b);
	}
	else if (a >= 0) // Both positive => regular division
	{
		return a / b;
	}
	else // Negative / positive => modified division
	{
		return (a + 1) / b - 1;
	}
}

template<typename T, typename U> requires std::is_integral_v<T> && std::is_integral_v<U>
auto ylife::util::uniform_mod(T a, U b) -> decltype(a % b)
{
	if (b == 0)
	{
		throw std::domain_error("Attempt to divide by zero");
	}
	else if (b < 0)
	{
		return uniform_mod(-a, -b);
	}
	else if (a >= 0) // Both positive => regular modulo
	{
		return a % b;
	}
	else // Negative % positive => modified modulo
	{
		return (a + 1) % b + b - 1;
	}
}
