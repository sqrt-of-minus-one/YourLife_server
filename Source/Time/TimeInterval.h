    ////////////////////////////////////////
   //        YourLife by sqrt(-1)        //
  //                                    //
 //  File: TimeInterval.h              //
////////////////////////////////////////

#pragma once

#include <compare>
#include <string>

namespace ylife
{

class TimeInterval
{
private:
	long long minutes_ = 0;

public:
	TimeInterval() noexcept = default;
	TimeInterval(const TimeInterval& interval) noexcept = default;

	long long min() const noexcept;
	long long hours() const noexcept;
	int days() const noexcept;
	int months() const noexcept;
	int years() const noexcept;

	void set_min(long long min) noexcept;
	void set_hours(long long hours) noexcept;
	void set_days(int days) noexcept;
	void set_months(int months) noexcept;
	void set_years(int years) noexcept;

	/* Format:
		#?		Any character after # remains the same
		-		minus sign if negative
		+		minus or plus sign
		y		years
		M		months of year
		MM		months of year, presicely 2 digits
		M*		months, total
		d		days of month
		dd		days of month, presicely 2 digits
		D		days of year
		DD		days of year, presicely 2 digits
		d*		days, total
		h		hours of day
		hh		hours of day, presicely 2 digits
		h*		hours, total
		m		minutes of hour
		mm		minutes of hour, presicely 2 digits
		md		minutes of day
		m*		minutes, total
	*/
	std::string to_string(const std::string& format = DEFAULT_FORMAT) const;

	TimeInterval& operator=(const TimeInterval& interval) noexcept = default;

	std::strong_ordering operator<=>(const TimeInterval& date_time) noexcept;

	TimeInterval operator+() const noexcept;
	TimeInterval operator-() const noexcept;
	TimeInterval operator+(const TimeInterval& interval) const noexcept;
	TimeInterval operator-(const TimeInterval& interval) const noexcept;
	TimeInterval operator*(long long number) const noexcept;
	friend TimeInterval operator*(long long number, const TimeInterval& interval) noexcept;
	long long operator/(const TimeInterval& interval) const;
	TimeInterval operator/(long long number) const;
	TimeInterval operator%(const TimeInterval& interval) const;

	TimeInterval operator++() noexcept;
	TimeInterval operator++(int) noexcept;
	TimeInterval operator--() noexcept;
	TimeInterval operator--(int) noexcept;

	TimeInterval& operator+=(const TimeInterval& interval) noexcept;
	TimeInterval& operator-=(const TimeInterval& interval) noexcept;
	TimeInterval& operator*=(long long number) noexcept;
	TimeInterval& operator/=(long long number);
	TimeInterval& operator%=(const TimeInterval& interval);

	static TimeInterval min(long long min) noexcept;
	static TimeInterval hours(long long hours) noexcept;
	static TimeInterval days(int days) noexcept;
	static TimeInterval months(int months) noexcept;
	static TimeInterval years(int years) noexcept;

	static const std::string DEFAULT_FORMAT;
};

TimeInterval operator*(long long number, const TimeInterval& interval) noexcept;

namespace time_literals
{

TimeInterval operator""_min(unsigned long long min) noexcept;
TimeInterval operator""_h(unsigned long long hours) noexcept;
TimeInterval operator""_d(unsigned long long days) noexcept;
TimeInterval operator""_mon(unsigned long long months) noexcept;
TimeInterval operator""_y(unsigned long long years) noexcept;

}

}
