/* 
Module: CovidPatient
Filename: CovidPatient.cpp
Version 1.0
Author	Muhammad Ahmed
*/

#include <iostream>
#include "CovidPatient.h"

using namespace std;
namespace sdds
{
	int nextCovidTicket = 1;

	CovidPatient::CovidPatient() : Patient(nextCovidTicket)
	{
		nextCovidTicket++;
	}

	char CovidPatient::type()const
	{
		return 'C';
	}

	std::istream& CovidPatient::csvRead(std::istream& in)
	{
		Patient::csvRead(in);
		nextCovidTicket = Patient::number() + 1;
		in.ignore();
		return in;
	}

	std::ostream& CovidPatient::write(std::ostream& out)const
	{
		if (Patient::fileIO())
		{
			Patient::csvWrite(out);
		}
		else
		{
			out << "COVID TEST" << endl;
			Patient::write(out);
			out << endl;
		}

		return out;
	}

	std::istream& CovidPatient::read(std::istream& in)
	{
		if (Patient::fileIO())
		{
			csvRead(in);
		}
		else
		{
			Patient::read(in);
		}

		return in;
	}
}


