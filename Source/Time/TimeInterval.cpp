    ////////////////////////////////////////
   //        YourLife by sqrt(-1)        //
  //                                    //
 //  File: TimeInterval.cpp            //
////////////////////////////////////////

#include "TimeInterval.h"

#include "../Util/Util.h"
#include "DateTime.h"

#include <stdexcept>

using namespace ylife;

long long TimeInterval::min() const noexcept
{
	return minutes_;
}

long long TimeInterval::hours() const noexcept
{
	return minutes_ / Time::MIN_IN_HOUR;
}

int TimeInterval::days() const noexcept
{
	return static_cast<int>(minutes_ / Time::MIN_IN_DAY);
}

int TimeInterval::months() const noexcept
{
	return static_cast<int>(minutes_ / DateTime::MIN_IN_MONTH);
}

int TimeInterval::years() const noexcept
{
	return static_cast<int>(minutes_ / DateTime::MIN_IN_YEAR);
}

void TimeInterval::set_min(long long min) noexcept
{
	minutes_ = min;
}

void TimeInterval::set_hours(long long hours) noexcept
{
	minutes_ = hours * Time::MIN_IN_HOUR;
}

void TimeInterval::set_days(int days) noexcept
{
	minutes_ = static_cast<long long>(days) * Time::MIN_IN_DAY;
}

void TimeInterval::set_months(int months) noexcept
{
	minutes_ = static_cast<long long>(months) * DateTime::MIN_IN_MONTH;
}

void TimeInterval::set_years(int years) noexcept
{
	minutes_ = static_cast<long long>(years) * DateTime::MIN_IN_YEAR;
}

std::string TimeInterval::to_string(const std::string& format) const
{
	std::string result;
	for (int i = 0; i < format.length(); ++i)
	{
		switch (format[i])
		{
		case '#':
		{
			switch (format[i + 1])
			{
			case '|': // #| => skip
				break;
			case '\0': // The end of the string => push the #
				result.push_back('#');
				break;
			default: // Push the character after the # (but not the #)
				result.push_back(format[i + 1]);
			}
			i += 1; // 2 characters were processed instead of 1
			break;
		}
		case '-':
		{
			if (minutes_ < 0)
			{
				result.push_back('-');
			}
			break;
		}
		case '+':
		{
			result.push_back(minutes_ < 0 ? '-' : '+');
			break;
		}
		case 'y': // Years
		{
			result.append(std::to_string(std::abs(years())));
			break;
		}
		case 'M': // Months
		{
			if (format[i + 1] == '*') // Total
			{
				result.append(std::to_string(std::abs(months())));
				i += 1;
			}
			else // Of year
			{
				int count = (format[i + 1] == 'M') ? 2 : 1; // How many digits are required
				util::append_up_to_two_digits(result, std::abs(months()) % Date::MONTHS_IN_YEAR, count);
				i += count - 1;
			}
			break;
		}
		case 'd': // Days
		{
			if (format[i + 1] == '*') // Total
			{
				result.append(std::to_string(std::abs(days())));
				i += 1;
			}
			else // Of month
			{
				int count = (format[i + 1] == 'd') ? 2 : 1; // How many digits are required
				util::append_up_to_two_digits(result, std::abs(days()) % Date::DAYS_IN_MONTH, count);
				i += count - 1;
			}
			break;
		}
		case 'D': // Days of year
		{
			int count = (format[i + 1] == 'D') ? 2 : 1; // How many digits are required
			util::append_up_to_two_digits(result, std::abs(days()) % Date::DAYS_IN_YEAR, count);
			i += count - 1;
			break;
		}
		case 'h': // Hours
		{
			if (format[i + 1] == '*') // Total
			{
				result.append(std::to_string(std::abs(hours())));
				i += 1;
			}
			else // Of day
			{
				int count = (format[i + 1] == 'h') ? 2 : 1; // How many digits are required
				util::append_up_to_two_digits(result, std::abs(hours()) % Time::HOURS_IN_DAY, count);
				i += count - 1;
			}
			break;
		}
		case 'm': // Minutes
		{
			if (format[i + 1] == '*') // Total
			{
				result.append(std::to_string(std::abs(min())));
				i += 1;
			}
			else if (format[i + 1] == 'd') // Of day
			{
				result.append(std::to_string(std::abs(min()) % Time::MIN_IN_DAY));
				i += 1;
			}
			else // Of hour
			{
				int count = (format[i + 1] == 'm') ? 2 : 1; // How many digits are required
				util::append_up_to_two_digits(result, std::abs(min()) % Time::MIN_IN_HOUR, count);
				i += count - 1;
			}
			break;
		}
		default: // Any other character
		{
			result.push_back(format[i]);
		}
		}
	}
	return result;
}

std::strong_ordering TimeInterval::operator<=>(const TimeInterval& date_time) noexcept
{
	return minutes_ <=> date_time.minutes_;
}

TimeInterval TimeInterval::operator+() const noexcept
{
	return *this;
}

TimeInterval TimeInterval::operator-() const noexcept
{
	return TimeInterval::min(-minutes_);
}

TimeInterval TimeInterval::operator+(const TimeInterval& interval) const noexcept
{
	return TimeInterval::min(minutes_ + interval.minutes_);
}

TimeInterval TimeInterval::operator-(const TimeInterval& interval) const noexcept
{
	return TimeInterval::min(minutes_ - interval.minutes_);
}

TimeInterval TimeInterval::operator*(long long number) const noexcept
{
	return TimeInterval::min(minutes_ * number);
}

TimeInterval ylife::operator*(long long number, const TimeInterval& interval) noexcept
{
	return interval * number;
}

long long TimeInterval::operator/(const TimeInterval& interval) const
{
	if (interval.minutes_ == 0)
	{
		throw std::domain_error("Attempt to divide by zero");
	}
	return minutes_ / interval.minutes_;
}

TimeInterval TimeInterval::operator/(long long number) const
{
	if (number == 0)
	{
		throw std::domain_error("Attempt to divide by zero");
	}
	return TimeInterval::min(minutes_ / number);
}

TimeInterval TimeInterval::operator%(const TimeInterval& interval) const
{
	if (interval.minutes_ == 0)
	{
		throw std::domain_error("Attempt to divide by zero");
	}
	return TimeInterval::min(minutes_ % interval.minutes_);
}

TimeInterval TimeInterval::operator++() noexcept
{
	++minutes_;
	return *this;
}

TimeInterval TimeInterval::operator++(int) noexcept
{
	TimeInterval interval = *this;
	++minutes_;
	return interval;
}

TimeInterval TimeInterval::operator--() noexcept
{
	--minutes_;
	return *this;
}

TimeInterval TimeInterval::operator--(int) noexcept
{
	TimeInterval interval = *this;
	--minutes_;
	return interval;
}

TimeInterval& TimeInterval::operator+=(const TimeInterval& interval) noexcept
{
	minutes_ += interval.minutes_;
	return *this;
}

TimeInterval& TimeInterval::operator-=(const TimeInterval& interval) noexcept
{
	minutes_ -= interval.minutes_;
	return *this;
}

TimeInterval& TimeInterval::operator*=(long long number) noexcept
{
	minutes_ *= number;
	return *this;
}

TimeInterval& TimeInterval::operator/=(long long number)
{
	if (number == 0)
	{
		throw std::domain_error("Attempt to divide by zero");
	}
	minutes_ /= number;
	return *this;
}

TimeInterval& TimeInterval::operator%=(const TimeInterval& interval)
{
	if (interval.minutes_ == 0)
	{
		throw std::domain_error("Attempt to divide by zero");
	}
	minutes_ %= interval.minutes_;
	return *this;
}


TimeInterval TimeInterval::min(long long min) noexcept
{
	TimeInterval interval;
	interval.set_min(min);
	return interval;
}

TimeInterval TimeInterval::hours(long long hours) noexcept
{
	TimeInterval interval;
	interval.set_hours(hours);
	return interval;
}

TimeInterval TimeInterval::days(int days) noexcept
{
	TimeInterval interval;
	interval.set_days(days);
	return interval;
}

TimeInterval TimeInterval::months(int months) noexcept
{
	TimeInterval interval;
	interval.set_months(months);
	return interval;
}

TimeInterval TimeInterval::years(int years) noexcept
{
	TimeInterval interval;
	interval.set_years(years);
	return interval;
}

const std::string TimeInterval::DEFAULT_FORMAT = "-d*:hh:mm";

TimeInterval time_literals::operator""_min(unsigned long long min) noexcept
{
	return TimeInterval::min(min);
}

TimeInterval time_literals::operator""_h(unsigned long long hours) noexcept
{
	return TimeInterval::hours(hours);
}

TimeInterval time_literals::operator""_d(unsigned long long days) noexcept
{
	return TimeInterval::days(days);
}

TimeInterval time_literals::operator""_mon(unsigned long long months) noexcept
{
	return TimeInterval::months(months);
}

TimeInterval time_literals::operator""_y(unsigned long long years) noexcept
{
	return TimeInterval::years(years);
}
