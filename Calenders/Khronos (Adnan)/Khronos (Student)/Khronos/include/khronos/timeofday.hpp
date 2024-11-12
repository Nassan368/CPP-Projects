#pragma once

/*
khronos\timeofday.hpp
(c) Garth Santor
Created: 2015-09-22
Last Updated: 2015-09-22

Khronos library 'time-of-day' declarations.
*/


#include <khronos/def.hpp>
#include<algorithm>
#include<khronos/calendar.hpp>
namespace khronos {
	// LITERALS
	/* UDL - converts an 'AM' hour to 'military' hour. */

	constexpr hour_t operator ""_am(unsigned long long hourAM)
	{
		if (hourAM != 12)
			hourAM = hourAM;
		else
			hourAM = 0;

		return static_cast<hour_t>(hourAM);
	};


	/* UDL - converts an 'PM' hour to 'military' hour. */
	constexpr hour_t operator ""_pm(unsigned long long hourPM)
	{

		if (hourPM == 12)
			hourPM = hourPM;
		else if (hourPM == 1)
			hourPM = 13;
		else if (hourPM == 2)
			hourPM = 14;
		else if (hourPM == 3)
			hourPM = 15;
		else if (hourPM == 4)
			hourPM = 16;
		else if (hourPM == 5)
			hourPM = 17;
		else if (hourPM == 6)
			hourPM = 18;
		else if (hourPM == 7)
			hourPM = 19;
		else if (hourPM == 8)
			hourPM = 20;
		else if (hourPM == 9)
			hourPM = 21;
		else if (hourPM == 10)
			hourPM = 22;
		else if (hourPM == 11)
			hourPM = 23;

		return static_cast<hour_t>(hourPM);
	};

	/* Seconds per day. */
	
	const double SECONDS_PER_DAY = 60 * 60 * 24.0;


	/* H:M:S.S to time-of-day [0.0..1.0) */

	inline void hms_from_tod(double tod, hour_t& h, minute_t& m, second_t& s)
	{
		double secondInDay = tod * 24 * 60 * 60 + 0.5;
		h = static_cast<hour_t>(secondInDay / (60 * 60));
		m = static_cast<minute_t>(secondInDay / 60) % 60;
		s = static_cast<long>(secondInDay - 60 * floor(secondInDay / 60));
	};
	/**	Convert Time-of-day (TOD) to hours, minutes, seconds.  Civil days run from midnight to midnight.
		@param tod [in] a time-of-day [0..1)
		@param hours [out] 0-23
		@param minutes [out] 0-59
		@param seconds [out] [0.0..60.0)
		*/
	inline void hms(double tod, hour_t& h, minute_t& m, second_t& s)
	{
		double secondsInDay = floor(tod * 24 * 60 * 60 + 0.5);
		h = static_cast<short> (secondsInDay / (60 * 60));
		m = static_cast<short>(secondsInDay / 60) % 60;
		s = static_cast<short>(secondsInDay) % 60;
	};

	inline void hms_fromJD(jd_t jd, hour_t& h, minute_t& m, second_t& s)
	{
		hms_from_tod(tod(jd), h, m, s);
	};
} // end-of-namespace khronos
