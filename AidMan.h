/*
Final Project Milestone 56
Module: AidMan
Filename: AidMan.h
Version 2.0
Author	Chungon Tse, 154928188, Section NDD, cotse@myseneca.ca
Revision History
-----------------------------------------------------------
Date      Reason
2022/4/6  Preliminary release
2022/4/28 Completing my project after the semester ended
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_AIDMAN_H
#define SDDS_AIDMAN_H

#include <fstream>
#include "Menu.h"
#include "iProduct.h"
#include "Item.h"
#include "Perishable.h"

const int sdds_max_num_items = 100;

namespace sdds
{
	class AidMan
	{
		char* filename{};
		Menu* m_menu;

		std::ofstream *fileStream;
		iProduct *iproducts[sdds_max_num_items];	//iproduct array
		int iproductsCount;		//an integer to keep track of the number of iProduct Items pointed by the iProduct pointers. Obviously this number can not grow more than 100.
		

	private:
		void save(); //a method for saving data records in file
		void deallocate(); //a method to dallocate all the memory allocated by the class
		bool load();	//a method to load all the records from the data file into the class.

		int list(const char* sub_desc = nullptr); //1- List Items

		int search(int sku) const;
		void remove(int index);
	public:
		AidMan();
		AidMan(const AidMan& am) = delete;
		AidMan& operator=(const AidMan& am) = delete;
		void setEmpty();
		void set(const char* fname);

		~AidMan();


		unsigned menu();
		void run();
	};
}
#endif // !SDDS_AIDMAN_H