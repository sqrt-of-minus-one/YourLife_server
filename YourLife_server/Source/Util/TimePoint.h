    ////////////////////////////////////////
   //       YourLife by SnegirSoft       //
  //                                    //
 //  File: TimePoint.h                 //
////////////////////////////////////////

#pragma once

namespace ylife
{

class TimeInterval;

class TimePoint
{
public:
	struct Date
	{
		int year;
		int month;
		int day;
	};

	struct Time
	{
		int hour;
		int min;
	};

	TimePoint() noexcept;
	TimePoint(const TimePoint& point) noexcept;
	TimePoint(int year, int month, int day, int hour, int min) noexcept;
	TimePoint(Date date, Time time = MIDNIGHT) noexcept;
	
	Date get_date() const noexcept;
	Time get_time() const noexcept;
	int get_year() const noexcept;
	int get_month() const noexcept;
	int get_day() const noexcept;
	int get_hour() const noexcept;
	int get_min() const noexcept;

	void set_date(Date date) noexcept;
	void set_time(Time time) noexcept;
	void set_year(int year) noexcept;
	void set_month(int month) noexcept;
	void set_day(int day) noexcept;
	void set_hour(int hour) noexcept;
	void set_min(int min) noexcept;

	TimePoint& operator=(const TimePoint& point) noexcept;
	TimePoint operator+(const TimeInterval& interval) const noexcept;
	TimePoint operator-(const TimeInterval& interval) const noexcept;
	TimeInterval operator-(const TimePoint& point) const noexcept;
	TimePoint& operator+=(const TimeInterval& interval) noexcept;
	TimePoint& operator-=(const TimeInterval& interval) noexcept;
	bool operator==(const TimePoint& point) const noexcept;
	bool operator<(const TimePoint& point) const noexcept;
	bool operator>(const TimePoint& point) const noexcept;
	bool operator<=(const TimePoint& point) const noexcept;
	bool operator>=(const TimePoint& point) const noexcept;

	static const TimePoint BEGINNING;
	static const Date NEW_YEAR;
	static const Time MIDNIGHT;
private:
	TimePoint(long long time_min) noexcept;
	long long time_min_; // Minutes passed since the beginning
};

}
