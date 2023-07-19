/*
Final Project Milestone 56
Module: Item
Filename: Item.cpp
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
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "Item.h"
#include "Utils.h"
using namespace std;

namespace sdds
{
	bool Item::linear() const{
		return m_linear;
	};
	Item::Item() {
		m_state = "Input file stream read failed!"; 
		m_price = 0;
		m_qty = 0;
		m_qtyNeeded = 0;
		m_description = nullptr;
		m_linear = false;
		m_sku = 0;
	};
	Item::Item(int sku) {
		m_state = "Input file stream read failed!";
		m_price = 0;
		m_qty = 0;
		m_qtyNeeded = 0;
		m_description = nullptr;
		m_linear = false;
		m_sku = sku;
	};
	Item::Item(double price, int qty, int qtyNeeded, const char* desc, bool iflinear, int sku) {
		m_price = price;
		m_qty = qty;
		m_qtyNeeded = qtyNeeded;
		ut.alocpy(m_description, desc);
		m_linear = iflinear;
		m_sku = sku;
		clear();
	};
	Item::Item(const Item& rhs) {
		m_price = rhs.m_price;
		m_qty = rhs.m_qty;
		m_qtyNeeded = rhs.m_qtyNeeded;
		ut.alocpy(m_description, rhs.m_description);
		m_linear = rhs.m_linear;
		m_sku = rhs.m_sku;
		clear();
	};
	Item& Item::operator=(const Item& rhs) {
		if (this != &rhs) {
			m_price = rhs.m_price;
			m_qty = rhs.m_qty;
			m_qtyNeeded = rhs.m_qtyNeeded;
			ut.alocpy(m_description, rhs.m_description);
			m_linear = rhs.m_linear;
			m_sku = rhs.m_sku;
			m_state = rhs.m_state;
		}
		return *this;
	};
	Item::~Item() {
		if (m_description) {
			delete[] m_description;
			m_description = nullptr;
		}
	}
	//public query overrides
	int Item::qtyNeeded()const {
		return m_qtyNeeded;
	};
	int Item::qty()const {
		return m_qty;
	};
	Item::operator double()const {
		return m_price;
	};
	Item::operator bool()const {
		return m_state; //state of the object being good
	};
	//public modifier overrides
	int Item::operator-=(int qty) {
		if (qty > 0) {
			m_qty -= qty;
		}
		return m_qty;
	};
	int Item::operator+=(int qty) {
		if (qty > 0) {
			m_qty += qty;
		}
		return m_qty;
	};
	void Item::linear(bool isLinear) {
		m_linear = isLinear;
	};
	//public mod
	void Item::clear() {//sets the state of the Item object back to good, by resetting the state attribute.
		m_state.clear();
	}
	bool Item::descriptionMatch(const char* match)
	{
		if (strstr(m_description, match)) {
			return true;
		}
		return false;
	};

	//== overrides
	bool Item::operator==(int sku)const {
		return (m_sku == sku);//SKU attribute matches the received value
	};
	bool Item::operator==(const char* desc)const {
		if (strstr(m_description, desc)) {
			return true;
		}
		return false;
	};
	std::ofstream& Item::save(std::ofstream& ofstr)const {//rework in Aug 2022: simplified this func
		//if (m_state) {//If the state of the Item is good <--?
		//	ofstr << m_sku << '\t' << m_description << '\t' << m_qty << '\t' << m_qtyNeeded << '\t' << m_price;
		//}
		//else {//added for 56
		//	ofstr.width(5);
		//	ofstr << m_sku << " | ";
		//	int i = 0;
		//	if (m_description != nullptr) {
		//		for (i = 0; i < 35; i++) {

		//			if (m_description[i] == '\0') {
		//				break;
		//			}
		//			else {
		//				ofstr << m_description[i];
		//			}
		//		}
		//	}
		//	while (i < 35) {
		//		ofstr << " ";
		//		i++;
		//	}

		//	ofstr << " | ";
		//	ofstr.fill(' ');
		//	ofstr.setf(ios::right);
		//	ofstr.width(4);
		//	ofstr << m_qty << " | ";
		//	ofstr.unsetf(ios::right);
		//	ofstr.setf(ios::right);
		//	ofstr.width(4);
		//	ofstr << m_qtyNeeded << " | ";
		//	ofstr.unsetf(ios::right);
		//	ofstr.setf(ios::right);
		//	ofstr.width(7);
		//	ofstr << fixed << setprecision(2) << m_price << " |";
		//}
		//return ofstr;
		if (m_state)
		{
			ofstr << m_sku << "\t";
			ofstr << m_description << "\t";
			ofstr << m_qty << "\t";
			ofstr << m_qtyNeeded << "\t";
			ofstr.setf(ios::fixed);
			ofstr.precision(2);
			ofstr << m_price;
			ofstr.unsetf(ios::fixed);
		}
		return ofstr;
	};

	std::ifstream& Item::load(std::ifstream& ifstr) {
		int local_sku;
		int local_qty;
		int local_qtyNeeded;
		double local_price;

		if (m_description) {
			delete[] m_description;
			m_description = nullptr;
		}

		if (ifstr.is_open()) {
			ifstr >> local_sku;

			ut.extractChar(ifstr, '\t');
			ut.getDescription(m_description, ifstr);

			ifstr >> local_qty;
			
			ut.extractChar(ifstr, '\t');
			ifstr >> local_qtyNeeded;

			ut.extractChar(ifstr, '\t');
			ifstr >> local_price;

			clear();
			m_sku = local_sku;
			m_qty = local_qty;
			m_qtyNeeded = local_qtyNeeded;
			m_price = local_price;
		}
		if (ifstr.fail()) {
			m_state = "Input file stream read failed!";
		}
		else {
			clear();
		}
		//The tab-separated SKU, description, on-hand quantity, needed quantity and price are read into their corresponding attributes and then a single character is discarded from the file.
		//If ifstream is in a bad state after the read the state of the item will be set to "Input file stream read failed!"
			//Note that the description is dynamically allocated
		return ifstr;
	};
	std::ostream& Item::display(std::ostream& ostr)const {
		ios init(NULL);
		init.copyfmt(ostr); //save default settings

		if (!m_state) // If the state is bad, the state is printed instead.
		{
			ostr << m_state;
		}
		else if (m_linear) {//rework in Aug 2022
			//ostr << m_sku << " | ";

			////limit to 35 chars
			//if (strlen(m_description) <= 35) {
			//	ostr.fill(' ');
			//	ostr.width(35);
			//	ostr << std::left << m_description << " | ";
			//}
			//else {
			//	char tempDisplay[36];
			//	strncpy(tempDisplay, m_description, 35);
			//	tempDisplay[35] = '\0';
			//	ostr.fill(' ');
			//	ostr.width(35);
			//	ostr << std::left << tempDisplay << " | ";
			//}

			////width 4 fields, right-align
			//ostr.setf(ios::fixed);
			//ostr.width(4);
			//ostr << std::right << m_qty << " | ";
			//ostr.width(4);
			//ostr << m_qtyNeeded << " | ";

			//ostr.setf(ios::fixed);
			//ostr.precision(2);
			//ostr.width(7); //from example
			//ostr << m_price;//todo: cout.width and right-leaning and so on

			ostr.setf(ios::fixed);
			ostr.width(5);
			ostr << m_sku;
			ostr.unsetf(ios::fixed);
			ostr << " | ";
			ostr.setf(ios::fixed);
			bool done = false;
			int i = 0;
			for (i = 0; i < 35 && done != true; i++)
			{
				if (m_description[i] != '\0')
				{
					ostr << m_description[i];
				}
				else
				{
					done = true;
				}
			}
			if (i < 35)
			{
				int tempLength = 35 - strlen(m_description);
				for (int j = 0; j < tempLength; j++)
				{
					ostr << " ";
				}
			}
			ostr.unsetf(ios::fixed);
			ostr << " | ";
			ostr.setf(ios::fixed);
			ostr.width(4);
			ostr.fill(' ');
			ostr << right << m_qty;
			ostr.unsetf(ios::fixed);
			ostr << " | ";
			ostr.setf(ios::fixed);
			ostr.width(4);
			ostr.fill(' ');
			ostr << right << m_qtyNeeded;
			ostr.unsetf(ios::fixed);
			ostr << " | ";
			ostr.setf(ios::fixed);
			ostr.width(7);
			ostr.fill(' ');
			ostr.precision(2);
			ostr << right << m_price;
			ostr.unsetf(ios::fixed);
			ostr << " |";
		}
		else if (m_description) {//if in descriptive format
			ostr << "AMA Item:" << endl;
			ostr << m_sku << ": " << m_description << endl;
			ostr << "Quantity Needed: " << m_qtyNeeded << endl;
			ostr << "Quantity Available: " << m_qty << endl;

			//print double properly, set precision
			ostr.setf(ios::fixed);
			ostr.precision(2);
			ostr << "Unit Price: $" << m_price << endl;
			ostr << "Needed Purchase Fund: $" << m_price * (m_qtyNeeded - m_qty);
		}
		return ostr;
	};

	int Item::readSku(std::istream& istr) {
		m_sku = ut.getint(40000, 99999, "SKU: ", "Invalid Integer");
		return *this;
	};
	std::istream& Item::read(std::istream& istr) {
		delete[] m_description;
		m_description = nullptr;

		cout << "AMA Item:" << endl;
		cout << "SKU: " << m_sku << endl;
		if (m_sku) {
			cout << "Description: ";
			m_description = new char[35];
			fgets(m_description, 35, stdin);
			m_description[strcspn(m_description, "\n")] = 0; //remove trailing newline char

			m_qtyNeeded = ut.getint(1, 9999, "Quantity Needed: ", "Invalid Integer");
			if (m_qtyNeeded) {
				m_qty = ut.getint(0, m_qtyNeeded, "Quantity On Hand: ", "Invalid Integer");
				if (m_qty) {
					m_price = ut.getdouble(0.0, 9999.0, "Unit Price: $", "Invalid Number");
					if (m_price) {
						clear();
					}
					else {
						m_state = "Console entry failed!";
					}
				}
				else {
					m_state = "Console entry failed!";
				}
			}
			else {
				m_state = "Console entry failed!";
			}
		}
		else {
			m_state = "Console entry failed!";
		}
		return istr;
	};
	const char* Item::desc() const {
		return m_description;
	};
}