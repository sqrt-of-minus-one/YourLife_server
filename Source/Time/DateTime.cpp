    ////////////////////////////////////////
   //        YourLife by sqrt(-1)        //
  //                                    //
 //  File: DateTime.cpp                //
////////////////////////////////////////

#include "DateTime.h"

#include "TimeInterval.h"
#include "../Util/Util.h"

using namespace ylife;

SDateTime SDateTime::combine(SDate date, STime time) noexcept
{
	return {
		.year = date.year,
		.month = date.month,
		.day = date.day,
		.hour = time.hour,
		.min = time.min
	};
}

SDate SDateTime::date() const noexcept
{
	return {
		.year = year,
		.month = month,
		.day = day
	};
}

STime SDateTime::time() const noexcept
{
	return {
		.hour = hour,
		.min = min
	};
}

DateTime::DateTime(SDateTime time) noexcept
{
	set_date_time(time);
}

DateTime::DateTime(SDate date, STime time) noexcept
{
	set_date_time(date, time);
}

DateTime::DateTime(Date date, Time time) noexcept
{
	set_date_time(date, time);
}

DateTime::DateTime(int year, EMonth month, int day, int hour, int min) noexcept
{
	set_date_time(year, month, day, hour, min);
}

SDateTime DateTime::get_date_time() const noexcept
{
	return SDateTime::combine(get_date(), get_time());
}

SDate DateTime::get_date() const noexcept
{
	return date().get_date();
}

Date DateTime::date() const noexcept
{
	return Date(util::uniform_div(minutes_, Time::MIN_IN_DAY));
}

int DateTime::get_year() const noexcept
{
	return util::uniform_div(minutes_, MIN_IN_YEAR) + 1;
}

EMonth DateTime::get_month() const noexcept
{
	return static_cast<EMonth>((get_day_of_year() - 1) / Date::DAYS_IN_MONTH + 1);
}

int DateTime::get_day() const noexcept
{
	return util::uniform_mod(get_day_since_origin() - 1, Date::DAYS_IN_MONTH) + 1;
}

int DateTime::get_day_of_year() const noexcept
{
	return util::uniform_mod(get_day_since_origin() - 1, Date::DAYS_IN_YEAR) + 1;
}

int DateTime::get_day_since_origin() const noexcept
{
	return util::uniform_div(minutes_, Time::MIN_IN_DAY) + 1;
}

STime DateTime::get_time() const noexcept
{
	return time().get_time();
}

Time DateTime::time() const noexcept
{
	return Time(util::uniform_mod(minutes_, Time::MIN_IN_DAY));
}

int DateTime::get_hour() const noexcept
{
	return get_min_since_midnight() / Time::MIN_IN_HOUR;
}

int DateTime::get_min() const noexcept
{
	return util::uniform_mod(minutes_, Time::MIN_IN_HOUR);
}

int DateTime::get_min_since_midnight() const noexcept
{
	return util::uniform_mod(minutes_, Time::MIN_IN_DAY);
}

long long DateTime::get_min_since_origin() const noexcept
{
	return minutes_;
}

TimeInterval DateTime::get_time_since_new_year() const noexcept
{
	return date().get_time_since_new_year() + time().get_time_since_midnight();
}

TimeInterval DateTime::get_time_since_origin() const noexcept
{
	return TimeInterval::min(minutes_);
}

void DateTime::set_date_time(SDateTime date_time) noexcept
{
	set_date_time(date_time.year, date_time.month, date_time.day, date_time.hour, date_time.min);
}

void DateTime::set_date_time(SDate date, STime time) noexcept
{
	set_date_time(date.year, date.month, date.day, time.hour, time.min);
}

void DateTime::set_date_time(Date date, Time time) noexcept
{
	minutes_ = static_cast<long long>(date.days_) * Time::MIN_IN_DAY + time.minutes_;
}

void DateTime::set_date_time(int year, EMonth month, int day, int hour, int min) noexcept
{
	minutes_ =
		static_cast<long long>(year - 1) * MIN_IN_YEAR +
		(static_cast<int>(month) - 1) * MIN_IN_MONTH +
		(day - 1) * Time::MIN_IN_DAY +
		hour * Time::MIN_IN_HOUR + min;
}

void DateTime::set_date(SDate date) noexcept
{
	set_date(Date(date));
}

void DateTime::set_date(Date date) noexcept
{
	minutes_ += static_cast<long long>(date.days_ - util::uniform_div(minutes_, Time::MIN_IN_DAY)) * Time::MIN_IN_DAY;
}

void DateTime::set_date(int year, EMonth month, int day) noexcept
{
	set_date(Date(year, month, day));
}

void DateTime::set_year(int year) noexcept
{
	minutes_ += (static_cast<long long>(year) - get_year()) * MIN_IN_YEAR;
}

void DateTime::set_month(EMonth month) noexcept
{
	minutes_ += (static_cast<long long>(month) - static_cast<long long>(get_month())) * MIN_IN_MONTH;
}

void DateTime::set_day(int day) noexcept
{
	minutes_ += (static_cast<long long>(day) - get_day()) * Time::MIN_IN_DAY;
}

void DateTime::set_day_of_year(int day) noexcept
{
	minutes_ += (static_cast<long long>(day) - get_day_of_year()) * Time::MIN_IN_DAY;
}

void DateTime::set_day_since_origin(int day) noexcept
{
	minutes_ += (static_cast<long long>(day) - get_day_since_origin()) * Time::MIN_IN_DAY;
}

void DateTime::set_time(STime time) noexcept
{
	set_time(Time(time));
}

void DateTime::set_time(Time time) noexcept
{
	minutes_ += time.minutes_ - get_min_since_midnight();
}

void DateTime::set_time(int hour, int min) noexcept
{
	set_time(Time(hour, min));
}

void DateTime::set_hour(int hour) noexcept
{
	minutes_ += (hour - get_hour()) * Time::MIN_IN_HOUR;
}

void DateTime::set_min(int min) noexcept
{
	minutes_ += min - get_min();
}

void DateTime::set_min_since_midnight(int min) noexcept
{
	minutes_ += min - get_min_since_midnight();
}

void DateTime::set_min_since_origin(long long min) noexcept
{
	minutes_ = min;
}

std::string DateTime::to_string(const std::string& format) const
{
	std::string result;
	for (int i = 0; i < format.size(); ++i)
	{
		switch (format[i])
		{
		case '#': // #?
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
		case 'y': // Year
		{
			std::string year = std::to_string(get_year()); // The year
			int count = util::count_letters(format, i, 4); // How many digits are required
			while (year.length() < count)
			{
				// Push zeros into the string 
				year.insert(year.front() == '-' ? 1 : 0, "0");
			}
			result.append(year);
			i += count - 1;
			break;
		}
		case 'M': // Month
		{
			int count = util::count_letters(format, i, 4);
			switch (count)
			{
			case 1:
			case 2:
				// Add 1 or 2 digits
				util::append_up_to_two_digits(result, static_cast<int>(get_month()), count);
				break;
			case 3: // Short name
				result.append(get_month_short_name(get_month()));
				break;
			case 4: // Full name
				result.append(get_month_full_name(get_month()));
				break;
			}
			i += count - 1;
			break;
		}
		case 'd': // Day of month
		{
			int count = util::count_letters(format, i, 4);
			switch (count)
			{
			case 2:
				result.push_back('0'); // Day of month always has only 1 digit
				[[fallthrough]];
			case 1:
				result.push_back('0' + get_day());
				break;
			case 3: // Short name
				result.append(get_day_short_name(static_cast<EWeekDay>(get_day())));
				break;
			case 4: // Full name
				result.append(get_day_full_name(static_cast<EWeekDay>(get_day())));
				break;
			}
			i += count - 1;
			break;
		}
		case 'D': // Day of year
		{
			int count = (format[i + 1] == 'D') ? 2 : 1; // How many digits are required
			util::append_up_to_two_digits(result, get_day_of_year(), count);
			i += count - 1;
			break;
		}
		case 'h': // Hour (12)
		{
			int count = (format[i + 1] == 'h') ? 2 : 1; // How many digits are required
			int hour = get_hour();
			if (hour == 0)
			{
				hour = 12;
			}
			else if (hour > 12)
			{
				hour -= 12;
			}
			util::append_up_to_two_digits(result, hour, count);
			i += count - 1;
			break;
		}
		case 'H': // Hour (24)
		{
			int count = (format[i + 1] == 'H') ? 2 : 1; // How many digits are required
			util::append_up_to_two_digits(result, get_hour(), count);
			i += count - 1;
			break;
		}
		case 'a': // am/pm
		{
			int hour = get_hour();
			bool is_pm = hour > 12 || hour == 0;
			if (format[i + 1] == '.')
			{
				result.append(is_pm ? "p.m." : "a.m.");
				i += 1;
			}
			else
			{
				result.append(is_pm ? "pm" : "am");
			}
			break;
		}
		case 'A': // AM/PM
		{
			int hour = get_hour();
			bool is_pm = hour > 12 || hour == 0;
			if (format[i + 1] == '.')
			{
				result.append(is_pm ? "P.M." : "A.M.");
				i += 1;
			}
			else
			{
				result.append(is_pm ? "PM" : "AM");
			}
			break;
		}
		case 'm': // Minutes
		{
			int count = (format[i + 1] == 'm') ? 2 : 1; // How many digits are required
			util::append_up_to_two_digits(result, get_min(), count);
			i += count - 1;
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

DateTime& DateTime::operator=(SDateTime date_time) noexcept
{
	set_date_time(date_time);
	return *this;
}

std::strong_ordering DateTime::operator<=>(const DateTime& date_time) noexcept
{
	return minutes_ <=> date_time.minutes_;
}

DateTime DateTime::operator+() const noexcept
{
	return *this;
}

DateTime DateTime::operator+(const TimeInterval& interval) const noexcept
{
	DateTime date_time(minutes_ + interval.min());
	return date_time;
}

DateTime ylife::operator+(const TimeInterval& interval, const DateTime& date_time) noexcept
{
	return date_time + interval;
}

DateTime DateTime::operator-(const TimeInterval& interval) const noexcept
{
	DateTime date_time(minutes_ - interval.min());
	return date_time;
}

TimeInterval DateTime::operator-(const DateTime& date_time) const noexcept
{
	return TimeInterval::min(minutes_ - date_time.minutes_);
}

DateTime DateTime::operator++() noexcept
{
	++minutes_;
	return *this;
}

DateTime DateTime::operator++(int) noexcept
{
	DateTime date_time = *this;
	++minutes_;
	return date_time;
}

DateTime DateTime::operator--() noexcept
{
	--minutes_;
	return *this;
}

DateTime DateTime::operator--(int) noexcept
{
	DateTime date_time = *this;
	--minutes_;
	return *this;
}

DateTime& DateTime::operator+=(const TimeInterval& interval) noexcept
{
	minutes_ += interval.min();
	return *this;
}

DateTime& DateTime::operator-=(const TimeInterval& interval) noexcept
{
	minutes_ -= interval.min();
	return *this;
}

const DateTime DateTime::ORIGIN(0);

const std::string DateTime::DEFAULT_FORMAT = "dd MMM yy, HH:mm";

DateTime::DateTime(long long minutes) noexcept :
	minutes_(minutes)
{}
