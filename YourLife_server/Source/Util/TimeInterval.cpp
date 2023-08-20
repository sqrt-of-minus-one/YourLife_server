    ////////////////////////////////////////
   //       YourLife by SnegirSoft       //
  //                                    //
 //  File: TimeInterval.cpp            //
////////////////////////////////////////

#include "TimeInterval.h"

#include <stdexcept>

using namespace ylife;

TimeInterval::TimeInterval() noexcept :
	time_min_(0ll)
{}

TimeInterval::TimeInterval(const TimeInterval& interval) noexcept :
	time_min_(interval.time_min_)
{}

int TimeInterval::get_years() const noexcept
{
	return static_cast<int>(time_min_ / 120'960);
}

int TimeInterval::get_months_total() const noexcept
{
	return static_cast<int>(time_min_ / 10'080);
}

int TimeInterval::get_days_total() const noexcept
{
	return static_cast<int>(time_min_ / 1440);
}

long long TimeInterval::get_hours_total() const noexcept
{
	return time_min_ / 60;
}

long long TimeInterval::get_mins_total() const noexcept
{
	return time_min_;
}

int TimeInterval::get_months_in_year() const noexcept
{
	return static_cast<int>(time_min_ / 10'080 % 12);
}

int TimeInterval::get_days_in_month() const noexcept
{
	return static_cast<int>(time_min_ / 1440 % 7);
}

int TimeInterval::get_hours_in_day() const noexcept
{
	return static_cast<int>(time_min_ / 60 % 24);
}

int TimeInterval::get_mins_in_hour() const noexcept
{
	return static_cast<int>(time_min_ % 60);
}

TimeInterval& TimeInterval::operator=(const TimeInterval& interval) noexcept
{
	time_min_ = interval.time_min_;
	return *this;
}

TimeInterval TimeInterval::operator+() const noexcept
{
	return *this;
}

TimeInterval TimeInterval::operator-() const noexcept
{
	return TimeInterval(-time_min_);
}

TimeInterval TimeInterval::operator+(const TimeInterval& interval) const noexcept
{
	return TimeInterval(time_min_ + interval.time_min_);
}

TimeInterval TimeInterval::operator-(const TimeInterval& interval) const noexcept
{
	return TimeInterval(time_min_ - interval.time_min_);
}

TimeInterval TimeInterval::operator*(int value) const noexcept
{
	return TimeInterval(time_min_ * value);
}

TimeInterval TimeInterval::operator*(double value) const noexcept
{
	return TimeInterval(static_cast<long long>(time_min_ * value));
}

TimeInterval ylife::operator*(int value, const TimeInterval& interval) noexcept
{
	return TimeInterval(value * interval.time_min_);
}

TimeInterval ylife::operator*(double value, const TimeInterval& interval) noexcept
{
	return TimeInterval(static_cast<long long>(value * interval.time_min_));
}

TimeInterval TimeInterval::operator/(int value) const
{
	if (value == 0)
	{
		throw std::domain_error("Attempt to divide by zero");
	}
	return TimeInterval(time_min_ / value);
}

TimeInterval TimeInterval::operator/(double value) const
{
	if (value == 0.)
	{
		throw std::domain_error("Attempt to divide by zero");
	}
	return TimeInterval(static_cast<long long>(time_min_ / value));
}

double TimeInterval::operator/(const TimeInterval& interval) const
{
	if (interval.time_min_ == 0)
	{
		throw std::domain_error("Attempt to divide by zero");
	}
	return static_cast<long double>(time_min_) / interval.time_min_;
}

TimeInterval& TimeInterval::operator+=(const TimeInterval& interval) noexcept
{
	time_min_ += interval.time_min_;
	return *this;
}

TimeInterval& TimeInterval::operator-=(const TimeInterval& interval) noexcept
{
	time_min_ -= interval.time_min_;
	return *this;
}

TimeInterval& TimeInterval::operator*=(int value) noexcept
{
	time_min_ *= value;
	return *this;
}

TimeInterval& TimeInterval::operator*=(double value) noexcept
{
	time_min_ *= value;
	return *this;
}

TimeInterval& TimeInterval::operator/=(int value)
{
	if (value == 0)
	{
		throw std::domain_error("Attempt to divide by zero");
	}
	time_min_ /= value;
	return *this;
}

TimeInterval& TimeInterval::operator/=(double value)
{
	if (value == 0.)
	{
		throw std::domain_error("Attempt to divide by zero");
	}
	time_min_ /= value;
	return *this;
}

bool TimeInterval::operator==(const TimeInterval& interval) const noexcept
{
	return time_min_ == interval.time_min_;
}

bool TimeInterval::operator<(const TimeInterval& interval) const noexcept
{
	return time_min_ < interval.time_min_;
}

bool TimeInterval::operator>(const TimeInterval& interval) const noexcept
{
	return time_min_ > interval.time_min_;
}

bool TimeInterval::operator<=(const TimeInterval& interval) const noexcept
{
	return time_min_ <= interval.time_min_;
}

bool TimeInterval::operator>=(const TimeInterval& interval) const noexcept
{
	return time_min_ >= interval.time_min_;
}

TimeInterval ylife::operator""_min(unsigned long long mins) noexcept
{
	return TimeInterval(mins);
}

TimeInterval ylife::operator""_h(unsigned long long hours) noexcept
{
	return TimeInterval(hours * 60);
}

TimeInterval ylife::operator""_d(unsigned long long days) noexcept
{
	return TimeInterval(days * 1440);
}

TimeInterval ylife::operator""_mon(unsigned long long months) noexcept
{
	return TimeInterval(months * 10'080);
}

TimeInterval ylife::operator""_y(unsigned long long years) noexcept
{
	return TimeInterval(years * 120'960);
}

TimeInterval::TimeInterval(long long mins) noexcept :
	time_min_(mins)
{}
