/**	@file Jdn.cpp
	@author Garth Santor
	@date 2012-09-16

	Date and time library to_string method implementations.
	*/


#include <khronos/julian_day.hpp>
#include <khronos/def.hpp>
#include <sstream>
#include <ctime>
#include<khronos/gregorian_calendar.hpp>

using namespace std;

namespace khronos {



	//JD Default Constructor
	Jd::Jd() : jd_(0.0)
	{
		time_t nowTime = time(NULL);
		struct tm tmNow;
		localtime_s(&tmNow, &nowTime);
		jd_ = gregorian_to_jd(
			tmNow.tm_year + 1900,
			month_t(tmNow.tm_mon + 1),
			day_t(tmNow.tm_mday),
			hour_t(tmNow.tm_hour),
			minute_t(tmNow.tm_min),
			second_t(tmNow.tm_sec)
		);
	}


	//JD toString
	std::string Jd::to_string() const {
		std::ostringstream oss;
		oss << "JD " << jd_;
		return oss.str();
	}


	//JD Constructor passing time
	Jd::Jd(now_t timet) : jd_(0.0)
	{
		if (timet == NOTIMEOFDAY)
		{

			time_t nowTime = time(NULL);
			struct tm tmNow;
			localtime_s(&tmNow, &nowTime);
			jd_ = gregorian_to_jd(
				tmNow.tm_year + 1900,
				month_t(tmNow.tm_mon + 1),
				day_t(tmNow.tm_mday));
		}

		else if (timet == WTIMEOFDAY)
		{
			time_t nowTime = time(NULL);
			struct tm tmNow;
			localtime_s(&tmNow, &nowTime);
			jd_ = gregorian_to_jd(
				tmNow.tm_year + 1900,
				month_t(tmNow.tm_mon + 1),
				day_t(tmNow.tm_mday),
				hour_t(tmNow.tm_hour),
				minute_t(tmNow.tm_min),
				second_t(tmNow.tm_sec));
		}
	}//end JD










}