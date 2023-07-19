/*
Final Project Milestone 56
Module: Item
Filename: Item.h
Version 1.0
Author	Chungon Tse, 154928188, Section NDD, cotse@myseneca.ca
Revision History
-----------------------------------------------------------
Date      Reason
2022/4/6  Preliminary release
2022/4/29 Completing my project after the semester ended
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H
#include <iostream>
#include "iProduct.h"
#include "Status.h"

#include <string.h>

namespace sdds
{
	class Item : public iProduct
	{
		double m_price;
		int m_qty;
		int m_qtyNeeded;
		char* m_description;
		bool m_linear;//to dictate to the display function if the next output is going to be linear to descriptive.
	protected:
		Status m_state;//state of the Item Object
		int m_sku;
		bool linear() const;
	public:
		Item();
		Item(int sku);
		Item(double price, int qty, int qtyNeeded, const char* desc, bool linear, int sku);
		Item(const Item&);
		Item& operator=(const Item&);
		//from iProduct
		int readSku(std::istream& istr);
		int operator-=(int qty) override;
		int operator+=(int qty) override;
		operator double()const override;
		operator bool()const override;
		int qtyNeeded()const override;
		int qty()const override;
		void linear(bool isLinear) override;
		std::ofstream& save(std::ofstream& ofstr)const;
		std::ifstream& load(std::ifstream& ifstr);
		std::ostream& display(std::ostream& ostr)const;
		std::istream& read(std::istream& istr);
		bool operator==(int sku)const override;
		bool operator==(const char* desc)const override;
		//Item
		void clear();
		bool descriptionMatch(const char* match);

		~Item();
		const char* desc() const;//added 56
	};
}
#endif // !SDDS_ITEM_H