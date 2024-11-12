/**	@file Islamic.cpp
	@author Garth Santor
	@date 2013-09-20

	Islamic calendar class implementation.
	*/

#include <khronos/islamic_calendar.hpp>

namespace khronos {

	//IsLeapYear
	inline bool is_islamic_leapyear(year_t y)
	{
		return (((11 * y) + 14) % 30 < 11);
	};

	// islamic_days_in_month
	day_t islamic_days_in_month(month_t m, bool bl)
	{
		if ((m % 2 == 1) || (m == 12 && bl))
			return 30;
		else
			return 29;
	}


// Default Constructor for Islamic
	Islamic::Islamic() : hour_(0), minute_(0), second_(0) {
		time_t nowTime = time(NULL);  // Get current system time
		struct tm tmNow;
		localtime_s(&tmNow, &nowTime);  // Convert system time to local time

		// Convert the current Gregorian date and time to an Islamic date
		jd_ = gregorian_to_jd(
			year_t(tmNow.tm_year + 1900),
			month_t(tmNow.tm_mon + 1),
			day_t(tmNow.tm_mday)
		);

		// Convert the Julian day to the Islamic calendar
		jd_to_islamic(jd_, year_, month_, day_);
	}


	Islamic::Islamic(now_t t)
	{
		time_t nowTime = time(NULL);
		struct tm tmNow;
		localtime_s(&tmNow, &nowTime);

		year_ = year_t(tmNow.tm_year + 1900);
		month_ = month_t(tmNow.tm_mon + 1);
		day_ = day_t(tmNow.tm_mday);
		hour_ = 0;
		minute_ = 0;
		second_ = 0;

		if (t == WTIMEOFDAY)
		{
			hour_ = hour_t(tmNow.tm_hour);
			minute_ = minute_t(tmNow.tm_min);
			second_ = second_t(tmNow.tm_sec);
		}

		jd_ = gregorian_to_jd(year_, month_, day_, hour_, minute_, second_);
		jd_to_islamic(jd_, year_, month_, day_,hour_,minute_,second_);
	}

	//islamic_add_months
	void islamic_add_months(year_t& year, month_t& month, day_t& day, month_t n)
	{
		year = year + n / 12;
		month = month + n % 12;
		long adjust = (month - 1) / 12 + (month - 12) / 12;
		year = year + adjust;
		month = month - (adjust * 12);
		day = min(day, islamic_days_in_month(month, is_islamic_leapyear(year)));
	}

	//islamicAddYear(
	void islamicAddYear(year_t& year, month_t& month, day_t& day, year_t n)
	{
		year = year + n;
		month_t m = month;
		day_t d = day;

		if (m == 12 && d == 30 && (is_islamic_leapyear(year) == false))
		{
			day = 29;
		}

	}

	//islamicAddYear
	jd_t islamicAddYear(Islamic const g, jd_t n)
	{
		year_t year = g.year();
		month_t month = g.month();
		day_t day = g.day();

		islamicAddYear(year, month, day, static_cast<year_t>(n));
		return islamic_to_jd(year, month, day, g.hour(), g.minute(), g.second());
	}

	// operator + months
	Islamic operator + (Islamic const& g, detail::packaged_month_integer months)
	{
		year_t y = g.year();
		month_t m = g.month();
		day_t d = g.day();

		islamic_add_months(y, m, d, months.nMonths_);
		return Islamic(y, m, d, g.hour(), g.minute(), g.second());
	}

	// operator - months
	Islamic operator -(Islamic const& g, detail::packaged_month_integer months)
	{
		year_t y = g.year();
		month_t m = g.month();
		day_t d = g.day();

		islamic_add_months(y, m, d, 0 - months.nMonths_);
		return Islamic(y, m, d, g.hour(), g.minute(), g.second());
	}


};//end namespace khronos