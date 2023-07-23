/*
Final Project Milestone 56
Module: AidMan
Filename: AidMan.cpp
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

#include <iostream>
#include <string>
#include <cstring>
#include "AidMan.h"
#include "Utils.h"
#include "Date.h"
#include "Menu.h"
#include "Item.h"
using namespace std;

namespace sdds
{
	// This function receives nothing and returns an unsigned integer that is the user's selection of an option in the main menu of the system.
	// The menu function will not change the state of the AidMan class.
	unsigned AidMan::menu() {
		cout << "Aid Management System" << endl;
		cout << "Date: ";
		cout << sdds_testYear << "/";
		if (sdds_testMon < 10) {
			cout << 0 << sdds_testMon;
		}
		else {
			cout << sdds_testMon;
		}
		cout << "/";
		if (sdds_testDay < 10) {
			cout << 0 << sdds_testDay;
		}
		else {
			cout << sdds_testDay;
		}
		cout << endl;
		if (filename == nullptr) {
			cout << "Data file: " << "No file" << endl;
		}
		else {
			cout << "Data file: " << filename << endl;
		}
		cout << "---------------------------------\n";
		m_menu->display();

		// hardcoded 7 here, should retreive no. of commands from menu object
		unsigned input = (unsigned)ut.getint(0, 7, "> ", "Invalid Integer");
		if (input && input <= 7) {
			//if there is no filename defined, whatever option selected is redirected to 7
			if (filename == NULL) {
				input = 7;
			}
			if (input == 1){
				cout << "\n****List Items****\n" ;
				int printed = list();
				if (printed > 0) {
					cout << "Enter row number to display details or <ENTER> to continue:" << endl;
					int response = ut.getResponse(1, iproductsCount, "> ", "Invalid Integer");
					if (response != -1) {
						if (iproducts[response - 1] != NULL) {
							iproducts[response - 1]->linear(false);
							iproducts[response - 1]->display(cout);
						}
					}
				}
				cout << endl;
			}
			if (input == 2) {
				cout << "\n****Add Item****\n";
				if (!(iproductsCount < sdds_max_num_items)) {
					cout << "Database full!" << endl;
				}
				else {
					Menu* add_menu = new Menu(	"1- Perishable\n"
												"2- Non-Perishable\n"
												"-----------------\n"
												, 2);
					
					int option = add_menu->run();
					delete add_menu;
					if (option == 0) {
						cout << "Aborted" << endl;
					}
					else {
						iProduct* newItem;

						int tempSku = ut.getint(10000, 99999, "SKU: ", "Invalid Integer");

						if (search(tempSku) != -1) {
							cout << "Sku: " << tempSku << " is already in the system, try updating quantity instead.\n\n";
							//update qty

							//TODO MS54 (Update Quantity)
							//input = 4;
						}
						else {
							//add new
							if (option == 1 || option == 2) {
								if (option == 1) {
									newItem = new Perishable(tempSku);
									newItem->read(cin);
									if (newItem) {
										//if state is good
										iproducts[iproductsCount] = newItem;
										iproductsCount++;
									}
								}
								else if (option == 2) {
									newItem = new Item(tempSku);
									newItem->read(cin);
									if (newItem) {
										//if state is good
										iproducts[iproductsCount] = newItem;
										iproductsCount++;
									}
								}
							}
						}
					}
				}
			}
			if (input == 3) {
				cout << "\n****Remove Item****\n";
				cout << "Item description: ";
				char* itemDesc = nullptr;
				ut.GetString(itemDesc);
				int printed = list(itemDesc);
				delete[] itemDesc;
				if (printed > 0) {
					int deleteSku = ut.getint(0, 99999, "Enter SKU: ");
					int sku2Index = search(deleteSku);
					if (sku2Index != -1) {
						cout << "Following item will be removed: " << endl;
						iproducts[sku2Index]->linear(false);
						iproducts[sku2Index]->display(cout);
						cout << endl;
						Menu* deleteConfirm = new Menu("Are you sure?\n1- Yes!\n", 1);
						int deleteConfirmRes = deleteConfirm->run();
						delete deleteConfirm;
						if (deleteConfirmRes == 1) {
							remove(sku2Index);
							cout << "Item removed!" << endl;
						}
						else {
							cout << "Aborted!" << endl;
						}
						cout << endl;
					}
				}
			}
			if (input == 4) {
				cout << "\n****Update Quantity****\n";
				cout << "Item description: ";
				char* itemDesc = nullptr;
				ut.GetString(itemDesc);
				int printed = list(itemDesc);
				delete[] itemDesc;
				if (printed > 0) {
					int sku = ut.getint(0, 99999, "Enter SKU: ", "Invalid Integer");
					int productIndexToUpdate = search(sku);
					if (productIndexToUpdate != -1) {
						Menu* updateMenu = new Menu("1- Add\n2- Reduce\n", 2);
						int response = updateMenu->run();
						delete updateMenu;

						//If Add
						if (response == 1) {
							if (iproducts[productIndexToUpdate]->qty() >= iproducts[productIndexToUpdate]->qtyNeeded()) {
								cout << "Quantity Needed already fulfilled!" << endl;
							}
							else {
								int addAmt = ut.getint(1, iproducts[productIndexToUpdate]->qtyNeeded(), "Quantity to add: ", "Invalid Integer");
								(*iproducts[productIndexToUpdate]) += addAmt;
								cout << addAmt << " items added!" << endl;
							}
						}
						//If reduce
						else if (response == 2) {
							int removeAmt = ut.getint(1, iproducts[productIndexToUpdate]->qty(), "Quantity to reduce: ", "Invalid Integer");
							(*iproducts[productIndexToUpdate]) -= removeAmt;
							cout << removeAmt << " items removed!" << endl;

						}
						else if (response == 0) {
							cout << "Aborted!" << endl;
						}
					}
				}
				cout << endl;
			}
			if (input == 5) {
				cout << "\n****Sort****\n";
				iProduct* temp;
				for (int i = 0; i < iproductsCount; i++) {
					for (int j = i + 1; j < iproductsCount; j++) {
						if ((iproducts[j]->qtyNeeded() - iproducts[j]->qty()) > (iproducts[i]->qtyNeeded() - iproducts[i]->qty())) {
							temp = iproducts[i];
							iproducts[i] = iproducts[j];
							iproducts[j] = temp;
						}
					}
				}
				cout << "Sort completed!\n\n";
			}
			if (input == 6) {//rework in Aug 2022
				cout << "\n****Ship Items****\n";
				int day = 0;
				int month = 0;
				int year = 0;
				ut.getSystemDate(&year, &month, &day);
				ofstream file("shippingOrder.txt");
				//file << "Shipping Order, Date: " << date << endl;
				file << "Shipping Order, Date: " << year << "/0" << month << "/" << day << endl;
				file << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
				file << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
				int match = 0;
				for (int i = 0; i < iproductsCount; i++) {
					if (iproducts[i]->qty() == iproducts[i]->qtyNeeded()) {
						iproducts[i]->linear(true);
						/*file.width(4);
						file.setf(ios::right);
						file.fill(' ');
						file << match + 1 << " | ";
						iproducts[i]->save(file);
						file << endl;
						match++;
						remove(i);*/

						match++;
						file << " ";

						file.setf(ios::right);
						file.width(3);
						file << match;
						file.unsetf(ios::right);
						file << " | ";
						iproducts[i]->display(file) << endl;
						remove(i);
					}
				}
				file << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
				cout << "Shipping Order for " << match << " times saved!" << endl << endl;
			}
			if (input == 7) {
				cout << "\n****New/Open Aid Database****\n";
				cout << "Enter file name: ";
				ut.GetString(filename);

				load();
			}
		}

		return input;//refer to Menu.cpp run
	};
	void AidMan::save()
	{
		if (filename != NULL) {
			fileStream = new ofstream();
			fileStream->open(filename);

			if (fileStream->is_open())
			{
				for (int i = 0; i < iproductsCount;i++) {
					iproducts[i]->linear(false);
					iproducts[i]->save(*fileStream);
					*fileStream << endl;
				}
			}
			fileStream->close();
		}
	}
	bool AidMan::load()
	{
		if (iproducts != NULL && iproductsCount > 0) {
			save();
		}

		deallocate();

		if(filename != NULL){
				ifstream file(filename);
				/*
				if the file opening the file was successful, in a loop:
				peeks the first character of the record to determine if the record is a Perishable item or not. (using the first digit of the SKU)
				if the upcoming record is perishable it will create a new Perishable item in the next available iProduct Pointers element.
				if the upcoming record is non-perishable it will create an Item in the next available iProduct Pointers.
				if the next character is not recognized as a valid digit, the ifstream is set into an invalid state.
				if the allocation was a success (Item or Perishable)
				calls the load method of the item to load the data from the file.
				the loaded item is checked to be in a good state, if true, number of iProduct Items is added by one, if false the loaded item is deleted.
				*/
				if (file.fail()) {
					cout << "Failed to open " << filename << " for reading!" << endl;
					Menu* newFileDialog = new Menu("Would you like to create a new data file?\n1- Yes!\n", 1);
					int response = newFileDialog->run();
					delete newFileDialog;
					if (response == 0) {
						filename = nullptr; //not successful
						cout << endl;
						return false;
					}
					if (response == 1) {
						//If the user selects yes, it will create an empty file under the same name and in any case, the function exits after.
						save();
						return true;
					}
				}
				int i = 0;
				while(file.is_open()) {
					char peek = file.peek();
					if (peek == EOF) {
						break; //file ended
					}
					if (peek >= '1' && peek <= '3') {
						iproducts[i] = new Perishable();
					}
					else {
						iproducts[i] = new Item();
					}
					iproducts[i]->load(file);
					i++;
					ut.extractChar(file, '\n');
				}
				iproductsCount = i;
				cout << iproductsCount << " records loaded!\n" << endl;
				return true;
		}
		filename = nullptr; //not successful
		return false;
	}
	int AidMan::list(const char* sub_desc)//rework in Aug 2022
	{
		int listed = 0;
		bool firstRow = true;
		for (int i = 0; i < iproductsCount; i++){
			if (iproducts[i] == nullptr) {
				continue;
			}

			bool descMatch = true; //default is true, if no desc is supplied also mean always true
			if (sub_desc != nullptr) {
				descMatch = (dynamic_cast<Item*>(iproducts[i]))->descriptionMatch(sub_desc);
			}
			if (descMatch) {
				listed++;

				if (firstRow) {
					cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
					cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
					firstRow = false;
				}
				cout.setf(ios::fixed);
				cout.width(3); //from example
				cout.precision(1);
				cout << " " << std::right << i + 1 << " | ";
				iproducts[i]->linear(true);
				iproducts[i]->display(cout);

				/*if (!dynamic_cast<Perishable*>(iproducts[i])) {
					cout << " |";
				}*/

				cout << endl;
			}
		}
		/*int listed = 0;
		cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
		cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
		if (sub_desc == nullptr) {
			for (int i = 0; i < iproductsCount; i++) {
				iproducts[i]->linear(true);
				cout.width(4);
				cout.setf(ios::right);
				cout.fill(' ');
				cout << i + 1 << " | ";
				cout << *iproducts[i] << endl;
				listed++;
			}
		}
		else {
			for (int i = 0; i < iproductsCount; i++) {
				if (strstr(iproducts[i]->desc(), sub_desc)) {
					iproducts[i]->linear(true);
					cout.width(4);
					cout.setf(ios::right);
					cout.fill(' ');
					cout << i + 1 << " | ";
					cout << *iproducts[i] << endl;
					listed++;

				}
			}
		}*/

		cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
		
		if (listed == 0) {
			cout << "The list is emtpy!" << endl;
		}
		return listed;
	}

	int AidMan::search(int sku) const
	{
		int index = 0;
		for (index = 0; index < iproductsCount; index++) {
			if ( *iproducts[index] == sku) {
				return index;
			}
		}
		cout << "SKU not found!" << endl;
		return -1;
	}

	void AidMan::remove(int index) {
		//iProduct* toBeDeleted = iproducts[index];

		//if (iproductsCount > 0 && index >= 0 && index < iproductsCount - 1) {
		//	for (int i = index; i < iproductsCount - 1; i++) {
		//		iproducts[i] = iproducts[i + 1]; //shift addresses
		//	}

		//	delete toBeDeleted;	//clean the deleted iProduct
		//	iproducts[iproductsCount - 1] = nullptr; //null last product pointer, as it is supposed moved to left so this one is no longer needed

		//	iproductsCount--;
		//}
		delete iproducts[index];
		iproducts[index] = nullptr;
		for (int i = index; i < iproductsCount; i++) {
			iproducts[i] = iproducts[i + 1];
		}
		iproductsCount--;
	}

	AidMan::AidMan()
	{
		filename = nullptr;
		fileStream = nullptr;
		m_menu = new Menu("1- List Items\n2- Add Item\n3- Remove Item\n4- Update Quantity\n5- Sort\n6- Ship Items\n7- New/Open Aid Database\n---------------------------------\n", 7);
		iproductsCount = 0;
	};

	void AidMan::setEmpty() {
		this->set(nullptr);
	};
	void AidMan::set(const char* fname) {
		if(filename){
			delete[] filename;
			filename = nullptr;
		}
		
		if (fname != nullptr && fname[0] != '\0') {
			this->filename = new char[strlen(fname) + 1];
			strcpy(filename, fname);
		}
	};
	AidMan::~AidMan() {
		deallocate();
		delete fileStream;

		if (filename) {
			delete[] filename;
			filename = nullptr;
		}
		delete m_menu;
	}
	void AidMan::deallocate()
	{
		if (iproducts != NULL) {
			for (int i = 0; i < iproductsCount; i++)
			{
				if (iproducts[i] != nullptr) {
					delete iproducts[i];
				}
			}
		}
		iproductsCount = 0;
		if (fileStream != NULL) {
			if (fileStream->is_open()) {
				fileStream->close();
			}
		}
	}
	void AidMan::run() {
		unsigned input = this->menu();
		while (input != 0) {
			input = this->menu();
		}

		if (input == 0) {
			save();
			cout << "Exiting Program!" << endl;
			if (filename) {
				delete[] filename;
				filename = nullptr;
			}
			return; //return early, terminate program
		}
	};
}