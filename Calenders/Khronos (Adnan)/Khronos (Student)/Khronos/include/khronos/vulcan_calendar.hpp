#pragma once

/** @file vulcan_calendar.hpp
    Vulcan calendar class and functions.
*/

#include <khronos/def.hpp>
#include <khronos/julian_day.hpp>
#include <sstream>
#include <array>

namespace khronos {

    // Vulcan Epoch
    constexpr double VULCAN_EPOCH = 173'651.6;

    enum vulcan_month_code {
        Zat = 1,
        Druh,
        KriBrax,
        reTKhutai,
        TkeKhuti,
        Khuti,
        TaKrat,
        Krilior,
        Etkhior,
        Tlakht,
        TkeTas,
        Tasmeen
    };

    static std::array<char const*, 13> const vulcan_month_names = {
        "",
        "Z'at",
        "D'ruh",
        "K'riBrax",
        "re'T'Khutai",
        "T'keKhuti",
        "Khuti",
        "Ta'Krat",
        "K'ri'lior",
        "et'khior",
        "T'lakht",
        "T'ke'Tas",
        "Tasmeen"
    };

    // Get the Vulcan month name
    inline char const* vulcan_month_name(month_t m) {
        return vulcan_month_names[m];
    }

    // Helper function to get the number of days in a Vulcan month
    inline day_t vulcan_days_in_month() {
        return 21;  // All Vulcan months have 21 days
    }

    // Vulcan class representing the Vulcan calendar
    class Vulcan {
        year_t year_;
        month_t month_;
        day_t day_;
        hour_t hour_;
        minute_t minute_;
        second_t second_;
        jd_t jd_;

        // Helper method: JD to Vulcan conversion
        void from_jd(jd_t jd);
        // Helper method: Vulcan to JD conversion
        jd_t to_jd() const;

    public:
        // Constructors
        Vulcan();
        Vulcan(Jd const& jd);
        Vulcan(year_t year, month_t month, day_t day);
        Vulcan(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second);

        // Getters
        year_t year() const { return year_; }
        month_t month() const { return month_; }
        day_t day() const { return day_; }
        hour_t hour() const { return hour_; }
        minute_t minute() const { return minute_; }
        second_t second() const { return second_; }

        // Conversion operator to Julian Day
        operator Jd() const { return Jd(jd_); }

        // Assignment operator from Julian Day
        Vulcan& operator=(Jd const& jd) {
            jd_ = jd.jd();
            from_jd(jd_);
            return *this;
        }

        // String conversion
        std::string to_string() const;
    };

    // Julian Day conversion functions for the Vulcan calendar
    jd_t vulcan_to_jd(year_t year, month_t month, day_t day);
    jd_t vulcan_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second);
    void jd_to_vulcan(jd_t jd, year_t& year, month_t& month, day_t& day);
    void jd_to_vulcan(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second);

    // Operators for adding/subtracting months
    Vulcan operator+(Vulcan const& vulcan, detail::packaged_month_integer months);
    Vulcan operator-(Vulcan const& vulcan, detail::packaged_month_integer months);
}
