/* 
Module: Patient
Filename: Patient.h
Version 1.0
Author:	Muhammad Ahmed
*/

#ifndef SDDS_PATIENT_H
#define SDDS_PATIENT_H

#include "IOAble.h"
#include "Ticket.h"

namespace sdds
{
	class Patient : public IOAble
	{
		char* m_name = nullptr;
		int m_ohip;
		bool m_fileIO;
		Ticket m_ticket;
	public:
		Patient(int ticketNum = 0, bool fileIO = false);
		~Patient();
		bool fileIO()const;
		void fileIO(bool fileIO);
		int number()const;
		void setArrivalTime();
		operator Time()const;
		bool operator==(char c)const;
		bool operator==(const Patient& p)const;
		std::ostream& csvWrite(std::ostream&)const;
		std::istream& csvRead(std::istream&);
		std::ostream& write(std::ostream&)const;
		std::istream& read(std::istream&);
		virtual char type()const = 0;
		Patient(Patient&) = delete;
		Patient& operator=(Patient&) = delete;
	};
}

#endif // !SDDS_PATIENT_H
