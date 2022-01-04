/* 
Module: CovidPatient
Filename: CovidPatient.h
Version 1.0
Author	Muhammad Ahmed
*/

#ifndef SDDS_COVIDPATIENT_H_
#define SDDS_COVIDPATIENT_H_

#include "Patient.h"

namespace sdds
{
	class CovidPatient : public Patient
	{
	public:
		CovidPatient();
		char type()const;
		std::istream& csvRead(std::istream&);
		std::ostream& write(std::ostream&)const;
		std::istream& read(std::istream&);
	};
}

#endif // !SDDS_COVIDPATIENT_H_



