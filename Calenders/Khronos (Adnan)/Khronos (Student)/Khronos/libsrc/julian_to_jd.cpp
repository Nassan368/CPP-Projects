/**	@file Julian_to_jd.cpp
	@author Garth Santor
	@date 2012-09-14

	Date and time library Julian conversion implementations.
	*/

#include <khronos/julian_calendar.hpp>
#include <khronos/timeofday.hpp>
namespace khronos {

	//Julian to Jd passing year,month,day
	jd_t julian_to_jd(year_t year, month_t month, day_t day)
	{
		long long a = (14 - month) / 12;
		long long y = year + 4800 - a;
		long long m = month + 12 * a - 3;
		return (day + (153 * m + 2) / 5 + 365 * y + y / 4 - 32083.5);

	}

	//Julian to Jd passing year,month,day,hsm
	jd_t julian_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t  second)
	{
		//jdn_t jdn = julian_to_jd(year, month, day);
		jdn_t jdn = static_cast<jdn_t>(floor(julian_to_jd(year, month, day)));


		double td = tod(hour, minute, second);

		return jdn + td + 0.5; // Check this extra 0.5 might be wrong
	}

	//Jd_to_julian passing JD, year, month, day
	void jd_to_julian(jd_t jd, year_t& year, month_t& month, day_t& day) {

		jd_t a = floor(jd + 0.5);
		long b = static_cast<long> (a) + 1524;
		long c = static_cast<long>(floor((b - 122.1) / 365.25));
		long d = static_cast<long>(floor(365.25 * c));
		long e = static_cast<long>(floor((b - d) / 30.6001));

		month = static_cast<month_t>((e < 14) ? (e - 1) : (e - 13));
		year = static_cast<year_t>((month > 2) ? (c - 4716) : (c - 4715));
		day = static_cast<day_t>(b - d - floor(30.6001 * e));

	};

	//Jd_to_julian passing JD, year, month, day,hms
	void jd_to_julian(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second) {

		jd_to_julian(jd, year, month, day);
		hms_fromJD(jd, hour, minute, second);
	};

};//end namespace khronos