

#include <khronos/hebrew_calendar.hpp>
#include <khronos\julian_calendar.hpp>
#include<khronos\gregorian_calendar.hpp>
#include<khronos\timeofday.hpp>
#include <khronos\def.hpp>
#include <cassert>
#include <sstream>
#include <ctime>
#include <iomanip>


namespace khronos {


	//hebrew leap year
	inline bool is_hebrew_leapyear(year_t y)
	{
		return (((7 * y) + 1) % 19 < 7);
	};

	//Default Constructor
	Hebrew::Hebrew() : hour_(0), minute_(0), second_(0)
	{
		time_t nowTime = time(NULL);
		struct tm tmNow;
		localtime_s(&tmNow, &nowTime);


		year_ = year_t(tmNow.tm_year + 1900);
		month_ = month_t(tmNow.tm_mon + 1);
		day_ = day_t(tmNow.tm_mday);
		

		jd_ = gregorian_to_jd(year_, month_, day_);
		jd_to_hebrew(jd_, year_, month_, day_);
	}

	//Constructor passing timet
	Hebrew::Hebrew(now_t t)
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
		jd_to_hebrew(jd_, year_, month_, day_, hour_, minute_, second_);
	}


	//delayOfWeek
	day_t delayOfWeek(year_t year)
	{
		month_t month = static_cast<month_t>(floor((235 * year - 234) / 19.0));
		month_t parts = static_cast<month_t>(12084 + 13753 * month);
		day_t day = static_cast<day_t>(month * 29 + floor(parts / 25920.0));

		if ((3 * (day + 1) % 7) < 3)
			day = day + 1;

		return day;
	}
	//delayAdjacentYear
	day_t delayAdjacentYear(year_t year)
	{
		day_t last = delayOfWeek(year - 1);
		day_t present = delayOfWeek(year);
		day_t next = delayOfWeek(year + 1);
		day_t days = 0;

		if (next - present == 356)
			days = 2;
		else if (next - present != 356 && present - last == 382)
			days = 1;

		return days;
	}
	//daysInYear
	day_t daysInYear(year_t year)
	{
		return static_cast<day_t>(hebrew_to_jd(year + 1, 7, 1) - hebrew_to_jd(year, 7, 1));
	}

	//hebrew_days_in_month
	day_t hebrew_days_in_month(year_t year, month_t month)
	{
		day_t day = 30;
		if (month == 2 || month == 4 || month == 6 || month == 10 || month == 13)
			day = 29;
		else if (month == 12 && is_hebrew_leapyear(year) != true)
			day = 29;
		else if (month == 8 && daysInYear(year) % 10 != 5)
			day = 29;
		else if (month == 9 && daysInYear(year) % 10 == 3)
			day = 29;

		return day;

	}

	//hebrewAddYear
	void hebrewAddYear(year_t& year, month_t& month, day_t& day, year_t n)
	{
		year = year + n;
		month_t m = month;
		day_t d = day;

		if (m == 12 && d == 30 && (is_hebrew_leapyear(year) == false))
		{
			day = 29;
		}

	}

	// hebrewAddYear
	jd_t hebrewAddYear(Hebrew const g, jd_t n)
	{
		year_t year = g.year();
		month_t month = g.month();
		day_t day = g.day();

		hebrewAddYear(year, month, day, static_cast<year_t>(n));
		return hebrew_to_jd(year, month, day, g.hour(), g.minute(), g.second());
	}


	//hebrew_add_months
	void hebrew_add_months(year_t& year, month_t& month, day_t& day, month_t n)
	{
		year = year + n / 12;
		month = month + n % 12;
		long adjust = (month - 1) / 12 + (month - 12) / 12;
		year = year + adjust;
		month = month - (adjust * 12);
		day = min(day, hebrew_days_in_month(month, is_hebrew_leapyear(year)));
	}

	//operator +
	Hebrew operator + (Hebrew const& g, detail::packaged_month_integer months)
	{
		year_t y = g.year();
		month_t m = g.month();
		day_t d = g.day();

		hebrew_add_months(y, m, d, months.nMonths_);
		return Hebrew(y, m, d, g.hour(), g.minute(), g.second());
	}
	// operator -
	Hebrew operator -(Hebrew const& g, detail::packaged_month_integer months)
	{
		year_t y = g.year();
		month_t m = g.month();
		day_t d = g.day();

		hebrew_add_months(y, m, d, 0 - months.nMonths_);
		return Hebrew(y, m, d, g.hour(), g.minute(), g.second());
	}

};//end namepsace