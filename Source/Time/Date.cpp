    ////////////////////////////////////////
   //        YourLife by sqrt(-1)        //
  //                                    //
 //  File: Date.cpp                    //
////////////////////////////////////////

#include "Date.h"

#include "../Util/Util.h"
#include "DateTime.h"
#include "TimeInterval.h"

using namespace ylife;

std::string ylife::get_month_short_name(EMonth month)
{
	switch (month)
	{
	case EMonth::JAN:
		return "JAN";
	case EMonth::FEB:
		return "FEB";
	case EMonth::MAR:
		return "MAR";
	case EMonth::APR:
		return "APR";
	case EMonth::MAY:
		return "MAY";
	case EMonth::JUN:
		return "JUN";
	case EMonth::JUL:
		return "JUL";
	case EMonth::AUG:
		return "AUG";
	case EMonth::SEP:
		return "SEP";
	case EMonth::OCT:
		return "OCT";
	case EMonth::NOV:
		return "NOV";
	case EMonth::DEC:
		return "DEC";
	default:
		return "???";
	}
}

std::string ylife::get_month_full_name(EMonth month)
{
	switch (month)
	{
	case EMonth::JAN:
		return "January";
	case EMonth::FEB:
		return "February";
	case EMonth::MAR:
		return "March";
	case EMonth::APR:
		return "April";
	case EMonth::MAY:
		return "May";
	case EMonth::JUN:
		return "June";
	case EMonth::JUL:
		return "July";
	case EMonth::AUG:
		return "August";
	case EMonth::SEP:
		return "September";
	case EMonth::OCT:
		return "October";
	case EMonth::NOV:
		return "November";
	case EMonth::DEC:
		return "December";
	default:
		return "Unknown";
	}
}

std::string ylife::get_day_short_name(EWeekDay day)
{
	switch (day)
	{
	case EWeekDay::MON:
		return "MON";
	case EWeekDay::TUE:
		return "TUE";
	case EWeekDay::WED:
		return "WED";
	case EWeekDay::THU:
		return "THU";
	case EWeekDay::FRI:
		return "FRI";
	case EWeekDay::SAT:
		return "SAT";
	case EWeekDay::SUN:
		return "SUN";
	default:
		return "???";
	}
}

std::string ylife::get_day_full_name(EWeekDay day)
{
	switch (day)
	{
	case EWeekDay::MON:
		return "Monday";
	case EWeekDay::TUE:
		return "Tuesday";
	case EWeekDay::WED:
		return "Wednesday";
	case EWeekDay::THU:
		return "Thursday";
	case EWeekDay::FRI:
		return "Friday";
	case EWeekDay::SAT:
		return "Saturday";
	case EWeekDay::SUN:
		return "Sunday";
	default:
		return "Unknown";
	}
}

Date::Date(SDate date) noexcept
{
	set_date(date);
}

Date::Date(int year, EMonth month, int day) noexcept
{
	set_date(year, month, day);
}

SDate Date::get_date() const noexcept
{
	return {
		.year = get_year(),
		.month = get_month(),
		.day = get_day()
	};
}

int Date::get_year() const noexcept
{
	return util::uniform_div(days_, DAYS_IN_YEAR) + 1;
}

EMonth Date::get_month() const noexcept
{
	// The first month is 1, not 0
	return static_cast<EMonth>((get_day_of_year() - 1) / DAYS_IN_MONTH + 1);
}

int Date::get_day() const noexcept
{
	return util::uniform_mod(days_, DAYS_IN_MONTH) + 1;
}

int Date::get_day_of_year() const noexcept
{
	return util::uniform_mod(days_, DAYS_IN_YEAR) + 1;
}

int Date::get_day_since_origin() const noexcept
{
	return days_ + 1;
}

TimeInterval Date::get_time_since_new_year() const noexcept
{
	return TimeInterval::days(util::uniform_mod(days_, DAYS_IN_YEAR));
}

TimeInterval Date::get_time_since_origin() const noexcept
{
	return TimeInterval::days(days_);
}

void Date::set_date(SDate date) noexcept
{
	set_date(date.year, date.month, date.day);
}

void Date::set_date(int year, EMonth month, int day) noexcept
{
	days_ =
		(year - 1) * DAYS_IN_YEAR +
		(static_cast<int>(month) - 1) * DAYS_IN_MONTH +
		(day - 1);
}

void Date::set_year(int year) noexcept
{
	days_ += (year - get_year()) * DAYS_IN_YEAR;
}

void Date::set_month(EMonth month) noexcept
{
	days_ += (static_cast<int>(month) - static_cast<int>(get_month())) * DAYS_IN_MONTH;
}

void Date::set_day(int day) noexcept
{
	days_ += day - get_day();
}

void Date::set_day_of_year(int day) noexcept
{
	days_ += day - get_day_of_year();
}

void Date::set_day_since_origin(int day) noexcept
{
	days_ = day - 1;
}

std::string Date::to_string(const std::string& format) const
{
	return DateTime(*this).to_string(format);
}

Date& Date::operator=(SDate date) noexcept
{
	set_date(date);
	return *this;
}

std::strong_ordering Date::operator<=>(const Date& date) noexcept
{
	return days_ <=> date.days_;
}

Date Date::operator+() const noexcept
{
	return *this;
}

Date Date::operator+(const TimeInterval& interval) const noexcept
{
	Date date(days_ + interval.days());
	return date;
}

Date ylife::operator+(const TimeInterval& interval, const Date& date) noexcept
{
	return date + interval;
}

Date Date::operator-(const TimeInterval& interval) const noexcept
{
	Date date(days_ - interval.days());
	return date;
}

TimeInterval Date::operator-(const Date& date) const noexcept
{
	return TimeInterval::days(days_ - date.days_);
}

Date Date::operator++() noexcept
{
	++days_;
	return *this;
}

Date Date::operator++(int) noexcept
{
	Date date = *this;
	++days_;
	return date;
}

Date Date::operator--() noexcept
{
	--days_;
	return *this;
}

Date Date::operator--(int) noexcept
{
	Date date = *this;
	--days_;
	return date;
}

Date& Date::operator+=(const TimeInterval& interval) noexcept
{
	days_ += interval.days();
	return *this;
}

Date& Date::operator-=(const TimeInterval& interval) noexcept
{
	days_ -= interval.days();
	return *this;
}

const Date Date::ORIGIN(0);

const std::string Date::DEFAULT_FORMAT = "dd MMM yy";

Date::Date(int days_since_origin) noexcept :
	days_(days_since_origin)
{}
