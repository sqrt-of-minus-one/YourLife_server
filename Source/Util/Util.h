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

template<typename T, typename U> requires std::is_integral_v<T> && std::is_integral_v<U>
auto uniform_div(T a, U b) -> decltype(a / b);

template<typename T, typename U> requires std::is_integral_v<T> && std::is_integral_v<U>
auto uniform_mod(T a, U b) -> decltype(a % b);

int count_letters(const std::string& string, int from, int max) noexcept;

void append_up_to_two_digits(std::string& destination, int number, int digits) noexcept;

}


template<typename T, typename U> requires std::is_integral_v<T> && std::is_integral_v<U>
auto ylife::util::uniform_div(T a, U b) -> decltype(a / b)
{
	if (b == 0)
	{
		throw std::domain_error("Attempt to divide by zero");
	}
	else if (!(a < 0 ^ b < 0))
	{
		return a / b;
	}
	else if (a < 0)
	{
		return (a + 1) / b - 1;
	}
	else
	{
		return (a - 1) / b + 1;
	}
}

template<typename T, typename U> requires std::is_integral_v<T> && std::is_integral_v<U>
auto ylife::util::uniform_mod(T a, U b) -> decltype(a % b)
{
	if (b == 0)
	{
		throw std::domain_error("Attempt to divide by zero");
	}
	else if (!(a < 0 ^ b < 0))
	{
		return a % b;
	}
	else if (a < 0)
	{
		return (a + 1) % b + b - 1;
	}
	else
	{
		return (a - 1) % b + b + 1;
	}
}
