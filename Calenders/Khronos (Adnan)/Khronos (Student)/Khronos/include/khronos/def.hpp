#pragma once

/*
khronos\def.hpp
(c) Garth Santor
Created: 2015-09-22
Last Updated: 2015-09-22

Khronos library definitions.
*/
#include<cmath>


namespace khronos {
	// Note: fundamental data types are signed to simplifies subtractions. * /
	using second_t = double;
	using minute_t = int;
	using hour_t = int;
	using jd_t =    double;
	using tod_t =  double;
	using jdn_t = double  ;
	using day_t = int;
	using month_t = int;
	using year_t = long long;

	/** Indicates the 'now' type used by default constructors. */
	enum now_t { NOTIMEOFDAY = 0, WTIMEOFDAY };

	// VALUES
	constexpr double EARTH_ORBITAL_PERIOD_DAYS = 365.256'363'004;
	


	//FUNCTIONS Converts Time (Hours, Minutes, Seconds) to a Fraction of a Day
	inline double tod(hour_t  h, minute_t m, second_t s) {
		double tod;
		tod = (s + 60.0 * (m + 60.0 * h)) / (60 * 60 * 24.0);
		return tod;
	};

	inline double tod(jd_t jd) { return jd + 0.5 - floor(jd + 0.5); }; // Extracts the Fractional Part of a Julian Day Number (JDN)
	//MIN // Using ternary operation
	//this functionw would be used  where you need to ensure that a value representing a day is within valid limits
	// or when determining the earlier of two days.
	inline day_t min(day_t day1, day_t day2) { return (day1 < day2) ? day1 : day2; }

} // end-of-namespace khronos
