﻿// -------------------------------------------------------------------------
//    @FileName         :    NFDateTime.hpp
//    @Author           :    LvSheng.Huang
//    @Date             :    2016-12-22
//    @Module           :    NFDateTime
//
// -------------------------------------------------------------------------

#pragma once
#ifndef NF_DATETIME_HPP
#define NF_DATETIME_HPP

#include <sstream>
#include <iomanip>
#include <string>
#include <chrono>
#include "NFException.hpp"

#define STR_CASE(_Enum, _Str) case _Enum::_Str : return # _Str
#define MONTH_CASE(_Month) STR_CASE(::Month, _Month)
#define DAY_CASE(_Day) STR_CASE(::DayOfWeek, _Day)

using std::chrono::nanoseconds;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::minutes;
using std::chrono::hours;
using days = std::chrono::duration<long long, std::ratio<3600 * 24>>;

using namespace std;
using namespace std::chrono;

enum class DayOfWeek
{
	Sunday = 0,
	Monday = 1,
	Thuesday = 2,
	Wednesday = 3,
	Thursday = 4,
	Friday = 5,
	Saturday = 6,
};

enum Month
{
	January = 1,
	February = 2,
	March = 3,
	April = 4,
	May = 5,
	June = 6,
	July = 7,
	August = 8,
	September = 9,
	October = 10,
	November = 11,
	December = 12,
};

class NFDateTime;

class NFTimeSpan
{
public:
	static constexpr long long TicksPerSecond = std::chrono::system_clock::duration::period::den;
	static constexpr long long TicksPerMillisecond = TicksPerSecond / 1000;
	static constexpr long long TicksPerMinute = TicksPerSecond * 60;
	static constexpr long long TicksPerHour = TicksPerMinute * 60;
	static constexpr long long TicksPerDay = TicksPerHour * 24;

	static NFTimeSpan Zero()
	{
		static NFTimeSpan _value = 0;
		return _value;
	}

	/*
	static NFTimeSpan MaxValue()
	{
		static NFTimeSpan _value = std::chrono::system_clock::duration::max();
		return _value;
	}

	static NFTimeSpan MinValue()
	{
		static NFTimeSpan _value = std::chrono::system_clock::duration::min();
		return _value;
	}
	*/

	NFTimeSpan(long long ticks) :
		NFTimeSpan(std::chrono::system_clock::duration(ticks))
	{}

	NFTimeSpan(int hours, int minutes, int seconds) :
		NFTimeSpan(0, hours, minutes, seconds, 0)
	{}

	NFTimeSpan(int days, int hours, int minutes, int seconds) :
		NFTimeSpan(days, hours, minutes, seconds, 0)
	{}

	NFTimeSpan(int days, int hours, int minutes, int seconds, int milliseconds) :
		NFTimeSpan(days * TicksPerDay + hours * TicksPerHour + minutes * TicksPerMinute + seconds * TicksPerSecond + milliseconds * TicksPerMillisecond)
	{}

	inline long long TotalMilliseconds() const
	{
		return TickCount<milliseconds>();
	}

	inline int TotalHours() const
	{
		return TickCount<hours>();
	}

	inline int TotalDays()  const
	{
		return TickCount<days>();
	}

	inline int Seconds() const
	{
		return TickCount<seconds>() % 60;
	}

	inline int Minutes() const
	{
		return TickCount<minutes>() % 60;
	}

	inline int Milliseconds() const
	{
		return TickCount<milliseconds>() % 1000;
	}

	inline int Hours() const
	{
		return TickCount<hours>() % 24;
	}

	inline int Days() const
	{
		return TickCount<days>();
	}

	inline long long Ticks() const
	{
		return _ticks.count();
	}

	inline long long TotalMinutes() const
	{
		return TickCount<minutes>();
	}

	inline long long TotalSeconds() const
	{
		return TickCount<seconds>();
	}

	static bool Equals(const NFTimeSpan& t1, const NFTimeSpan& t2)
	{
		return t1._ticks == t2._ticks;
	}

	static NFTimeSpan FromDays(long long value)
	{
		return NFTimeSpan(value, 0, 0, 0, 0);
	}

	static NFTimeSpan FromHours(long long value)
	{
		return NFTimeSpan(0, value, 0, 0, 0);
	}

	static NFTimeSpan FromMilliseconds(long long value)
	{
		return NFTimeSpan(0, 0, 0, 0, value);
	}

	static NFTimeSpan FromMinutes(long long value)
	{
		return NFTimeSpan(0, 0, value, 0, 0);
	}

	static NFTimeSpan FromSeconds(long long value)
	{
		return NFTimeSpan(0, 0, 0, value, 0);
	}

	static NFTimeSpan FromTicks(long long value)
	{
		return value;
	}

	inline NFTimeSpan Add(const NFTimeSpan& ts) const
	{
		return _ticks + ts._ticks;
	}

	inline NFTimeSpan Duration() const
	{
		return std::abs(_ticks.count());
	}

	inline bool Equals(const NFTimeSpan& value) const
	{
		return _ticks == value._ticks;
	}

	inline NFTimeSpan Negate() const
	{
		return -_ticks.count();
	}

	inline NFTimeSpan Subtract(const NFTimeSpan& ts) const
	{
		return _ticks - ts._ticks;
	}

	inline std::string ToString() const
	{
		std::stringstream ss(std::stringstream::in | std::stringstream::out);
		ss << std::setfill('0') << Days() << "." << std::setw(2) << Hours() << ":" << std::setw(2) << Minutes() << ":" << std::setw(2) << Seconds() << "." << std::setw(3) << Milliseconds();
		return ss.str();
	}

	inline NFTimeSpan operator +()
	{
		return *this;
	}

	inline NFTimeSpan operator +(const NFTimeSpan& t)
	{
		return _ticks + t._ticks;
	}

	inline NFTimeSpan operator  -()
	{
		return -_ticks;
	}

	inline NFTimeSpan operator -(const NFTimeSpan& t)
	{
		return _ticks - t._ticks;
	}

	inline bool operator ==(const NFTimeSpan& t)
	{
		return _ticks == t._ticks;
	}

	inline bool operator !=(const NFTimeSpan& t)
	{
		return _ticks != t._ticks;
	}

	inline bool operator <(const NFTimeSpan& t)
	{
		return _ticks < t._ticks;
	}

	inline bool operator >(const NFTimeSpan& t)
	{
		return _ticks > t._ticks;
	}

	inline bool operator <=(const NFTimeSpan& t)
	{
		return _ticks <= t._ticks;
	}

	inline bool operator >=(const NFTimeSpan& t)
	{
		return _ticks >= t._ticks;
	}

protected:
	NFTimeSpan(const std::chrono::system_clock::duration& ticks) :
		_ticks(ticks)
	{}

	template<typename T>
	inline long long TickCount() const
	{
		return std::chrono::duration_cast<T>(_ticks).count();
	}

	std::chrono::system_clock::duration _ticks;

	friend class NFDateTime;
};


class NFDateTime
{
public:
	/*
	static NFDateTime MinValue()
	{
		static NFDateTime _value = std::chrono::system_clock::time_point::min();
		return _value;
	}

	static NFDateTime MaxValue()
	{
		static NFDateTime _value = std::chrono::system_clock::time_point::max();
		return _value;
	}
	*/
	NFDateTime(int year, int month, int day) :
		NFDateTime(year, month, day, 0, 0, 0, 0)
	{}

	NFDateTime(int year, int month, int day, int hour, int minute, int second) :
		NFDateTime(year, month, day, hour, minute, second, 0)
	{}

	NFDateTime(int year, int month, int day, int hour, int minute, int second, int millisecond) :
		_millisecond(millisecond),
		_tm{ second, minute, hour, day, month - 1, year - 1900 }
	{
		_time = mktime(&_tm);
		_time_point = std::chrono::system_clock::from_time_t(_time) + milliseconds(millisecond);
	}

	static NFDateTime Now()
	{
		return std::chrono::system_clock::now();
	}

	static NFDateTime Today()
	{
		NFDateTime dt = std::chrono::system_clock::now();
		dt._tm.tm_hour = dt._tm.tm_min = dt._tm.tm_sec = 0;
		return std::move(dt);
	}

	inline long long Ticks()
	{
		return _time_point.time_since_epoch().count();
	}

	inline NFDateTime Date() const
	{
		return NFDateTime(_tm.tm_year + 1900, _tm.tm_mon + 1, _tm.tm_mday);
	}

	inline int Month() const
	{
		return _tm.tm_mon + 1;
	}

	inline int Minute() const
	{
		return _tm.tm_min;
	}

	inline int Millisecond() const
	{
		return _millisecond;
	}

	inline int Hour() const
	{
		return _tm.tm_hour;
	}

	inline int DayOfYear() const
	{
		return _tm.tm_yday;
	}

	inline ::DayOfWeek DayOfWeek() const
	{
		return static_cast<::DayOfWeek>(_tm.tm_wday);
	}

	inline int Day() const
	{
		return _tm.tm_mday;
	}

	inline int Second() const
	{
		return _tm.tm_sec;
	}

	inline NFTimeSpan TimeOfDay() const
	{
		return NFTimeSpan(0, _tm.tm_hour, _tm.tm_min, _tm.tm_sec, _millisecond);
	}

	inline int Year() const
	{
		return _tm.tm_year + 1900;
	}

	static int DaysInMonth(int year, int month)
	{
		switch (month)
		{
		case Month::January:
		case Month::March:
		case Month::May:
		case Month::July:
		case Month::August:
		case Month::October:
		case Month::December:
			return 31;

		case Month::April:
		case Month::June:
		case Month::September:
		case Month::November:
			return 30;

		case Month::February:
			return IsLeapYear(year) ? 29 : 28;

		default:
			break;
		}

		return -1;
	}

	static bool IsLeapYear(int year)
	{
		return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
	}

	inline NFDateTime Add(const NFTimeSpan& value) const
	{
		return _time_point + value._ticks;
	}

	inline NFDateTime AddDays(const double value) const
	{
		return _time_point + std::chrono::system_clock::duration(static_cast<long long>(value * NFTimeSpan::TicksPerDay));
	}

	inline NFDateTime AddHours(const double value) const
	{
		return _time_point + std::chrono::system_clock::duration(static_cast<long long>(value * NFTimeSpan::TicksPerHour));
	}

	inline NFDateTime AddMilliseconds(const double value) const
	{
		return _time_point + std::chrono::system_clock::duration(static_cast<long long>(value * NFTimeSpan::TicksPerMillisecond));
	}

	inline NFDateTime AddMinutes(const double value) const
	{
		return _time_point + std::chrono::system_clock::duration(static_cast<long long>(value * NFTimeSpan::TicksPerMinute));
	}

	inline NFDateTime AddMonths(const int value) const
	{
		auto new_month = _tm.tm_mon + value;
		auto new_year = _tm.tm_year + new_month / 12 + 1900;
		new_month = new_month % 12 + 1;
		auto daysInMonth = DaysInMonth(new_year, new_month);
		auto new_day = _tm.tm_mday < daysInMonth ? _tm.tm_mday : daysInMonth;
		return NFDateTime(_tm.tm_year, new_month, new_day, _tm.tm_hour, _tm.tm_min, _tm.tm_sec);
	}

	inline NFDateTime AddSeconds(const double value) const
	{
		return _time_point + std::chrono::system_clock::duration(static_cast<long long>(value * NFTimeSpan::TicksPerSecond));
	}

	inline NFDateTime AddTicks(const long long value) const
	{
		return _time_point + std::chrono::system_clock::duration(value);
	}

	inline NFDateTime AddYears(const int value) const
	{
		auto new_year = _tm.tm_year + value + 1900;
		auto daysInMonth = DaysInMonth(new_year, _tm.tm_mon);
		auto new_day = _tm.tm_mday < daysInMonth ? _tm.tm_mday : daysInMonth;
		return NFDateTime(_tm.tm_year, _tm.tm_mon, new_day, _tm.tm_hour, _tm.tm_min, _tm.tm_sec);
	}

	inline bool Equals(const NFDateTime& value)
	{
		return *this == value;
	}

	inline bool IsDaylightSavingTime() const
	{
		return _tm.tm_isdst;
	}

	inline NFTimeSpan Subtract(const NFDateTime& value) const
	{
		return _time_point - value._time_point;
	}

	inline NFDateTime Subtract(const NFTimeSpan& value) const
	{
		return _time_point - value._ticks;
	}

	std::string ToLongDateString() const
	{
        //yyyy-MM-dd hh:mm:ss
		std::stringstream ss(std::stringstream::in | std::stringstream::out);
        //ss << NameOfDay(DayOfWeek()) << ", " << Day() << DaySuffix(Day()) << " " << NameOfMonth(Month()) << ", " << Year();
        ss << Year() << "-" << Month() << "-" << Day();
		return ss.str();
	}

	std::string ToLongTimeString() const
	{
		std::stringstream ss(std::stringstream::in | std::stringstream::out);
		ss << std::setfill('0') << std::setw(2) << Hour() << ":" << std::setw(2) << Minute() << ":" << std::setw(2) << Second() << "." << std::setw(3) << Millisecond();
		return ss.str();
	}

	std::string ToShortDateString() const
	{
		std::stringstream ss(std::stringstream::in | std::stringstream::out);
		ss << std::setfill('0') << std::setw(2) << Day() << "." << std::setw(2) << Month() << "." << Year();
		return ss.str();
	}

	std::string GetLongTimeString()
	{
		std::stringstream ss(std::stringstream::in | std::stringstream::out);
		ss << std::setfill('0') << std::setw(2) << Hour() << ":" << std::setw(2) << Minute() << ":" << std::setw(2) << Second() << "." << std::setw(3) << Millisecond();
		return ss.str();
	}

	//yyyy-MM-dd hh:mm:ss
	inline std::string ToString()
	{
		return ToLongDateString() + " - " + ToLongTimeString();
	}

	inline NFDateTime operator +(const NFTimeSpan &t) const
	{
		return Add(t);
	}

	inline NFTimeSpan operator -(const NFDateTime& d) const
	{
		return Subtract(d);
	}

	inline NFDateTime operator -(const NFTimeSpan& t) const
	{
		return Subtract(t);
	}

	inline bool operator ==(const NFDateTime &dt) const
	{
		return _time_point == dt._time_point;
	}

	inline bool operator !=(const NFDateTime &dt) const
	{
		return _time_point != dt._time_point;
	}

	inline bool operator <(const NFDateTime &dt) const
	{
		return _time_point < dt._time_point;
	}

	inline bool operator >(const NFDateTime &dt) const
	{
		return _time_point > dt._time_point;
	}

	inline bool operator <=(const NFDateTime &dt) const
	{
		return _time_point <= dt._time_point;
	}

	inline bool operator >=(const NFDateTime &dt) const
	{
		return _time_point >= dt._time_point;
	}

protected:
	NFDateTime(const std::chrono::system_clock::time_point& tp) :
		_time_point(tp),
		_time(std::chrono::system_clock::to_time_t(tp))
	{
		_tm = *localtime(&_time);
		_millisecond = std::chrono::time_point_cast<milliseconds>(tp).time_since_epoch().count() % 1000;
	}

	int _millisecond;
	time_t _time;
	tm _tm;
	std::chrono::system_clock::time_point _time_point;

	static std::string NameOfDay(::DayOfWeek day)
	{
		switch (day)
		{
			DAY_CASE(Monday);
			DAY_CASE(Thuesday);
			DAY_CASE(Wednesday);
			DAY_CASE(Thursday);
			DAY_CASE(Friday);
			DAY_CASE(Saturday);
			DAY_CASE(Sunday);

		default:
			throw NFException("Day %d is not in valid weekday range ( %d - %d )", day, ::DayOfWeek::Sunday, ::DayOfWeek::Saturday);
			break;
		}
	}

	static std::string NameOfMonth(int month)
	{
		switch (month)
		{
			MONTH_CASE(January);
			MONTH_CASE(February);
			MONTH_CASE(March);
			MONTH_CASE(April);
			MONTH_CASE(May);
			MONTH_CASE(June);
			MONTH_CASE(July);
			MONTH_CASE(August);
			MONTH_CASE(September);
			MONTH_CASE(October);
			MONTH_CASE(November);
			MONTH_CASE(December);

		default:
			throw NFException("Month %d is not in valid range ( %d - %d )", month, ::Month::January, ::Month::December);
			break;
		}
	}
	static std::string DaySuffix(int day)
	{
		switch (day)
		{
		case 1:
		case 21:
		case 31:
			return "st";

		case 2:
		case 22:
			return "nd";

		case 3:
		case 23:
			return "rd";

		default:
			return "th";
		}
	}
};

#endif