/**	@file Islamic_to_jd.cpp
	@author Garth Santor
	@date 2013-09-19

	Islamic calendar conversion implementations.
	*/

#include <khronos/islamic_calendar.hpp>

namespace khronos {

	//Islamic to jd passing year, month and day
	jd_t islamic_to_jd(year_t year, month_t month, day_t day) {
		return day + ceil(29.5 * (month - 1)) + (static_cast<jd_t>(year) - 1) * 354.0 + floor((3 + 11 * static_cast<jd_t>(year)) / 30.0) + ISLAMIC_EPOCH - 1;
	}

	//end islamit_to_jd(no_tod)


	 //Islamic to jd passing year, month and day
	jd_t islamic_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second) {
		jdn_t jdn = static_cast<long >(islamic_to_jd(year, month, day));
		// This already handles the year conversion

		double td = tod(hour, minute, second);

		if (td >= 0.5)
			td = td - 1;

		return jdn + td + 0.5;
	}




	//end islamic_to_jd(+tod)


	 //JD to Islamic
	void jd_to_islamic(jd_t jd, year_t& year, month_t& month, day_t& day)
	{

		jd_t j = floor(jd) + 0.5;
		year = static_cast<year_t>(floor((30.0 * (j - ISLAMIC_EPOCH) + 10646) / 10631.0));
		month = static_cast<month_t>(min(12, static_cast<month_t>(ceil((j - (29 + islamic_to_jd(year, 1, 1))) / 29.5) + 1)));
		day = static_cast<day_t>(j - islamic_to_jd(year, month, 1) + 1);

		


	};

	//JD to Islamic passing HSM
	void jd_to_islamic(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second)
	{
		hms_fromJD(jd, hour, minute, second);
		jd_to_islamic(jd, year, month, day);

	};



};//end namespace khronos