/*
Final Project Milestone 54
Module: Perishable
Filename: Perishable.cpp
Version 1.0
Author	Chungon Tse, 154928188, Section NDD, cotse@myseneca.ca
Revision History
-----------------------------------------------------------
Date      Reason
2022/4/1  Preliminary release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#include <iostream>
#include <fstream>
#include <cstring>
#include "Perishable.h"
#include "Utils.h"
#include "Date.h"
#include "Item.h"
#include <string>
using namespace std;
using namespace sdds;

namespace sdds
{
    bool Perishable::linear() const
    {
        return Item::linear();
    }
    void Perishable::linear(bool isLinear){
        Item::linear(isLinear);
    };

    Perishable::Perishable() {
        m_sku = 0;
        handlingInstructions = nullptr;
    };

    Perishable::Perishable(int sku)
    {
        m_sku = sku;
        handlingInstructions = nullptr;
    };

    Perishable::Perishable(const Perishable& pish) {
        m_sku = 0;
        handlingInstructions = nullptr;
        Perishable::operator=(pish);
    };
    Perishable& Perishable::operator=(const Perishable& pish) {
        if (this != &pish) {
            expiryDate = pish.expiryDate;
            if (pish.handlingInstructions != nullptr) {
                if (handlingInstructions != nullptr) {
                    delete[] handlingInstructions;
                    handlingInstructions = nullptr;
                }
                handlingInstructions = new char[strlen(pish.handlingInstructions) + 1];
                ut.alocpy(handlingInstructions, pish.handlingInstructions);
            }
        }
        Item::operator=(pish);

        return *this;
    };
    Perishable::~Perishable() {
        if (handlingInstructions) {
            delete[] handlingInstructions;
            handlingInstructions = nullptr;
        }
    };
    const Date& Perishable::expiry() const {
        return expiryDate;
    };
    int Perishable::readSku(std::istream& istr) {
        m_sku = ut.getint(10000, 39999, "SKU: ", "Invalid Integer");
        return *this;
    };
    std::ofstream& Perishable::save(std::ofstream& ofstr)const {
        if (m_state) {
            Item::save(ofstr);
            ofstr << '\t';
            if (handlingInstructions && handlingInstructions != nullptr) {
                ofstr << handlingInstructions;
            }
            //change date formatting for file writing
            ((Date&)(expiryDate)).formatted(false);
            ofstr << '\t';
            expiryDate.write(ofstr);
            ((Date&)(expiryDate)).formatted(true);
        }
        return ofstr;
    };
    std::ifstream& Perishable::load(std::ifstream& ifstr) {
        Item::load(ifstr);
        if (ifstr.is_open()) {
            ut.extractChar(ifstr, '\t');
            ut.getDescription(handlingInstructions, ifstr);
            expiryDate.formatted(true); //default value
            ifstr >> expiryDate;

        }
        if (ifstr.fail()) {
            m_state = "Input file stream read (perishable) failed!";
        }

        return ifstr;
    };
    std::ostream& Perishable::display(std::ostream& ostr)const {
        if (!m_state) {
            ostr << m_state;
        }
        else if (this->linear()) {
            Item::display(ostr);
            //rework in Aug 2022
            //ostr << " |";//minus extra chars here
            if (handlingInstructions != nullptr && handlingInstructions[0] != '\0') {
                ostr << "*";
            }
            else {
                ostr << " ";
            }
            ((Date&)(expiryDate)).formatted(true);
            expiryDate.write(ostr);
        }
        else
        {
            ostr << "Perishable ";
            Item::display(ostr);
            ostr << endl;
            ostr << "Expiry date: ";
            
            ((Date&)(expiryDate)).formatted(true);
            expiryDate.write(ostr);
            ostr << endl;
            if (handlingInstructions != nullptr && handlingInstructions[0] != '\0') {
                ostr << "Handling Instructions: " << handlingInstructions;
                ostr << endl;
            }
        }
        return ostr;
    };
    std::istream& Perishable::read(std::istream& istr) {
        Item::read(istr);
        if (handlingInstructions != NULL) {
            delete[] handlingInstructions;
            handlingInstructions = nullptr;
        }

        cout << "Expiry date (YYMMDD): ";
        istr >> expiryDate;
        ut.extractChar(istr, '\n');
        cout << "Handling Instructions, ENTER to skip: ";

        std::string local_instruction;
        getline(cin, local_instruction);

        cout << endl;

		int instructionSize = local_instruction.size();
		
        if (handlingInstructions != nullptr) {
            delete[] handlingInstructions;
            handlingInstructions = nullptr;
            handlingInstructions = new char[instructionSize + 1];
        }
        else {
            handlingInstructions = new char[instructionSize + 1];
        }
		strcpy(handlingInstructions, local_instruction.c_str());

        if (handlingInstructions[0] != '\n') {
            handlingInstructions[strcspn(handlingInstructions, "\n")] = 0; //remove trailing newline char
        }
        else {
            handlingInstructions = nullptr;
        }
        if (istr.fail()) {
            m_state = "Perishable console data entry failed!";
        }
        return istr;
    };
}