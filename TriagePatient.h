/* 
Module: TriagePatient
Filename: TriagePatient.h
Version 1.0
Author:	Muhammad Ahmed
*/

#ifndef SDDS_TRIAGEPATIENT_H
#define SDDS_TRIAGEPATIENT_H

#include "Patient.h"

namespace sdds
{
	class TriagePatient : public Patient
	{
		char* m_symptoms = nullptr;
	public:
		TriagePatient();
		~TriagePatient();
		char type()const;
		std::ostream& csvWrite(std::ostream&)const;
		std::istream& csvRead(std::istream&);
		std::ostream& write(std::ostream&)const;
		std::istream& read(std::istream&);
	};
}

#endif // !SDDS_TRIAGEPATIENT_H


