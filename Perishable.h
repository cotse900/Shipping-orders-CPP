/*
Final Project Milestone 54
Module: Perishable
Filename: Perishable.h
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
#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H
#include <iostream>
#include "Item.h"
#include "Date.h"
namespace sdds
{
    class Perishable : public Item
    {
        Date expiryDate;
        char* handlingInstructions;
    protected:
        bool linear() const;
    public:
        Perishable();
        Perishable(int sku);
        Perishable(const Perishable& pish);
        Perishable& operator=(const Perishable& pish);
        ~Perishable();
        //query
        const Date& expiry() const;

        void linear(bool isLinear) override;
        int readSku(std::istream& istr) override;
        std::ofstream& save(std::ofstream& ofstr)const override;
        std::ifstream& load(std::ifstream& ifstr) override;
        std::ostream& display(std::ostream& ostr)const override;
        std::istream& read(std::istream& istr) override;

    };


}
#endif // !SDDS_PERISHABLE_H