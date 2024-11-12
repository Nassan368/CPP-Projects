#include <khronos/vulcan_calendar.hpp>
#include <cmath>
#include <ctime>
#include<iomanip>
namespace khronos {

    Vulcan::Vulcan() {
        time_t now = time(nullptr);
        struct tm tmNow;
        localtime_s(&tmNow, &now);  // Converts to local time

        year_ = year_t(tmNow.tm_year + 1900);
        month_ = month_t(tmNow.tm_mon + 1);
        day_ = day_t(tmNow.tm_mday);
        hour_ = hour_t(tmNow.tm_hour);
        minute_ = minute_t(tmNow.tm_min);
        second_ = second_t(tmNow.tm_sec);

        // Set jd_ to the current Vulcan Julian Day using local time
        jd_ = vulcan_to_jd(year_, month_, day_, hour_, minute_, second_);
    }


    // Constructor from Julian Day
    Vulcan::Vulcan(Jd const& jd) {
        from_jd(jd.jd());
    }

    // Constructor with year, month, and day
    Vulcan::Vulcan(year_t y, month_t m, day_t d)
        : year_(y), month_(m), day_(d), hour_(0), minute_(0), second_(0) {
        jd_ = vulcan_to_jd(year_, month_, day_);
    }

    // Constructor with year, month, day, hour, minute, and second
    Vulcan::Vulcan(year_t y, month_t m, day_t d, hour_t h, minute_t min, second_t s)
        : year_(y), month_(m), day_(d), hour_(h), minute_(min), second_(s) {
        jd_ = vulcan_to_jd(year_, month_, day_, hour_, minute_, second_);
    }

    // Helper Method: Converts Julian Day to Vulcan date and updates the object
    void Vulcan::from_jd(jd_t jd) {
        jd_to_vulcan(jd, year_, month_, day_, hour_, minute_, second_);
        jd_ = jd;
    }

    // Helper Method: Converts the current Vulcan date to Julian Day
    jd_t Vulcan::to_jd() const {
        return vulcan_to_jd(year_, month_, day_, hour_, minute_, second_);
    }

    // Vulcan to JD conversion without time of day
    jd_t vulcan_to_jd(year_t year, month_t month, day_t day) {
        jd_t jd = VULCAN_EPOCH - 1;
        jd += (year - 1) * 252.0;  // Vulcan year has 252 days (12 months, 21 days each)
        jd += (month - 1) * vulcan_days_in_month();  // Each month has 21 days
        jd += day;
        return jd;
    }

    // Vulcan to JD conversion with time of day
    jd_t vulcan_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second) {
        jd_t jd = vulcan_to_jd(year, month, day);
        double timeFraction = tod(hour, minute, second); // Fraction of a day
        return jd + timeFraction;
    }

    // JD to Vulcan conversion without time of day
    void jd_to_vulcan(jd_t jd, year_t& year, month_t& month, day_t& day) {
        jd_t z = std::floor(jd - VULCAN_EPOCH + 1);  // Adjust JD to Vulcan Epoch
        year = static_cast<year_t>(std::floor((z / 252.0) + 1));  // Calculate the Vulcan year
        jd_t yearStart = vulcan_to_jd(year, 1, 1);  // Start of the year
        z = jd - yearStart;  // Remainder after calculating year
        month = static_cast<month_t>(std::floor(z / 21.0)) + 1;  // Each month has 21 days
        day = static_cast<day_t>(std::fmod(z, 21.0)) + 1;  // Days remaining within the month
    }

    void jd_to_vulcan(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second) {
        jd_to_vulcan(jd, year, month, day);

        // Extract the fractional part of the Julian Day (for time calculation)
        double time_fraction = jd - std::floor(jd);

        // If the time fraction is very close to zero, set the time to 0:00:00
        if (std::abs(time_fraction) < 1e-10) {
            hour = 0;
            minute = 0;
            second = 0;
        }
        else {
            // Convert the fractional day into hours, minutes, and seconds
            hour = static_cast<hour_t>(std::floor(time_fraction * 24.0));
            minute = static_cast<minute_t>(std::floor((time_fraction * 1440.0) - (hour * 60)));
            second = static_cast<second_t>((time_fraction * 86400.0) - (hour * 3600) - (minute * 60));

            // Round small fractional values of seconds to 0 if very close to 0
            if (std::abs(second) < 1e-5) {
                second = 0;
            }
        }
    }


    // Operators for adding/subtracting months
    Vulcan operator+(Vulcan const& vulcan, detail::packaged_month_integer months) {
        year_t y = vulcan.year();
        month_t m = vulcan.month() + months.nMonths_;
        day_t d = vulcan.day();
        while (m > 12) {
            m -= 12;
            ++y;
        }
        while (m < 1) {
            m += 12;
            --y;
        }
        return Vulcan(y, m, d, vulcan.hour(), vulcan.minute(), vulcan.second());
    }

    Vulcan operator-(Vulcan const& vulcan, detail::packaged_month_integer months) {
        return vulcan + detail::packaged_month_integer(-months.nMonths_);
    }

    std::string Vulcan::to_string() const {
        std::ostringstream oss;

        // Month name and day
        oss << vulcan_month_name(month_) << " " << day_ << ", " << year_ << " ";

        // Hour (without leading zero), Minute and Second (with leading zeros)
        oss << hour_ << ":"
            << std::setw(2) << std::setfill('0') << minute_ << ":"
            << std::setw(2) << std::setfill('0') << second_;

        return oss.str();
    }

}
