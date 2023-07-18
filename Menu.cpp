/*
Final Project Milestone 54
Module: Menu
Filename: Menu.cpp
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

#include <iostream>
#include <cstring>
#include "Menu.h"
#include "Utils.h"

using namespace std;

namespace sdds
{

	void Menu::setEmpty() {
		if (text) {
			delete[] text;
		}
		text = nullptr;
	};
	Menu::Menu(const char* optiontext, unsigned numoptions) {
		setEmpty();
		if (optiontext && optiontext[0] != '\0') {
			text = new char[strlen(optiontext) + 1];
			strcpy(text, optiontext);
		}
		numoptions > 0 && numoptions <= maxoptions ? options = numoptions : options = 0;
	};
	Menu::Menu(const Menu& src) {
		this->options = src.options;
		setEmpty();
		if (src.text) {
			this->text = new char[strlen(src.text) + 1];
			strcpy(text, src.text);
		}
	};
	Menu::~Menu() {
		setEmpty();
	};
	void Menu::display() {
		cout << text;
		cout << "0- Exit" << endl;
	};
	unsigned Menu::run() {
		display();
		int selectoption = ut.getint(0, options, "> ", "Invalid Integer, retry: ");
		return selectoption;
	};

}