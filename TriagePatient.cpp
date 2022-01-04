/* 
Module: TriagePatient
Filename: TriagePatient.cpp
Version 1.0
Author:	Muhammad Ahmed
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <cstring>
#include "TriagePatient.h"
#include "utils.h"

using namespace std;
namespace sdds
{
	int nextTriageTicket = 1;

	TriagePatient::TriagePatient() : Patient(nextTriageTicket)
	{
		nextTriageTicket++;
		delete[] m_symptoms;
		m_symptoms = nullptr;
	}

	TriagePatient::~TriagePatient()
	{
		delete[] m_symptoms;
	}

	char TriagePatient::type()const
	{
		return 'T';
	}

	std::ostream& TriagePatient::csvWrite(std::ostream& out)const
	{
		Patient::csvWrite(out);
		out << ',' << m_symptoms;
		return out;
	}

	std::istream& TriagePatient::csvRead(std::istream& in)
	{
		Patient::csvRead(in);
		in.ignore();

		string symptoms;
		delete[] m_symptoms;
		getline(in, symptoms, '\n');
		m_symptoms = new char[symptoms.length() + 1];
		strcpy(m_symptoms, symptoms.c_str());
		/*
		delete[] m_symptoms;
		m_symptoms = getcstr("", in, '\n');
		*/

		nextTriageTicket = Patient::number() + 1;

		return in;
	}

	std::ostream& TriagePatient::write(std::ostream& out)const
	{
		if (Patient::fileIO())
		{
			csvWrite(out);
		}
		else
		{
			out << "TRIAGE" << endl;
			Patient::write(out);
			out << endl;
			out << "Symptoms: " << m_symptoms << endl;
		}

		return out;
	}

	std::istream& TriagePatient::read(std::istream& in)
	{
		if (Patient::fileIO())
		{
			csvRead(in);
		}
		else
		{
			Patient::read(in);
			delete[] m_symptoms;
			m_symptoms = getcstr("Symptoms: ", in, '\n');
		}

		return in;
	}
}


