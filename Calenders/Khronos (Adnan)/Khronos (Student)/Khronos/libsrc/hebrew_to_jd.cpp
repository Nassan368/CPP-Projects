/**	@file Hebrew_to_jd.cpp
	@author Garth Santor
	

	Hebrew calendar conversion implementations.
*/

#include <khronos/hebrew_calendar.hpp>
#include<khronos\timeofday.hpp>
#include<khronos\def.hpp>
#include <cassert>
#include<math.h>

namespace khronos {

	jdn_t hebrew_to_jd(year_t year, month_t month, day_t day)
	{
		jd_t jd = (HEBREW_EPOCH + delayOfWeek(year) + delayAdjacentYear(year) + day + 1);
		if (month < 7)
		{
			for (int i = 7; i <= hebrew_months_in_year(year); i++)
			{
				jd += hebrew_days_in_month(year, i);
			}

			for (int i = 1; i < month; i++)
			{
				jd += hebrew_days_in_month(year, i);
			}

		}
		else
		{
			for (int i = 7; i < month; i++)
			{
				jd += hebrew_days_in_month(year, i);
			}

		}
		return jd;
	}



	//hebrew_to_jd
	jd_t hebrew_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second)
	{
		jd_t jdn = hebrew_to_jd(year, month, day);
		double td = tod(hour, minute, second);
		if (td >= 0.5) td -= 1;
		return (jdn + td) ;
	}








	//jd_to_hebrew
	void jd_to_hebrew(jd_t jd, year_t& year, month_t& month, day_t& day)
	{
		jd_t j = (floor(jd) + 0.5);
		int count = static_cast<int>(floor((j - HEBREW_EPOCH * 98496) / 35975351));
		year = static_cast<year_t>(count) - 1;
		int i = count;

		while (j > hebrew_to_jd(i, 7, 1))
		{
			year = year + 1;
			i = i + 1;
		}

		int first = 1;

		if (j < hebrew_to_jd(year, 1, 1))
			first = 7;
		month = first;
		i = first;

		while (j > hebrew_to_jd(year, i, hebrew_days_in_month(year, i)))
		{
			month = month + 1;
			i = i + 1;
		}

		day = static_cast<day_t>(floor(j - hebrew_to_jd(year, month, 1) + 1));
	}

	//jd_to_hebrew
	void jd_to_hebrew(jd_t jd, year_t& y, month_t& m, day_t& d, hour_t& h, minute_t& mi, second_t& s)
	{
		hms_fromJD(jd, h, mi, s);
		jd_to_hebrew(jd, y, m, d);

	}



};//end namespace