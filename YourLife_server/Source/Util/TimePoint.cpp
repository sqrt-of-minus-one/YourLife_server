    ////////////////////////////////////////
   //       YourLife by SnegirSoft       //
  //                                    //
 //  File: TimePoint.cpp               //
////////////////////////////////////////

#include "TimePoint.h"

#include "TimeInterval.h"

using namespace ylife;

TimePoint::TimePoint() noexcept :
	time_min_(0ll)
{}

TimePoint::TimePoint(const TimePoint& point) noexcept :
	time_min_(point.time_min_)
{}

TimePoint::TimePoint(int year, int month, int day, int hour, int min) noexcept :
	time_min_((((year * 12ll + month) * 7 + day) * 24 + hour) * 60 + min)
{}

TimePoint::TimePoint(Date date, Time time) noexcept :
	TimePoint(date.year, date.month, date.day, time.hour, time.min)
{}

TimePoint::Date TimePoint::get_date() const noexcept
{
	Date date;
	date.year = get_year();
	date.month = get_month();
	date.day = get_day();
	return date;
}

TimePoint::Time TimePoint::get_time() const noexcept
{
	Time time;
	time.hour = get_hour();
	time.min = get_min();
	return time;
}

int TimePoint::get_year() const noexcept
{
	return static_cast<int>(time_min_ / 120'960);
}

int TimePoint::get_month() const noexcept
{
	return static_cast<int>(time_min_ / 10'080 % 12);
}

int TimePoint::get_day() const noexcept
{
	return static_cast<int>(time_min_ / 1440 % 7);
}

int TimePoint::get_hour() const noexcept
{
	return static_cast<int>(time_min_ / 60 % 24);
}

int TimePoint::get_min() const noexcept
{
	return static_cast<int>(time_min_ % 60);
}

void TimePoint::set_date(Date date) noexcept
{
	time_min_ %= 1440; // Now it's only time without date
	time_min_ += ((date.year * 12ll + date.month) * 7 + date.day) * 1440;
}

void TimePoint::set_time(Time time) noexcept
{
	time_min_ -= time_min_ % 1440; // Now it's midnight
	time_min_ += time.min + time.hour * 60;
}

void TimePoint::set_year(int year) noexcept
{
	time_min_ += (year - get_year()) * 120'960ll;
}

void TimePoint::set_month(int month) noexcept
{
	time_min_ += (month - get_month()) * 10'080ll;
}

void TimePoint::set_day(int day) noexcept
{
	time_min_ += (day - get_day()) * 1440;
}

void TimePoint::set_hour(int hour) noexcept
{
	time_min_ += (hour - get_hour()) * 60;
}

void TimePoint::set_min(int min) noexcept
{
	time_min_ += min - get_min();
}

TimePoint& TimePoint::operator=(const TimePoint& point) noexcept
{
	time_min_ = point.time_min_;
	return *this;
}

TimePoint TimePoint::operator+(const TimeInterval& interval) const noexcept
{
	return TimePoint(time_min_ + interval.get_mins_total());
}

TimePoint TimePoint::operator-(const TimeInterval& interval) const noexcept
{
	return TimePoint(time_min_ - interval.get_mins_total());
}

TimeInterval TimePoint::operator-(const TimePoint& point) const noexcept
{
	return operator""_min(time_min_ - point.time_min_);
}

TimePoint& TimePoint::operator+=(const TimeInterval& interval) noexcept
{
	time_min_ += interval.get_mins_total();
	return *this;
}

TimePoint& TimePoint::operator-=(const TimeInterval& interval) noexcept
{
	time_min_ -= interval.get_mins_total();
	return *this;
}

bool TimePoint::operator==(const TimePoint& point) const noexcept
{
	return time_min_ == point.time_min_;
}

bool TimePoint::operator<(const TimePoint& point) const noexcept
{
	return time_min_ < point.time_min_;
}

bool TimePoint::operator>(const TimePoint& point) const noexcept
{
	return time_min_ > point.time_min_;
}

bool TimePoint::operator<=(const TimePoint& point) const noexcept
{
	return time_min_ <= point.time_min_;
}

bool TimePoint::operator>=(const TimePoint& point) const noexcept
{
	return time_min_ >= point.time_min_;
}

const TimePoint TimePoint::BEGINNING;
const TimePoint::Date TimePoint::NEW_YEAR { 0, 0, 0 };
const TimePoint::Time TimePoint::MIDNIGHT { 0, 0 };

TimePoint::TimePoint(long long time_min) noexcept :
	time_min_(time_min)
{}
