#pragma once

/**	@file khronos/julian_calendar.hpp
	@author Garth Santor
	@date 2013-09-19

	Julian calendar functions and class declaration.
	*/

#include <khronos/julian_day.hpp>
#include <khronos/gregorian_calendar.hpp>

namespace khronos {



	//VALUES
		//Julian Epoch
	jd_t constexpr JULIAN_EPOCH = 1'721'423.5;

	//FUNCTIONS JULIAN TO JD and Viseversa
	jd_t julian_to_jd(year_t year, month_t month, day_t day);
	jd_t julian_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t  second);
	void jd_to_julian(jd_t jd, year_t& year, month_t& month, day_t& day);
	void jd_to_julian(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second);

	/*Is Leap Year*/
	bool	is_julian_leapyear(year_t year);

	//Functions
	/** Provide the number of days in the month of the Julian Calendar. */
	constexpr day_t julian_days_in_month(month_t month, bool is_julian_leapyear) { return civil::days_in_month(month, is_julian_leapyear); }

	/** Provide the name of the given month in the Julian calendar. */
	constexpr char const* julian_month_name(month_t month) { return civil::month_name_long(month); }

	/** Provide the short name of the given month in the Julian calendar. */
	constexpr char const* julian_short_month_name(month_t month) { return civil::month_name_short(month); }

	/* UDL - _BC*/
	constexpr year_t operator ""_BC(unsigned long long JulianYearBC) { return static_cast<long long>(JulianYearBC - 1) * -1; }
	constexpr year_t operator ""_bc(unsigned long long JulianYearBC) { return static_cast<long long>(JulianYearBC - 1) * -1; }
	

	class Julian {

		year_t		year_ = 1;
		month_t		month_ = 1;
		day_t		day_ = 1;
		hour_t		hour_ = 0;
		minute_t	minute_ = 0;
		second_t	second_ = 0;
		jd_t jd_;

		//FUNCTION FROM_JD
		void from_jd(jd_t jd) { jd_to_julian(jd, year_, month_, day_, hour_, minute_, second_); }
		//FUNCTION TO JD
		//jd_t to_jd() const { return julian_to_jd(year_, month_, day_); }
		jd_t to_jd() const { return julian_to_jd(year_, month_, day_, hour_, minute_, second_); }

	public:

		//Default Constructor
		Julian();

		Julian(now_t t);
		//Constructor from  Julian Day Number
		Julian(Jd const& jd) { from_jd(jd.jd()); }
		//Julian Constructor passing in year, monht, day
		Julian(year_t y, month_t m, day_t d);
		//Julian Constructor passing in year, month, day, hour, minute, second
		/*Julian(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second, jd_t jd_) : year_(year), month_(month), day_(day), hour_(hour), minute_(minute), second_(second), jd_(julian_to_jd(year, month, day, hour, minute, second)) {};*/
		// Constructor: year, month, day, hour, minute, second
		Julian(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second);

		//Getters
		constexpr year_t  year() const { return year_; }
		constexpr month_t month() const { return month_; }
		constexpr day_t   day() const { return day_; }
		constexpr hour_t   hour() const { return hour_; }
		constexpr minute_t   minute() const { return minute_; }
		constexpr second_t   second() const { return second_; }

		//To String
		std::string to_string() const;

		//Implicit cast to Jd class
		operator Jd () const { return Jd(to_jd()); }

		//Assign and convert from Jd type to Julian type.
		Julian& operator = (Jd const& jd) {
			from_jd(jd.jd());
			return *this;
		}

	private:
		Julian operator + (detail::packaged_year_real const&);
		Julian operator - (detail::packaged_year_real const&);
		Julian operator + (detail::packaged_month_real const&);
		Julian operator - (detail::packaged_month_real const&);

	};//end class


	//OPERATORS
		/** Julian + (integer month) */
	Julian operator + (Julian const& dt, detail::packaged_month_integer const& month);

	/** Julian - (integer month) */
	inline Julian operator - (Julian const& dt, detail::packaged_month_integer const& month) { return dt + detail::packaged_month_integer(-month.nMonths_); }

	/**	Julian + (integer year) */
	Julian operator + (Julian const& dt, detail::packaged_year_integer const& year);

	/**	Julian - (integer year) */
	inline Julian operator - (Julian const& dt, detail::packaged_year_integer const& year) { return dt + detail::packaged_year_integer(-year.nYears_); }

	/** Stream insertion operator. */
	inline std::ostream& operator << (std::ostream& os, Julian const& g) { return os << g.to_string(); }






};
