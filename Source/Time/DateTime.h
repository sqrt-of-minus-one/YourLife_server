    ////////////////////////////////////////
   //        YourLife by sqrt(-1)        //
  //                                    //
 //  File: DateTime.h                  //
////////////////////////////////////////

#pragma once

#include "Date.h"
#include "Time.h"

namespace ylife
{

struct SDateTime
{
	int year;
	EMonth month;
	int day;
	int hour;
	int min;

	static SDateTime combine(SDate date, STime time = Time::MIDNIGHT.get_time()) noexcept;
	SDate date() const noexcept;
	STime time() const noexcept;
};

// In the game 1 month = 1 week = 7 days
class DateTime
{
	friend class Date;
	friend class Time;

private:
	// minutes_ = 0 means the midnight of 1 Jan 1
	long long minutes_ = 0;

public:
	DateTime() noexcept = default;
	DateTime(const DateTime& date_time) noexcept = default;
	// Similarly to Date and Time, ill-formed dates and times are supported by the constructors
	DateTime(SDateTime time) noexcept;
	DateTime(SDate date, STime time = Time::MIDNIGHT.get_time()) noexcept;
	DateTime(Date date, Time time = Time::MIDNIGHT) noexcept;
	DateTime(int year, EMonth month, int day, int hour = 0, int min = 0) noexcept;

	// The methods work similarly to those of Date and Time classes
	SDateTime get_date_time() const noexcept;
	SDate get_date() const noexcept;
	Date date() const noexcept;
	int get_year() const noexcept;
	EMonth get_month() const noexcept;
	int get_day() const noexcept;
	int get_day_of_year() const noexcept;
	int get_day_since_origin() const noexcept;

	STime get_time() const noexcept;
	Time time() const noexcept;
	int get_hour() const noexcept;
	int get_min() const noexcept;
	int get_min_since_midnight() const noexcept;
	long long get_min_since_origin() const noexcept;
	TimeInterval get_time_since_new_year() const noexcept;
	TimeInterval get_time_since_origin() const noexcept;

	void set_date_time(SDateTime date_time) noexcept;
	void set_date_time(SDate date, STime time = Time::MIDNIGHT.get_time()) noexcept;
	void set_date_time(Date date, Time time = Time::MIDNIGHT) noexcept;
	void set_date_time(int year, EMonth month, int day, int hour = 0, int min = 0) noexcept;

	void set_date(SDate date) noexcept;
	void set_date(Date date) noexcept;
	void set_date(int year, EMonth month, int day) noexcept;
	void set_year(int year) noexcept;
	void set_month(EMonth month) noexcept;
	void set_day(int day) noexcept;
	void set_day_of_year(int day) noexcept;
	void set_day_since_origin(int day) noexcept;

	void set_time(STime time) noexcept;
	void set_time(Time time) noexcept;
	void set_time(int hour = 0, int min = 0) noexcept;
	void set_hour(int hour) noexcept;
	void set_min(int min) noexcept;
	void set_min_since_midnight(int min) noexcept;
	void set_min_since_origin(long long min) noexcept;

	/* Format:
		#?      any character after # (except '|') remains the same, e.g.:
		            "day: d" => "1am3: 1", "#d#a#y: d" => "day: 1"
		            "hhours, mmin" => "12ours, 03in", "h#hours, m#min" => "12hours, 3min"
		#|      is removed from the string; can be used to separate different groups, e.g.:
		            "MMMM" => "January", "MM#|MM" => "0101"
		y		year, at least 1 digit
		yy		year, at least 2 digits (or minus and 1 digit if negative)
		yyy		year, at least 3 digits (or minus and 2 digits if negative)
		yyyy	year, at least 4 digits (or minus and 3 digits if negative)
		M		month, at least 1 digit
		MM		month, precisely 2 digit
		MMM		month, short name
		MMMM	month, full name
		d		day of month, precisely 1 digit
		dd		day of month, precisely 2 digits
		ddd		day of week, short name
		dddd	day of week, full name
		D		day of year, at least 1 digit
		DD		day of year, presicely 2 digits
		h		hours, 12-h format, at least 1 digit
		hh		hours, 12-h format, precisely 2 digits
		H		hours, 24-h format, at least 1 digit
		HH		hours, 24-h format, precisely 2 digits
		a		am/pm
		a.		a.m./p.m.
		A		AM/PM
		A.		A.M./P.M.
		m		minutes, at least 1 digit
		mm		minutes, precisely 2 digits
	*/
	std::string to_string(const std::string& format = DEFAULT_FORMAT) const;

	DateTime& operator=(const DateTime& date_time) noexcept = default;
	DateTime& operator=(SDateTime date_time) noexcept;

	std::strong_ordering operator<=>(const DateTime& date_time) noexcept;

	DateTime operator+() const noexcept;
	DateTime operator+(const TimeInterval& interval) const noexcept;
	friend DateTime operator+(const TimeInterval& interval, const DateTime& date_time) noexcept;
	DateTime operator-(const TimeInterval& interval) const noexcept;
	TimeInterval operator-(const DateTime& date_time) const noexcept;

	// Increase/decrease by 1 minute
	DateTime operator++() noexcept;
	DateTime operator++(int) noexcept;
	DateTime operator--() noexcept;
	DateTime operator--(int) noexcept;

	DateTime& operator+=(const TimeInterval& interval) noexcept;
	DateTime& operator-=(const TimeInterval& interval) noexcept;

	static constexpr int MIN_IN_MONTH = Time::MIN_IN_DAY * Date::DAYS_IN_MONTH;
	static constexpr int MIN_IN_YEAR = Time::MIN_IN_DAY * Date::DAYS_IN_YEAR;

	static const DateTime ORIGIN; // 00:00 of 1 Jan 1

	static const std::string DEFAULT_FORMAT;

private:
	DateTime(long long minutes) noexcept;
};

DateTime operator+(const TimeInterval& interval, const DateTime& date_time) noexcept;

}
