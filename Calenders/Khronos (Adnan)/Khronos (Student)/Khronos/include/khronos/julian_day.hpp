#pragma once
/*	julian_day.hpp

	Khronos library Julian Day class declaration.

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.09.25
	Repaced relational operators with <=>

Version 2016.09.30
	Added: Phase List

Version 2015.09.21
	Initial Release


=============================================================

Copyright Garth Santor/Trinh Han

The copyright to the computer program(s) herein
is the property of Garth Santor/Trinh Han, Canada.
The program(s) may be used and/or copied only with
the written permission of Garth Santor/Trinh Han
or in accordance with the terms and conditions
stipulated in the agreement/contract under which
the program(s) have been supplied.
=============================================================*/
#include <string>
#include <ostream>
#include<algorithm>
#include <khronos/def.hpp>
#include <khronos/timeofday.hpp>
#include <khronos/utility.hpp>
#include <khronos/calendar.hpp>


namespace khronos {


	//Functions
//Convert a Julian date to a Julian day number
	inline jdn_t jd_to_jdn(jd_t jd) {
		return static_cast<jdn_t>(floor(jd + 0.5));
	}
	// CLASSES
	// --------------------------------------------------------------------------------------

	/**	Julian Date (JN) class. */
	class Jd {
		jd_t	jd_;
	public:

		//default constructer
		Jd();
		//Constructor passing time
		Jd(now_t timet);
		/**	Constructor from real number. */
		constexpr Jd(jd_t jd) : jd_(jd) { }

		/**	Get the number of days. */
		constexpr jd_t jd() const { return jd_; }

		std::string to_string() const;

	};


	/** stream insertion operator. */
	inline std::ostream& operator << (std::ostream& os, Jd const& jd) {
		return os << jd.to_string();
	}


	// OPERATORS
	// --------------------------------------------------------------------------------------

	/** Jd relational operators. */
	constexpr auto operator <=> (Jd const& lhs, Jd const& rhs) { return lhs.jd() <=> rhs.jd(); }
	inline bool operator == (Jd const& lhs, Jd const& rhs) { return lhs.jd() == rhs.jd(); }
	inline bool operator != (Jd const& lhs, Jd const& rhs) { return lhs.jd() != rhs.jd(); }
	inline bool operator <= (Jd const& lhs, Jd const& rhs) { return lhs.jd() <= rhs.jd(); }
	inline bool operator >= (Jd const& lhs, Jd const& rhs) { return lhs.jd() >= rhs.jd(); }
	inline bool operator <  (Jd const& lhs, Jd const& rhs) { return lhs.jd() < rhs.jd(); }
	inline bool operator >  (Jd const& lhs, Jd const& rhs) { return lhs.jd() > rhs.jd(); }


	/**Jd difference operator. */
	constexpr jd_t operator - (Jd const& lhs, Jd const& rhs) { return lhs.jd() - rhs.jd(); }


	/**	Day of the week. */
	inline day_t day_of_week(Jd const& jd) { return civil::day_of_week(jd.jd()); }


	/** Day addition/subtraction. */
	namespace detail {
		struct packaged_day {
			day_t nDays_;
			constexpr packaged_day(day_t d) : nDays_(d) { };
		};
	};
	constexpr detail::packaged_day days(day_t d) { return detail::packaged_day(d); }
	constexpr Jd operator + (Jd const& jdn, detail::packaged_day days) { return Jd(jdn.jd() + days.nDays_); }
	constexpr Jd operator - (Jd const& jdn, detail::packaged_day days) { return jdn.jd() - days.nDays_; }


	/** Week addition/subtraction. */
	namespace detail {
		struct packaged_week {
			day_t nWeeks_;
			constexpr packaged_week(day_t w) : nWeeks_(w) { };
		};
	};
	constexpr detail::packaged_week weeks(day_t w) { return detail::packaged_week(w); }
	constexpr Jd operator + (Jd const& jdn, detail::packaged_week weeks) { return jdn.jd() + weeks.nWeeks_ * 7.0; }
	constexpr Jd operator - (Jd const& jdn, detail::packaged_week weeks) { return jdn.jd() - weeks.nWeeks_ * 7.0; }


	//** Month addition/subtraction. */
	namespace detail {
		struct packaged_month_integer {
			month_t nMonths_;
			constexpr packaged_month_integer(month_t m) : nMonths_(m) { }
		};
		struct packaged_month_real {
			double nMonths_;
			constexpr packaged_month_real(double m) : nMonths_(m) { }
		};
	};
	constexpr detail::packaged_month_real months(double m) { return detail::packaged_month_real(m); }
	constexpr detail::packaged_month_real months(float m) { return detail::packaged_month_real(m); }
	template <typename T> constexpr detail::packaged_month_integer months(T m) { return detail::packaged_month_integer(month_t(m)); }


	//** Year addition/subtraction. */
	namespace detail {
		/** Year as integer number wrapper. */
		struct packaged_year_integer {
			year_t nYears_;
			constexpr packaged_year_integer(year_t y) : nYears_(y) { }
		};
		/** Year as real number wrapper. */
		struct packaged_year_real {
			double nYears_;
			constexpr packaged_year_real(double y) : nYears_(y) { }
		};
	};
	/** Wrap a double literal into a real year package. */
	constexpr detail::packaged_year_real years(double y) { return detail::packaged_year_real(y); }

	/** Wrap a float literal into a real year package. */
	constexpr detail::packaged_year_real years(float y) { return detail::packaged_year_real(y); }

	/** Wrap all other literals into an integer year package (if possible). */
	template<typename T> constexpr detail::packaged_year_integer years(T y) { return detail::packaged_year_integer(static_cast<year_t>(y)); }

	/**	JD + (real years) */
	constexpr Jd operator + (Jd const& dt, detail::packaged_year_real const& year) {
		return Jd(dt.jd() + year.nYears_ * EARTH_ORBITAL_PERIOD_DAYS);
	}

	/**	JD - (real years) */
	constexpr Jd operator - (Jd const& dt, detail::packaged_year_real const& year) { return dt + detail::packaged_year_real(-year.nYears_); }

	/**	JD + (integer year) */
	constexpr Jd operator + (Jd const& dt, detail::packaged_year_integer const& year) { return dt + detail::packaged_year_real((double)year.nYears_); }

	/**	JD - (integer year) */
	constexpr Jd operator - (Jd const& dt, detail::packaged_year_integer const& year) { return dt + detail::packaged_year_integer(-year.nYears_); }


}; // end-of-namespace khronos