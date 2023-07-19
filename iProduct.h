/*
Final Project Milestone 54
Module: iProduct
Filename: iProduct.h
Version 1.0
Author	Chungon Tse, 154928188, Section NDD, cotse@myseneca.ca
Revision History
-----------------------------------------------------------
Date      Reason
2022/3/23  Preliminary release
2022/4/29 Completing my project after the semester ended
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_IPRODUCT_H
#define SDDS_IPRODUCT_H
#include <iostream>
namespace sdds
{
	class iProduct
	{
	public:
		// to read the Stock-Keeping Unit from console before
		// main data entry
		virtual int readSku(std::istream& istr) = 0;
		// to reduce the quantity on hand
		virtual int operator-=(int qty) = 0;
		// to increase the quantity on hand
		virtual int operator+=(int qty) = 0;
		// returns the price of the produce
		virtual operator double()const = 0;
		// returns if the iProduct is in a good state
		virtual operator bool()const = 0;
		// returns the number of products needed
		virtual int qtyNeeded()const = 0;
		// retuns the quantity on hand
		virtual int qty()const = 0;
		// determines if the iProduct is displayed in a linear format or 
		// descriptive format
		virtual void linear(bool isLinear) = 0;
		// saves the iProduct into a file
		virtual std::ofstream& save(std::ofstream& ofstr)const = 0;
		// loads an iProduct from a file
		virtual std::ifstream& load(std::ifstream& ifstr) = 0;
		// displays the iProduct on the screen
		virtual std::ostream& display(std::ostream& ostr)const = 0;
		// reads the iProduct from the console
		virtual std::istream& read(std::istream& istr) = 0;
		// return true if the sku is a match to the iProduct's sku
		virtual bool operator==(int sku)const = 0;
		// retrns true if the description is found in the iProduct's description
		virtual bool operator==(const char* desc)const = 0;

		virtual ~iProduct() {};
		virtual const char* desc() const {//added 56
			return "";
		};
	};
	std::ostream& operator<<(std::ostream& ostr, const iProduct& iprod);
	std::istream& operator>>(std::istream& istr, iProduct& iprod);
}
#endif // !SDDS_IPRODUCT_H