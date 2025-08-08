    ////////////////////////////////////////
   //        YourLife by sqrt(-1)        //
  //                                    //
 //  File: Time.cpp                    //
////////////////////////////////////////

#include "Time.h"

#include "../Util/Util.h"
#include "DateTime.h"
#include "TimeInterval.h"

using namespace ylife;

Time::Time(int hour, int min) noexcept :
	minutes_(hour * MIN_IN_HOUR + min)
{
	fix_time_();
}

Time::Time(STime time) noexcept :
	Time(time.hour, time.min)
{}

STime Time::get_time() const noexcept
{
	return {
		.hour = get_hour(),
		.min = get_min()
	};
}

int Time::get_hour() const noexcept
{
	return minutes_ / MIN_IN_HOUR;
}

int Time::get_min() const noexcept
{
	return minutes_ % MIN_IN_HOUR;
}

int Time::get_min_since_midnight() const noexcept
{
	return minutes_;
}

TimeInterval Time::get_time_since_midnight() const noexcept
{
	return TimeInterval::min(minutes_);
}

void Time::set_time(STime time) noexcept
{
	set_time(time.hour, time.min);
}

void Time::set_time(int hour, int min) noexcept
{
	set_min_since_midnight(hour * MIN_IN_HOUR + min);
}

void Time::set_hour(int hour) noexcept
{
	minutes_ += (hour - get_hour()) * MIN_IN_HOUR;
	fix_time_();
}

void Time::set_min(int min) noexcept
{
	minutes_ += min - get_min();
	fix_time_();
}

void Time::set_min_since_midnight(int min) noexcept
{
	minutes_ = min;
	fix_time_();
}

std::string Time::to_string(const std::string& format) const
{
	return DateTime(Date::ORIGIN, *this).to_string(format);
}

Time& Time::operator=(STime time) noexcept
{
	set_time(time);
	return *this;
}

std::strong_ordering Time::operator<=>(const Time& time) noexcept
{
	return minutes_ <=> time.minutes_;
}

Time Time::operator+() const noexcept
{
	return *this;
}

Time Time::operator-() const noexcept
{
	Time time(MIN_IN_DAY - minutes_);
	return time;
}

Time Time::operator+(const TimeInterval& interval) const noexcept
{
	Time time(minutes_ + interval.min() % MIN_IN_DAY);
	return time;
}

Time ylife::operator+(const TimeInterval& interval, const Time& time) noexcept
{
	return time + interval;
}

Time Time::operator-(const TimeInterval& interval) const noexcept
{
	Time time(minutes_ - interval.min() % MIN_IN_DAY);
	return time;
}

TimeInterval Time::operator-(const Time& time) const noexcept
{
	return TimeInterval::min(minutes_ - time.minutes_);
}

Time Time::operator~() const noexcept
{
	return -*this;
}

Time Time::operator++() noexcept
{
	++minutes_;
	fix_time_();
	return *this;
}

Time Time::operator++(int) noexcept
{
	Time time = *this;
	++minutes_;
	fix_time_();
	return time;
}

Time Time::operator--() noexcept
{
	--minutes_;
	fix_time_();
	return *this;
}

Time Time::operator--(int) noexcept
{
	Time time = *this;
	--minutes_;
	fix_time_();
	return time;
}

Time& Time::operator+=(const TimeInterval& interval) noexcept
{
	set_min_since_midnight(minutes_ + interval.min() % MIN_IN_DAY);
	return *this;
}

Time& Time::operator-=(const TimeInterval& interval) noexcept
{
	set_min_since_midnight(minutes_ - interval.min() % MIN_IN_DAY);
	return *this;
}

const Time Time::MIDNIGHT(0, 0);
const Time Time::NOON(12, 0);

const std::string Time::DEFAULT_FORMAT = "HH:mm";

void Time::fix_time_() noexcept
{
	minutes_ = util::uniform_mod(minutes_, MIN_IN_DAY);
}
