/**	@file Julian.cpp
	@author Garth Santor
	@date 2013-09-19

	Julian calendar class implementation.
	*/

#include <khronos/julian_calendar.hpp>
#include <khronos/def.hpp>
#include <khronos/julian_day.hpp>
#include <sstream>
#include <ctime>

namespace khronos {

	//Is Julian LeapYear
	bool is_julian_leapyear(year_t year) {
		return (year % 4 == 0);
	}

	//Julian Default Constructor
	Julian::Julian() : hour_(0), minute_(0), second_(0) {
		time_t nowTime = time(NULL);  // Get current time
		struct tm tmNow;
		localtime_s(&tmNow, &nowTime);  // Convert to local time

		// Initialize the Julian date based on the current Gregorian date and time
		jd_ = gregorian_to_jd(
			year_t(tmNow.tm_year + 1900),
			month_t(tmNow.tm_mon + 1),
			day_t(tmNow.tm_mday)
		);

		// Call jd_to_julian to set the year, month, day, etc.
		jd_to_julian(jd_, year_, month_, day_);
	}

	Julian::Julian(now_t t) {
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
		jd_to_julian(jd_, year_, month_, day_, hour_, minute_, second_);
	}

	//Julian Constructor passing year,month,day
	Julian::Julian(year_t y, month_t m, day_t d){

		year_ = y;
		month_ = m;
		day_ = d;
		hour_ = 0;
		minute_ = 0;
		second_ = 0;
		jd_ = julian_to_jd(year_, month_, day_);
	}
	// Constructor with year, month, day, hour, minute, second
	Julian::Julian(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second)
		: year_(year), month_(month), day_(day), hour_(hour), minute_(minute), second_(second) {
		jd_ = julian_to_jd(year, month, day, hour, minute, second);
	}



	//ToString()
	std::string Julian::to_string() const {

		unsigned dayOfWeek = day_of_week(julian_to_jd(year_, month_, day_, hour_, minute_, second_));
		hour_t hourP = hour_;
		std::ostringstream oss;

		// Day of the week
		oss << civil::day_name(day_of_week(to_jd())) << ", ";
		oss << julian_month_name(month_) << ' ' << (unsigned)day_ << ' ';

		if (year_ <= 0)
			oss << (-year_ + 1) << " BC";
		else
			oss << year_ << " AD";

		oss << ", " << (hourP = (hourP % 12 == 0) ? (12) : ((hourP - 1) % 12 + 1)) << ":"
			<< (minute_ < 10 ? "0" : "") << minute_ << ":"
			<< (second_ < 10 ? "0" : "") << second_
			<< (hour_ >= 12 ? " pm" : " am");

		return oss.str();

	}

	Julian Julian::operator+(detail::packaged_year_real const&)
	{
		return Julian();
	}

	Julian Julian::operator-(detail::packaged_year_real const&)
	{
		return Julian();
	}

	Julian Julian::operator+(detail::packaged_month_real const&)
	{
		return Julian();
	}

	Julian Julian::operator-(detail::packaged_month_real const&)
	{
		return Julian();
	}

	

	Julian operator + (Julian const& dt, detail::packaged_year_integer const& year) {
		year_t newYear = dt.year() + year.nYears_;
		month_t newMonth = dt.month();
		day_t newDay = dt.day();

		// If we're starting on February 29 and the new year is not a leap year, adjust to February 28
		if (newMonth == February && newDay == 29 && !is_julian_leapyear(newYear)) {
			newDay = 28;  // Adjust to February 28 if the new year is not a leap year
		}

		return Julian(newYear, newMonth, newDay, dt.hour(), dt.minute(), dt.second());
	}




	Julian operator+(Julian const& dt, detail::packaged_month_integer const& month) {
		year_t yearsToAdd = month.nMonths_ / 12; // Calculate how many years to add
		month_t monthsToAdd = month.nMonths_ % 12; // Calculate remaining months to add

		year_t newYear = dt.year() + yearsToAdd; // Update year with years to add
		month_t newMonth = dt.month() + monthsToAdd; // Update month

		// Handle overflow/underflow of months
		if (newMonth > 12) {
			newYear++;
			newMonth -= 12;
		}
		else if (newMonth < 1) {
			newYear--;
			newMonth += 12;
		}

		// Adjust day if it exceeds the number of days in the resulting month
		day_t newDay = std::min(dt.day(), julian_days_in_month(newMonth, is_julian_leapyear(newYear)));

		return Julian(newYear, newMonth, newDay, dt.hour(), dt.minute(), dt.second());
	}

};//end namesapce khronos