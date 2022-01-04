/* 
Module: utils
Filename: utils.cpp
Version 1.0
Author:	Muhammad Ahmed
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include "utils.h"
#include "Time.h"

using namespace std;
namespace sdds
{
	bool debug = false;  // made global in utils.h

	int getTime()
	{
		int mins = -1;
		if (debug)
		{
			Time t(0);
			cout << "Enter current time: ";
			do
			{
				cin.clear();
				cin >> t;   // needs extraction operator overloaded for Time
				if (!cin)
				{
					cout << "Invlid time, try agian (HH:MM): ";
					cin.clear();
				}
				else
				{
					mins = int(t);
				}
				cin.ignore(1000, '\n');
			}
			while (mins < 0);
		}
		else
		{
			time_t t = time(NULL);
			tm lt = *localtime(&t);
			mins = lt.tm_hour * 60 + lt.tm_min;
		}
		return mins;
	}

	int getInt(const char* prompt)
	{
		int intValue, flag;

		if (prompt != nullptr)
		{
			cout << prompt;
		}

		do
		{
			flag = 0;

			cin >> intValue;

			if (cin.fail())
			{
				flag = 1;
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Bad integer value, try again: ";
			}
			else if (cin.peek() != '\n')
			{
				flag = 1;
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Enter only an integer, try again: ";
			}
		}
		while (flag);

		return intValue;
	}

	int getInt(int min, int max, const char* prompt, const char* errorMessage, bool showRangeAtError)
	{
		int intValue, flag;

		if (prompt != nullptr)
		{
			cout << prompt;
		}

		do
		{
			flag = 0;

			cin >> intValue;

			if (cin.fail())
			{
				flag = 1;
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Bad integer value, try again: ";
			}
			else if (cin.peek() != '\n')
			{
				flag = 1;
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Enter only an integer, try again: ";
			}
			else if (intValue < min || intValue > max)
			{
				flag = 1;
				cin.clear();
				cin.ignore(1000, '\n');
				if (errorMessage != nullptr)
				{
					cout << errorMessage;
				}
				if (showRangeAtError)
				{
					cout << "[";

					//cout.width(2);
					//cout.fill('0');
					//cout.setf(ios::fixed);
					cout << min;
					//cout.unsetf(ios::fixed);

					cout << " <= value <= ";

					//cout.width(2);
					//cout.fill('0');
					//cout.setf(ios::fixed);
					cout << max;
					//cout.unsetf(ios::fixed);

					cout << "]: ";
				}
				
			}
		}
		while (flag);

		return intValue;
	}

	char* getcstr(const char* prompt, std::istream& istr, char delimiter)
	{
		char* strPointer;
		string strValue;

		if (prompt != nullptr)
		{
			cout << prompt;
		}

		cin.clear();
		getline(cin, strValue, delimiter);

		strPointer = new char[strValue.length() + 1];
		strcpy(strPointer, strValue.c_str());
		strPointer[strValue.length()] = '\0';

		return strPointer;
	}
}


