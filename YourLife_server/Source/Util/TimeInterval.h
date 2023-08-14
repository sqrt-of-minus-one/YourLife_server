    ////////////////////////////////////////
   //       YourLife by SnegirSoft       //
  //                                    //
 //  File: TimeInterval.h              //
////////////////////////////////////////

#pragma once

namespace ylife
{

class TimePoint;

class TimeInterval
{
public:
	TimeInterval() noexcept;
	TimeInterval(const TimeInterval& interval) noexcept;

	int get_years() const noexcept;
	int get_months_total() const noexcept;
	int get_days_total() const noexcept;
	long long get_hours_total() const noexcept;
	long long get_mins_total() const noexcept;
	int get_months_in_year() const noexcept;
	int get_days_in_month() const noexcept;
	int get_hours_in_day() const noexcept;
	int get_mins_in_hour() const noexcept;

	TimeInterval& operator=(const TimeInterval& interval) noexcept;
	TimeInterval operator+() const noexcept;
	TimeInterval operator-() const noexcept;
	TimeInterval operator+(const TimeInterval& interval) const noexcept;
	TimeInterval operator-(const TimeInterval& interval) const noexcept;
	TimeInterval operator*(int value) const noexcept;
	TimeInterval operator*(double value) const noexcept;
	friend TimeInterval operator*(int value, const TimeInterval& interval) noexcept;
	friend TimeInterval operator*(double value, const TimeInterval& interval) noexcept;
	TimeInterval operator/(int value) const;
	TimeInterval operator/(double value) const;
	double operator/(const TimeInterval& interval) const;
	TimeInterval& operator+=(const TimeInterval& interval) noexcept;
	TimeInterval& operator-=(const TimeInterval& interval) noexcept;
	TimeInterval& operator*=(int value) noexcept;
	TimeInterval& operator*=(double value) noexcept;
	TimeInterval& operator/=(int value);
	TimeInterval& operator/=(double value);
	bool operator==(const TimeInterval& interval) const noexcept;
	bool operator<(const TimeInterval& interval) const noexcept;
	bool operator>(const TimeInterval& interval) const noexcept;
	bool operator<=(const TimeInterval& interval) const noexcept;
	bool operator>=(const TimeInterval& interval) const noexcept;
	friend TimeInterval operator""_min(unsigned long long mins) noexcept;
	friend TimeInterval operator""_h(unsigned long long hours) noexcept;
	friend TimeInterval operator""_d(unsigned long long days) noexcept;
	friend TimeInterval operator""_mon(unsigned long long months) noexcept;
	friend TimeInterval operator""_y(unsigned long long years) noexcept;
private:
	TimeInterval(long long mins) noexcept;
	long long time_min_; // Minutes passed since the beginning
};

TimeInterval operator""_min(unsigned long long mins) noexcept;
TimeInterval operator""_h(unsigned long long hours) noexcept;
TimeInterval operator""_d(unsigned long long days) noexcept;
TimeInterval operator""_mon(unsigned long long months) noexcept;
TimeInterval operator""_y(unsigned long long years) noexcept;

}

using ylife::operator""_min;
using ylife::operator""_h;
using ylife::operator""_d;
using ylife::operator""_mon;
using ylife::operator""_y;
