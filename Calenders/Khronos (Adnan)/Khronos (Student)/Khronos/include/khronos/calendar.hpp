#pragma once

/*
khronos\calendar.hpp
(c) Garth Santor
Created: 2015-09-22
Last Updated: 2015-09-22

Khronos library 'civil' declarations.
*/


#include <khronos/def.hpp>
#include <array>
#include <cassert>
#include<string>
#include"utility.hpp"

namespace khronos {

	namespace civil {

		namespace detail {
			constexpr std::array<std::array<day_t, 13>, 2> daysInMonth = {
				0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
				0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
			};
		}


		/** Get the full name of the civil day of week.
			@return pointer to the day name as a c-string.
			@param day [in] day number [0..6], where 0 = Monday
		*/
		constexpr char const* day_name(day_t day) {
			constexpr char const* names[7] = {
				"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
			};
			assert(day >= 0);
			assert(day < 7);
			return names[day];
		}

		/**	Returns the number of days in the given month of the civil calendar.
			@return The number of days in the given month.
			@param month [in] month number [1..12]
			@param isLeapYear [in] 'true' for leap year, 'false' otherwise.
			*/
		constexpr day_t days_in_month(month_t month, bool isLeapYear) {
			return detail::daysInMonth[isLeapYear][month];
		}
		inline day_t day_of_week(jd_t jd) { return static_cast<day_t>(utility::mod(jd + 0.5, 7)); }
		// month functions

		/** Get the full name of the civil month.
			@return pointer to the month name as a c-string.
			@param month [in] month number [1..12]
		*/
		constexpr char const* month_name_long(month_t month) {
			constexpr char const* const names[13] = {
				"",
				"January", "February", "March", "April", "May", "June",
				"July", "August", "September", "October", "November", "December"
			};

			assert(month > 0);
			assert(month < 13);
			return names[month];
		}



		/** Get the short name of the civil month.
			@return pointer to the 3-letter month name as a c-string.
			@param month [in] month number [1..12]
		*/
		constexpr char const* month_name_short(month_t month) {
			constexpr char const* const names[13] = {
				"",
				"JAN", "FEB", "MAR", "APR", "MAY", "JUN",
				"JUL", "AUG", "SEP", "OCT", "NOV", "DEC"
			};

			assert(month > 0);
			assert(month < 13);
			return names[month];
		}
	}



	// VALUES
	enum civil_month_codes_long { January = 1, February, March, April, May, June, July, August, September, October, November, December };
	enum civil_month_codes_short { JAN = January, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };
	enum civil_weekday_codes_long { Monday = 0, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };
	enum civil_weekday_codes_short { MON = Monday, TUE, WED, THU, FRI, SAT, SUN };




	// ALTERNATE QUERY
	// ===============
	template <class Calendar> inline year_t year(Calendar const& date) { return date.year(); }
	template <class Calendar> inline month_t month(Calendar const& date) { return date.month(); }
	template <class Calendar> inline day_t day(Calendar const& date) { return date.day(); }

	template <class Calendar> inline hour_t hour(Calendar const& date) { return date.hour(); }
	template <class Calendar> inline minute_t minute(Calendar const& date) { return date.minute(); }
	template <class Calendar> inline second_t second(Calendar const& date) { return date.second(); }

} // end-of-namespace khronos
