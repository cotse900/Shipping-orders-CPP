/*
Final Project Milestone 54
Module: Menu
Filename: Menu.h
Version 1.0
Author	Chungon Tse, 154928188, Section NDD, cotse@myseneca.ca
Revision History
-----------------------------------------------------------
Date      Reason
2022/3/24  Preliminary release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_MENU_H
#define SDDS_MENU_H

namespace sdds
{
#define maxoptions 15
	class Menu
	{
		char* text{};
		unsigned options;
		void setEmpty();
	public:
		Menu(const char* optiontext, unsigned numoptions);
		Menu(const Menu& src);
		virtual ~Menu();
		Menu& operator=(const Menu& src) = delete;
		void display();

		unsigned run();
	};
}
#endif // !SDDS_MENU_H