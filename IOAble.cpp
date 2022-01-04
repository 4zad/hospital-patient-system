/* 
Module: IOAble
Filename: IOAble.h
Version 1.0
Author	Muhammad Ahmed
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "IOAble.h"

using namespace std;
namespace sdds
{
	std::ostream& operator<<(std::ostream& out, const IOAble& data)
	{
		return data.write(out);
	}

	std::istream& operator>>(std::istream& in, IOAble& data)
	{
		return data.read(in);
	}
}

