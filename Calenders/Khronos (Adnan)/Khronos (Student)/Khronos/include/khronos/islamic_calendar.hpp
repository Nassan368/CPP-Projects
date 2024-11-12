#pragma once

/**	@file khronos/Islamic_calendar.hpp
	@author Garth Santor
	@date 2013-09-19

	Islamic calendar class and functions.
	*/

#include<khronos\def.hpp>
#include<khronos\julian_day.hpp>
#include <khronos/gregorian_calendar.hpp>
#include<sstream>

namespace khronos {

	//VALUES
	//Islamic Epoch
	constexpr double ISLAMIC_EPOCH = 1'948'439.5;


	enum islamic_weekday_codes { al_ahad, al_ithnayn, ath_thalatha, al_arba, al_khamis, al_juma, as_sabt };
	static std::array<char const*, 7> const islamic_week_names = { "al-ithnayn", "ath-thalatha", "al-'arb`a'", "al-khamis","al-jum`a", "as-sabt", "al-ahad" };


	enum islamic_month_code { Muharram = 1, Safar, RabialAwwal, RabiathThani, Jumadaalula, JumadatTania, Rajab, Shaban, Ramadan, Shawwal, DhulQadah, DhulHijja };
	static std::array<char const*, 13> const islamic_month_names = { "", "Muharram", "Safar", "Rabi'al-Awwal",
		"Rabi'ath-Thani", "Jumada I-Ula", "Jumada t-Tania", "Rajab", "Sha'ban", "Ramadan", "Shawwal",
		"Dhu I-Qa'da", "Dhu I-Hijja" };


	//FUNCTIONS Islamic TO JD and Viseversa
	jd_t islamic_to_jd(year_t year, month_t month, day_t day);
	jd_t islamic_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second);
	void jd_to_islamic(jd_t jd, year_t& year, month_t& month, day_t& day);
	void jd_to_islamic(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second);


	/*Is Leap Year*/
	inline bool is_islamic_leapyear(year_t y);

	//Functions
	// return islamic name and short name
	inline char const* islamic_month_name(month_t m) { return islamic_month_names[m]; }

	//julian_days_in_month(JAN, false)
	day_t islamic_days_in_month(month_t m, bool bl);

	//Islamic class
	class Islamic
	{

		year_t year_ = 1;
		month_t month_ = 1;
		day_t day_ =1;
		hour_t hour_ = 0;
		minute_t minute_ = 0;
		second_t second_ = 0;
		jd_t jd_;

		//FUNCTION FROM_JD
		void from_jd(jd_t jd) { jd_to_islamic(jd, year_, month_, day_, hour_, minute_, second_); }
		//FUNCTION TO JD
		jd_t to_jd() const { return islamic_to_jd(year_, month_, day_); }

	public:
		//Default Constructor
		Islamic();
		//Constructor passing time_type
		Islamic(now_t m);
		//Constructor from  Julian Day Number
		Islamic(Jd const& jd) :jd_(jd.jd()) { from_jd(jd.jd()); }
		//Julian Constructor passing in year, monht, day
		Islamic(year_t y, month_t m, day_t d) :year_(y), month_(m), day_(d), hour_(0), minute_(0), second_(0) { jd_ = islamic_to_jd(year_, month_, day_); }
		//Julian Constructor passing in year, month, day, hour, minute, second
		Islamic(year_t y, month_t m, day_t d, hour_t h, minute_t min, second_t s) :year_(y), month_(m), day_(d), hour_(h), minute_(min), second_(s) { jd_ = islamic_to_jd(year_, month_, day_, hour_, minute_, second_); }


		//Getters
		constexpr year_t  year() const { return year_; }
		constexpr month_t month() const { return month_; }
		constexpr day_t   day() const { return day_; }
		constexpr hour_t   hour() const { return hour_; }
		constexpr minute_t   minute() const { return minute_; }
		constexpr second_t   second() const { return second_; }


		//To String
		std::string to_string() const {
			std::ostringstream oss;
			unsigned dow = day_of_week(islamic_to_jd(year_, month_, day_, hour_, minute_, second_));

			oss << islamic_week_names[dow]
				<< ", " << islamic_month_names[month_]
				<< " " << day_
				<< " " << year_ << ", " << ((hour_ % 12 == 0) ? (12) : ((hour_ - 1) % 12 + 1)) << ":"
				<< (minute_ < 10 ? "0" : "") << minute_ << ":" << (second_ < 10 ? "0" : "") << second_ << (hour_ >= 12 ? " pm" : " am");

			return oss.str();
		}



		//Implicit cast to Jd class
		operator Jd() const { return  jd_; }

		//Assign and convert from Jd type to Julian type.
		Islamic& operator = (Jd const& jd)
		{
			jd_ = jd.jd();
			from_jd(jd.jd());
			return *this;
		}


	};//end class

	

	//Functions
	void islamic_add_months(year_t& year, month_t& month, day_t& day, month_t n);
	void islamicAddYear(year_t& year, month_t& month, day_t& day, year_t n);
	jd_t islamicAddYear(Islamic const g, jd_t n);

	//Stream inserter operator
	inline std::ostream& operator << (std::ostream& os, Islamic const& is) { return os << is.to_string(); }

	// + - Operators for Months and Years
	Islamic operator + (Islamic const& g, detail::packaged_month_integer months);
	Islamic operator -(Islamic const& g, detail::packaged_month_integer months);
	inline Islamic operator + (Islamic const& g, detail::packaged_year_integer years) {
		return Islamic(islamicAddYear(g, static_cast<jd_t>(years.nYears_)));

	}

	inline Islamic operator - (Islamic const& g, detail::packaged_year_integer years) {
		return Islamic(islamicAddYear(g, static_cast<jd_t>(0 - static_cast<year_t>(years.nYears_))));

	}




};//end namespace