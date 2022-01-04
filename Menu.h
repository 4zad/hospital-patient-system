/* 
Module: Menu
Filename: Menu.h
Version 1.0
Author:	Muhammad Ahmed
*/

#ifndef SDDS_MENU_H
#define SDDS_MENU_H

#include <iostream>

namespace sdds
{
    class Menu
    {
        char* m_text; // holds the menu content dynamically
        int m_noOfSel;  // holds the number of options displayed in menu content
        void display()const;
    public:
        Menu(const char* MenuContent, int NoOfSelections);
        virtual ~Menu();
        int& operator>>(int& Selection);
        // add safe copying logic
        Menu(const Menu& source);
        Menu& operator=(const Menu& source) = delete;
    };
}

#endif // !SDDS_MENU_H


