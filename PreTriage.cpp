/* 
Module: PreTriage
Filename: PreTriage.h
Version 1.0
Author:	Muhammad Ahmed
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include "PreTriage.h"

using namespace std;
namespace sdds
{
	void PreTriage::reg()
	{
		int selection;
		bool flag = true;

		do
		{
			m_pMenu >> selection;
			switch (selection)
			{
			case 0:
				flag = false;
				break;
			case 1:
				delete m_lineup[m_lineupSize];
				m_lineup[m_lineupSize] = new CovidPatient();
				flag = false;
				break;
			case 2:
				delete m_lineup[m_lineupSize];
				m_lineup[m_lineupSize] = new TriagePatient();
				flag = false;
				break;
			}
		}
		while (flag);

		if (selection != 0)
		{
			m_lineup[m_lineupSize]->setArrivalTime();
			cout << "Please enter patient information:" << endl;
			m_lineup[m_lineupSize]->fileIO(false);
			m_lineup[m_lineupSize]->read(cin);

			cout << endl << "******************************************" << endl;
			//m_lineup[m_lineupSize]->write(cout);
			cout << *m_lineup[m_lineupSize];
			cout << "Estimated Wait Time: ";
			cout << getWaitTime(*m_lineup[m_lineupSize]);
			cout << endl;
			cout << "******************************************" << endl << endl;

			m_lineupSize++;
		}
	}

	void PreTriage::admit()
	{
		int i, selection;
		bool flag = true;
		char type;

		do
		{
			m_pMenu >> selection;
			switch (selection)
			{
			case 0:
				flag = false;
				break;
			case 1:
				type = 'C';
				flag = false;
				break;
			case 2:
				type = 'T';
				flag = false;
				break;
			}
		}
		while (flag);

		if (selection != 0)
		{
			for (i = 0; i < m_lineupSize && !flag; i++)
			{
				if (m_lineup[i]->type() == type)
				{
					flag = true;
					i--;
				}
			}

			if (flag)
			{
				cout << endl << "******************************************" << endl;
				m_lineup[i]->fileIO(false);
				cout << "Calling for ";
				cout << *m_lineup[i];
				cout << "******************************************" << endl << endl;

				setAverageWaitTime(*m_lineup[i]);
				removeDynamicElement(m_lineup, i, m_lineupSize);
			}
		}
	}

	const Time PreTriage::getWaitTime(const Patient& p)const
	{
		int i, waitLine = 0;

		for (i = 0; i < m_lineupSize; i++)
		{
			if (p.type() == m_lineup[i]->type()) waitLine++;
		}
		Time time(waitLine);
		time *= (p.type() == 'C' ? m_averCovidWait : m_averTriageWait);

		return time;
	}

	void PreTriage::setAverageWaitTime(const Patient& p)
	{
		/*
		CT: Current Time
		PTT: Patient's Ticket Time
		AWT: Average Wait Time (Covid or Triage)
		PTN: Patient's Ticket Number
		AWT = ((CT - PTT) + (AWT * (PTN - 1))) / PTN
		*/
		if (p.type() == 'C')
		{
			m_averCovidWait = ((getTime() - int(Time(p))) + (int(m_averCovidWait) * (p.number() - 1))) / p.number();
		}
		else if (p.type() == 'T')
		{
			m_averTriageWait = ((getTime() - int(Time(p))) + (int(m_averTriageWait) * (p.number() - 1))) / p.number();
		}
	}

	void PreTriage::removePatientFromLineup(int index)
	{
		removeDynamicElement(m_lineup, index, m_lineupSize);
	}

	int PreTriage::indexOfFirstInLine(char type) const
	{
		bool flag = false;
		int i;

		for (i = 0; !flag && i < m_lineupSize; i++)
		{
			if (m_lineup[i]->type() == type) flag = true;
		}

		return flag ? i - 1 : -1;
	}

	void PreTriage::load()
	{
		int i;
		char patientType;
		Patient* patient = nullptr;
		ifstream fin(m_dataFilename); // opening file for reading

		cout << "Loading data..." << endl;
		if (fin.is_open())
		{
			if (fin.peek() != -1)
			{
				fin >> m_averCovidWait;
				fin.ignore(1000, ',');
				fin >> m_averTriageWait;
				fin.ignore(1000, '\n');

				for (i = 0; i < maxNoOfPatients && fin.peek() != EOF; i++)
				{
					fin >> patientType;
					fin.ignore(1000, ',');

					if (patientType == 'C')
					{
						patient = new CovidPatient();
					}
					else if (patientType == 'T')
					{
						patient = new TriagePatient();
					}

					if (patient)
					{
						patient->fileIO(true);
						patient->read(fin);
						patient->fileIO(false);
						m_lineup[i] = patient;
						m_lineupSize++;
					}
				}

				if (fin.peek() != EOF) cout << "Warning: number of records exceeded " << maxNoOfPatients << endl;
				cout << i << " Records imported..." << endl << endl;
			}
			else
			{
				cout << "No data or bad data file!" << endl << endl;
			}
		}
		else
		{
			cout << "Unable to find file or open file!" << endl << endl;
		}
	}

	PreTriage::PreTriage(const char* dataFilename) : m_appMenu("General Hospital Pre-Triage Application\n1- Register\n2- Admit", 2), m_pMenu("Select Type of Admittance:\n1- Covid Test\n2- Triage", 2)
	{
		m_dataFilename = new char[strlen(dataFilename) + 1];
		strcpy(m_dataFilename, dataFilename);
		m_averCovidWait = 15;
		m_averTriageWait = 5;
		load();
	}

	PreTriage::~PreTriage()
	{
		int i;
		ofstream fout(m_dataFilename, ofstream::trunc);	// opening file to write to it
		/*
		To delete contents of file then write to it:
		std::ios::trunc or std::ofstream::trunc

		To open file and append what you write to it:
		std::ios::app or std::ofstream::app
		*/

		if (fout.is_open())
		{
			fout << m_averCovidWait << ',' << m_averTriageWait << endl;
			cout << "Saving Average Wait Times," << endl;
			cout << "   COVID Test: " << m_averCovidWait << endl;
			cout << "   Triage: " << m_averTriageWait << endl;
			cout << "Saving m_lineup..." << endl;

			for (i = 0; i < m_lineupSize; i++)
			{
				m_lineup[i]->csvWrite(fout);
				fout << endl;

				cout << i + 1 << "- ";
				m_lineup[i]->csvWrite(cout);
				cout << endl;
			}
		}
		else
		{
			cout << "ERROR: unable to open/find file." << endl;
		}

		for (i = 0; i < m_lineupSize; i++) delete m_lineup[i];
		delete[] m_dataFilename;
		cout << "done!" << endl;
	}

	void PreTriage::run(void)
	{
		int selection;
		bool flag = true;

		do
		{
			m_appMenu >> selection;
			switch (selection)
			{
			case 0:
				flag = false;
				break;
			case 1:
				if (m_lineupSize < 100 && m_lineupSize > -1)
				{
					reg();
				}
				else
				{
					cout << "Line up full!" << endl;
				}
				break;
			case 2:
				admit();
				break;
			}
		}
		while (flag);
	}
}

