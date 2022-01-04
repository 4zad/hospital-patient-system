/* 
Module: Patient
Filename: Patient.cpp
Version 1.0
Author:	Muhammad Ahmed
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <cstring>
#include "Patient.h"
#include "IOAble.h"
#include "utils.h"

using namespace std;
namespace sdds
{
	Patient::Patient(int ticketNum, bool fileIO) : m_fileIO(fileIO), m_ticket(ticketNum)
	{
		//NOTE: when initializing members as done above, order of initialization should match the order of in which they were declared in their class (in their header file)
		//Alternative below:
		//m_fileIO = fileIO;
		//m_ticket.m_number = number;   //This is not allowed though because m_number is private
	}

	Patient::~Patient()
	{
		delete[] m_name;
	}

	bool Patient::fileIO()const
	{
		return m_fileIO;
	}

	void Patient::fileIO(bool fileIO)
	{
		m_fileIO = fileIO;
	}

	int Patient::number()const
	{
		return m_ticket.number();
	}

	void Patient::setArrivalTime()
	{
		m_ticket.resetTime();
	}

	Patient::operator Time()const
	{
		return Time(m_ticket);
	}

	bool Patient::operator==(char c)const
	{
		return type() == c;
	}

	bool Patient::operator==(const Patient& p)const
	{
		return type() == p.type();
	}

	std::ostream& Patient::csvWrite(std::ostream& out)const
	{
		out << type() << ',' << m_name << ',' << m_ohip << ',';
		m_ticket.csvWrite(out);
		return out;
	}

	std::istream& Patient::csvRead(std::istream& in)
	{
		string tempName;
		getline(in, tempName, ',');
		delete[] m_name;
		m_name = new char[tempName.length() + 1];
		strcpy(m_name, tempName.c_str());
		in >> m_ohip;
		in.ignore(1000, ',');
		m_ticket.csvRead(in);
		return in;
	}

	std::ostream& Patient::write(std::ostream& out)const
	{
		out << m_ticket << endl;
		for (int i = 0; (i < 25) && (m_name[i] != '\0'); i++) out << m_name[i];
		out << ", OHIP: " << m_ohip;
		return out;
	}

	std::istream& Patient::read(std::istream& in)
	{
		/*
		string tempName;
		getline(in, tempName, '\n');
		delete[] m_name;
		m_name = new char[tempName.length() + 1];
		strcpy(m_name, tempName.c_str());
		*/
		delete[] m_name;
		m_name = getcstr("Name: ", in, '\n');
		m_ohip = getInt(100000000, 999999999, "OHIP: ", "Invalid OHIP Number, ", true);
		return in;
	}
}
