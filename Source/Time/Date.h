    ////////////////////////////////////////
   //        YourLife by sqrt(-1)        //
  //                                    //
 //  File: Date.h                      //
////////////////////////////////////////

#pragma once

#include <string>
#include <compare>

namespace ylife
{

class TimeInterval;

enum class EMonth
{
	JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC
};

enum class EWeekDay
{
	MON = 1, TUE, WED, THU, FRI, SAT, SUN
};

std::string get_month_short_name(EMonth day);
std::string get_month_full_name(EMonth day);
std::string get_day_short_name(EWeekDay day);
std::string get_day_full_name(EWeekDay day);
	
struct SDate
{
	int year;
	EMonth month;
	int day;
};

class Date
{
	friend class DateTime;

private:
	int days_ = 0;

public:
	Date() noexcept = default;
	Date(const Date& date) noexcept = default;
	Date(SDate date) noexcept;
	Date(int year, EMonth month, int day) noexcept;

	SDate get_date() const noexcept;
	int get_year() const noexcept;
	EMonth get_month() const noexcept;
	int get_day() const noexcept;
	int get_day_of_year() const noexcept;
	int get_day_since_origin() const noexcept;
	TimeInterval get_time_since_new_year() const noexcept;
	TimeInterval get_time_since_origin() const noexcept;

	void set_date(SDate date) noexcept;
	void set_date(int year = 1, EMonth month = EMonth::JAN, int day = 1) noexcept;
	void set_year(int year) noexcept;
	void set_month(EMonth month) noexcept;
	void set_day(int day) noexcept;
	void set_day_of_year(int day) noexcept;
	void set_day_since_origin(int day) noexcept;

	std::string to_string(const std::string& format = DEFAULT_FORMAT) const;

	Date& operator=(const Date& date) noexcept = default;
	Date& operator=(SDate date) noexcept;

	std::strong_ordering operator<=>(const Date& date) noexcept;

	Date operator+() const noexcept;
	Date operator+(const TimeInterval& interval) const noexcept;
	friend Date operator+(const TimeInterval& interval, const Date& date) noexcept;
	Date operator-(const TimeInterval& interval) const noexcept;
	TimeInterval operator-(const Date& date) const noexcept;

	Date operator++() noexcept;
	Date operator++(int) noexcept;
	Date operator--() noexcept;
	Date operator--(int) noexcept;

	Date& operator+=(const TimeInterval& interval) noexcept;
	Date& operator-=(const TimeInterval& interval) noexcept;

	static constexpr int DAYS_IN_MONTH = 7;
	static constexpr int MONTHS_IN_YEAR = 12;
	static constexpr int DAYS_IN_YEAR = DAYS_IN_MONTH * MONTHS_IN_YEAR;

	static const Date ORIGIN;

	static const std::string DEFAULT_FORMAT;

private:
	Date(int days_since_origin) noexcept;
};

Date operator+(const TimeInterval& interval, const Date& date) noexcept;

}
