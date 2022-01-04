/* 
Module: IOAble
Filename: IOAble.h
Version 1.0
Author:	Muhammad Ahmed
*/

#ifndef SDDS_IO_ABLE_H
#define SDDS_IO_ABLE_H

#include <iostream>

namespace sdds
{
	class IOAble
	{
	public:
		virtual std::ostream& csvWrite(std::ostream&)const = 0;
		virtual std::istream& csvRead(std::istream&) = 0;
		virtual std::ostream& write(std::ostream&)const = 0;
		virtual std::istream& read(std::istream&) = 0;
		virtual ~IOAble() {}
	};

	std::ostream& operator<<(std::ostream& out, const IOAble& s);
	std::istream& operator>>(std::istream& in, IOAble& s);
}

#endif // !SDDS_IO_ABLE_H
