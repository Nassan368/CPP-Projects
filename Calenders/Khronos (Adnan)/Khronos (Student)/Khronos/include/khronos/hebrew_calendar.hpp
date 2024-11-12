#pragma once

/**	@file khronos/hebrew_calendar.hpp
	@author Garth Santor
	

	Hebrew calendar class.
	*/

#include<khronos\def.hpp>
#include<khronos\julian_day.hpp>
#include<type_traits>
#include<assert.h>
#include<array>
#include<string>
#include<sstream> // Removes Error from OSS


namespace khronos {


	//VALUES
	//HEBREW EPOCH
	constexpr double HEBREW_EPOCH = 347'995.5;

	enum hebrew_weekday_codes { yom_rishon, yom_sheni, yom_shlishi, yom_revii, yom_chamishi, yom_shishi, yom_shabbat };

	static std::array<char const* const, 7> const hebrew_week_names = { "Yom-Rishon","Yom-Sheni","Yom-Shlishi","Yom-Revi'i", "Yom-Chamishi","Yom-Shishi","Yom-Shabbat" };

	enum hebrew_month_code { Nisan = 1, Iyyar, Sivan, Tammuz, Av, Elul, Tishri, Heshvan, Kislev, Teveth, Shevat, Adar, Veadar };

	static std::array<char const*, 14> const hebrew_month_names = { "",	"Nisan", "Iyyar", "Sivan", "Tammuz", "Av", "Elul", "Tishri", "Heshvan",
		"Kislev", "Teveth", "Shevat", "Adar", "Veadar" };

	//FUNCTIONS Islamic TO JD and Viseversa
	jdn_t hebrew_to_jd(year_t year, month_t month, day_t day);
	jd_t hebrew_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second);
	void jd_to_hebrew(jd_t jd, year_t& year, month_t& month, day_t& day);
	void jd_to_hebrew(jd_t jd, year_t& y, month_t& m, day_t& d, hour_t& h, minute_t& mi, second_t& s);


	/*Is Leap Year*/
	inline bool is_hebrew_leapyear(year_t y);

	//Functions
	inline char const* hebrew_month_name(month_t m) { return hebrew_month_names[m]; }
	day_t delayOfWeek(year_t year);
	day_t delayAdjacentYear(year_t year);
	day_t daysInYear(year_t year);
	day_t hebrew_days_in_month(year_t year, month_t m);
	inline month_t hebrew_months_in_year(year_t y) { return is_hebrew_leapyear(y) ? 13 : 12; };


	/**************************************************************************
	H E B R E W    -   C L A S S
	**************************************************************************/

	class Hebrew
	{
		year_t year_ = 1;
		month_t month_ = 1;
		day_t day_ = 1;
		hour_t hour_ = 0; 
		minute_t minute_ = 0;
		second_t second_ = 0;
		jd_t jd_;

		//FUNCTION FROM_JD
		void from_jd(jd_t jd) { jd_to_hebrew(jd, year_, month_, day_, hour_, minute_, second_); }
		//FUNCTION TO JD
		jd_t to_jd() const { return static_cast<jd_t>(hebrew_to_jd(year_, month_, day_, hour_, minute_, second_)); }

	public:
		//Default Constructor
		Hebrew();
		//Constructor passing time_type
		Hebrew(now_t m);
		//Constructor from  Julian Day Number
		Hebrew(Jd const& jd) :jd_(jd.jd()) { from_jd(jd.jd()); }
		//Julian Constructor passing in year, monht, day
		Hebrew(year_t y, month_t m, day_t d) :year_(y), month_(m), day_(d), hour_(0), minute_(0), second_(0) { jd_ = static_cast<jd_t>(hebrew_to_jd(year_, month_, day_)); }
		//Julian Constructor passing in year, month, day, hour, minute, second
		Hebrew(year_t y, month_t m, day_t d, hour_t h, minute_t min, second_t s) :year_(y), month_(m), day_(d), hour_(h), minute_(min), second_(s) { jd_ = hebrew_to_jd(year_, month_, day_, hour_, minute_, second_); }


		//Getters
		year_t  year() const { return year_; }
		month_t month() const { return month_; }
		day_t   day() const { return day_; }
		hour_t   hour() const { return hour_; }
		minute_t   minute() const { return minute_; }
		second_t   second() const { return second_; }


		//To String
		std::string to_string() const {
			std::ostringstream oss;

			//"Nisan 1 1000, 12:00:00 am"
			oss << hebrew_month_names[month_]
				<< " " << day_
				<< " " << year_ << ", " << ((hour_ % 12 == 0) ? (12) : ((hour_ - 1) % 12 + 1)) << ":"
				<< (minute_ < 10 ? "0" : "") << minute_ << ":" << (second_ < 10 ? "0" : "") << second_ << (hour_ >= 12 ? " pm" : " am");

			return oss.str();
		}

		//Implicit cast to Jd class
		operator Jd() const { return  jd_; }

		//Assign and convert from Jd type to Julian type.
		Hebrew& operator = (Jd const& jd)
		{
			jd_ = jd.jd();
			from_jd(jd.jd());
			return *this;
		}

	};//end class

	/**************************************************************************
	E N D  -  H E B R E W    -   C L A S S
	**************************************************************************/

	//Functions
	void hebrewAddYear(year_t& year, month_t& month, day_t& day, year_t n);
	jd_t hebrewAddYear(Hebrew const g, jd_t n);
	void hebrew_add_months(year_t& year, month_t& month, day_t& day, month_t n);

	//Stream inserter operator
	inline std::ostream& operator << (std::ostream& os, Hebrew const& heb) { return os << heb.to_string(); }

	// + - Operators for Months and Years
	Hebrew operator + (Hebrew const& g, detail::packaged_month_integer months);
	Hebrew operator -(Hebrew const& g, detail::packaged_month_integer months);
	inline Hebrew operator + (Hebrew const& g, detail::packaged_year_integer years) { return Hebrew(hebrewAddYear(g, static_cast<jd_t>(years.nYears_))); }
	inline Hebrew operator - (Hebrew const& g, detail::packaged_year_integer years) { return Hebrew(hebrewAddYear(g, static_cast < jd_t>( 0 - static_cast<year_t>(years.nYears_)))); }

};//END 