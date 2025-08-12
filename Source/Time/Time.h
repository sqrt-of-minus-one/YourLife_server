    ////////////////////////////////////////
   //        YourLife by sqrt(-1)        //
  //                                    //
 //  File: Time.h                      //
////////////////////////////////////////

#pragma once

#include <string>
#include <compare>

namespace ylife
{

class TimeInterval;

struct STime
{
	int hour;
	int min;
};

// The time in the game works like the real time
// The smallest time unit is a minute
class Time
{
	friend class DateTime;

private:
	// minutes_ = 0 means midnight
	// minutes_ = 1 means 00:01
	// minutes_ = 61 means 01:01
	int minutes_ = 0;

public:
	Time(const Time& time) noexcept = default;
	Time(STime time) noexcept;
	// Ill-formed times are supported by the constructor, e.g.:
	// 25:09 => 01:09
	// 12:64 => 13:04
	// 23:143 => 01:23
	// 05:-15 => 04:45
	// -05:-05 => 18:55
	Time(int hour = 0, int min = 0) noexcept;

	STime get_time() const noexcept;
	int get_hour() const noexcept;
	int get_min() const noexcept;
	int get_min_since_midnight() const noexcept; // 0 if midnight
	TimeInterval get_time_since_midnight() const noexcept;

	void set_time(STime time) noexcept;
	void set_time(int hour = 0, int min = 0) noexcept;
	void set_hour(int hour) noexcept;
	void set_min(int min) noexcept;
	void set_min_since_midnight(int min) noexcept; // 0 if midnight

	// See DateTime::to_string for the format reference
	std::string to_string(const std::string& format = DEFAULT_FORMAT) const;

	Time& operator=(const Time& time) noexcept = default;
	Time& operator=(STime time) noexcept;

	std::strong_ordering operator<=>(const Time& time) noexcept;

	Time operator+() const noexcept;
	Time operator-() const noexcept; // Same as operator~
	Time operator+(const TimeInterval& interval) const noexcept;
	friend Time operator+(const TimeInterval& interval, const Time& time) noexcept;
	Time operator-(const TimeInterval& interval) const noexcept;
	TimeInterval operator-(const Time& time) const noexcept;
	Time operator~() const noexcept; // Time before the next midnight: ~21:45 = 03:15

	// Increase/decrease the time by 1 minute
	Time operator++() noexcept;
	Time operator++(int) noexcept;
	Time operator--() noexcept;
	Time operator--(int) noexcept;

	Time& operator+=(const TimeInterval& interval) noexcept;
	Time& operator-=(const TimeInterval& interval) noexcept;

	static constexpr int MIN_IN_HOUR = 60;
	static constexpr int HOURS_IN_DAY = 24;
	static constexpr int MIN_IN_DAY = MIN_IN_HOUR * HOURS_IN_DAY;

	static const Time MIDNIGHT;
	static const Time NOON;

	static const std::string DEFAULT_FORMAT;

private:
	// Makes the minutes_ be between 0 and MIN_IN_DAY
	void fix_time_() noexcept;
};

Time operator+(const TimeInterval& interval, const Time& time) noexcept;

}
