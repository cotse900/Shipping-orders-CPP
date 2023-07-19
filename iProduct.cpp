/*
Final Project Milestone 54
Module: iProduct
Filename: iProduct.cpp
Version 1.0
Author	Chungon Tse, 154928188, Section NDD, cotse@myseneca.ca
Revision History
-----------------------------------------------------------
Date      Reason
2022/3/23  Preliminary release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#include "iProduct.h"
using namespace std;

namespace sdds
{
	std::ostream& operator<<(std::ostream& ostr, const iProduct& iprod) {
		return iprod.display(ostr);
	};
	std::istream& operator>>(std::istream& istr, iProduct& iprod) {
		return iprod.read(istr);
	};
}