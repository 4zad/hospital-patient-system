/* 
Module: Menu
Filename: Menu.cpp
Version 1.0
Author:	Muhammad Ahmed
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include "Menu.h"
#include "utils.h"

using namespace std;
namespace sdds
{
	Menu::Menu(const char* MenuContent, int NoOfSelections)
	{
		m_noOfSel = NoOfSelections;
		m_text = new char[strlen(MenuContent) + 1];
		strcpy(m_text, MenuContent);
	}

	Menu::Menu(const Menu& source)
	{
		m_noOfSel = source.m_noOfSel;
		m_text = new char[strlen(source.m_text) + 1];
		strcpy(m_text, source.m_text);
	}

	Menu::~Menu()
	{
		delete[] m_text;
	}

	void Menu::display()const
	{
		cout << m_text;
		cout << "\n0- Exit" << endl;
	}

	int& Menu::operator>>(int& Selection)
	{
		display();
		Selection = getInt(0, m_noOfSel, "> ", "Invalid option ", true);
		return Selection;
	}
}

