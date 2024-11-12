/**	@file	gregorian.cpp
	@author	Garth Santor
	@date	2013-09-19

	Gregorian calendar class implementation.
	*/

#include <khronos/gregorian_calendar.hpp>
#include<khronos\def.hpp>
#include <cassert>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <algorithm>

using namespace std;
namespace khronos {

	
	//DEFAULT CONSTRUCTOR
	Gregorian::Gregorian() {

		time_t nowTime = time(NULL);
		struct tm tmNow;
		localtime_s(&tmNow, &nowTime);

		year_ = year_t(tmNow.tm_year + 1900);
		month_ = month_t(tmNow.tm_mon + 1);
		day_ = day_t(tmNow.tm_mday);

		hour_ = hour_t(tmNow.tm_hour);
		minute_ = minute_t(tmNow.tm_min);
		second_ = second_t(tmNow.tm_sec);
	}//end default contructor

	//DEFAULT CONSTRUCTOR passing year,month,day
	Gregorian::Gregorian(year_t y, month_t m, day_t d)
	{
		assert(y >= -4800);
		assert(1 <= m);
		assert(m <= 12);
		assert(1 <= d);
		assert(d <= gregorian_days_in_month(m, is_gregorian_leapyear(y)));

		year_ = y;
		month_ = m;
		day_ = d;
		hour_ = 0;
		minute_ = 0;
		second_ = 0;
	}

	//toString Method
/** Print the Gregorian Date as a string. */
	std::string Gregorian::to_string() const {
		std::ostringstream oss;

		// Get the day of the week (0 = Sunday, 1 = Monday, ..., 6 = Saturday)
		day_t dow = day_of_week(to_jd());
		oss << civil::day_name(dow) << ", ";  // day of the week

		// Add the month name and day of the month
		oss << gregorian_month_name(month_) << ' ' << static_cast<unsigned>(day_) << ' ';

		// Handle the year and add BCE/CE appropriately
		if (year_ <= 0) {
			oss << (-year_ + 1) << " BCE, ";
		}
		else {
			oss << year_ << " CE, ";
		}

		// Convert hour to 12-hour format and append AM/PM
		hour_t hour12 = (hour_ % 12 == 0) ? 12 : hour_ % 12;  // Convert 24-hour to 12-hour format
		std::string period = (hour_ >= 12) ? "pm" : "am";  // Determine AM/PM

		// Do not pad the hour with leading zeros, but pad minutes and seconds
		oss << hour12 << ":"  // No leading zero for hour
			<< std::setw(2) << std::setfill('0') << minute_ << ":"  // Leading zero for minutes
			<< std::setw(2) << std::setfill('0') << second_ << ' '  // Leading zero for seconds
			<< period;

		return oss.str();
	}

	Gregorian Gregorian::operator+(detail::packaged_year_real const&)
	{
		return Gregorian();
	}

	Gregorian Gregorian::operator-(detail::packaged_year_real const&)
	{
		return Gregorian();
	}

	Gregorian Gregorian::operator+(detail::packaged_month_real const&)
	{
		return Gregorian();
	}

	Gregorian Gregorian::operator-(detail::packaged_month_real const&)
	{
		return Gregorian();
	}

	/** Gregorian + (integer year) operator. */
	Gregorian operator + (Gregorian const& dt, detail::packaged_year_integer const& year) {
		year_t y = dt.year() + year.nYears_;
		month_t m = dt.month();
		day_t d = dt.day();

		if (m == February && d == 29 && !is_gregorian_leapyear(y))
			d = 28;

		return Gregorian(y, m, d);
	}


	/** Gregorian + (integer month) operator. */
	Gregorian operator + (Gregorian const& dt, detail::packaged_month_integer const& month) {
		year_t yearsToAdd = month.nMonths_ / 12;
		month_t monthsToAdd = month.nMonths_ % 12;
		year_t y = dt.year() + yearsToAdd;
		month_t m = dt.month() + monthsToAdd;

		int adjustment = (m - 1) / 12 + (m - 12) / 12;
		y += adjustment;
		m -= month_t(adjustment * 12);

		day_t d = std::min(dt.day(), gregorian_days_in_month(m, is_gregorian_leapyear(y)));

		return Gregorian(y, m, d);
	}




}