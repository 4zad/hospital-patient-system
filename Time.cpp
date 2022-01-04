/*
Module: Time
Filename: Time.cpp
Version 1.0
Author:	Muhammad Ahmed
*/

#include "Time.h"
#include "utils.h"

using namespace std;

namespace sdds
{
	Time& Time::setToNow()
	{
		m_min = getTime();
		return *this;
	}

	Time::Time(unsigned int min)
	{
		m_min = min;
	}

	std::ostream& Time::write(std::ostream& ostr) const
	{
		ostr.width(2);
		ostr.fill('0');
		ostr << m_min / 60;

		ostr << ":";

		ostr.width(2);
		ostr.fill('0');
		ostr << m_min % 60;

		return ostr;
	}

	std::istream& Time::read(std::istream& istr)
	{
		int hrs, mins;
		char delimiter;

		istr >> hrs >> delimiter >> mins;
		if (istr.fail() || delimiter != ':' || hrs < 0 || mins < 0)
		{
			istr.setstate(ios::failbit);
		}
		else
		{
			m_min = (hrs * 60) + mins;
		}

		return istr;
	}

	Time& Time::operator-=(const Time& D)
	{
		int hrs = m_min / 60, mins = m_min % 60, hrsD = D.m_min / 60, minsD = D.m_min % 60;

		hrs -= hrsD;
		while (hrs < 0)
		{
			hrs += 24;
		}	

		mins -= minsD;
		while (mins < 0)
		{
			mins += 60;
			hrs -= 1;
		}

		m_min = (hrs * 60) + mins;

		return *this;
	}

	Time Time::operator-(const Time& D)const
	{
		int hrs = m_min / 60, mins = m_min % 60, hrsD = D.m_min / 60, minsD = D.m_min % 60;
		Time temp;

		hrs -= hrsD;
		while (hrs < 0)
		{
			hrs += 24;
		}

		mins -= minsD;
		while (mins < 0)
		{
			mins += 60;
			hrs -= 1;
		}

		temp.m_min = (hrs * 60) + mins;

		return temp;
	}

	Time& Time::operator+=(const Time& D)
	{
		m_min += D.m_min;
		return *this;
	}

	Time Time::operator+(const Time& D)const
	{
		Time temp;
		temp.m_min = m_min + D.m_min;
		return temp;
	}

	Time& Time::operator=(unsigned int val)
	{
		m_min = val;
		return *this;
	}

	Time& Time::operator *= (unsigned int val)
	{
		m_min *= val;
		return *this;
	}

	Time& Time::operator /= (unsigned int val)
	{
		m_min /= val;
		return *this;
	}

	Time Time::operator *(unsigned int val)const
	{
		Time temp;
		temp.m_min = m_min * val;
		return temp;
	}

	Time Time::operator /(unsigned int val)const
	{
		Time temp;
		temp.m_min = m_min / val;
		return temp;
	}

	Time::operator unsigned int()const
	{
		return m_min;
	}

	Time::operator int()const
	{
		return (int)m_min;
	}

	std::ostream& operator<<(std::ostream& ostr, const Time& D)
	{
		D.write(ostr);
		return ostr;
	}

	std::istream& operator>>(std::istream& istr, Time& D)
	{
		D.read(istr);
		return istr;
	}
}

