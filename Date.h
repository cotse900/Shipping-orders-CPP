/*
Final Project Milestone 54
Module: Date
Filename: Date.h
Version 2.0
Author	Chungon Tse, 154928188, Section NDD, cotse@myseneca.ca
Revision History
-----------------------------------------------------------
Date      Reason
2022/4/6  Preliminary release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#include <iostream>
#include "Status.h"
#ifndef SDDS_DATE_H
#define SDDS_DATE_H
namespace sdds {
#define valid 0
#define invalid_year 1
#define invalid_month 2
#define invalid_day 3
    const int maxyear = 2030;
    const int minyear = 2022;
    class Date
    {
        int year;
        int month;
        int day;
        int compare;
        sdds::Status m_state;
        bool m_formatted;
        bool validate();
        int uniqueValue();
        void set(int yy, int mm, int dd);
    public:
        Date();
        Date(int yy, int mm, int dd);
        Date& operator=(const Date& dt);
        //comparison
        bool operator==(const Date& rhs);
        bool operator!=(const Date& rhs);
        bool operator<(const Date& rhs);
        bool operator>(const Date& rhs);
        bool operator<=(const Date& rhs);
        bool operator>=(const Date& rhs);
        //accessor
        const Status& state();
        //modifier
        Date& formatted(bool attribute);
        operator bool() const;
        std::ostream& write(std::ostream& ostr) const;
        std::istream& read(std::istream& istr);
    };
    std::ostream& operator<<(std::ostream& ostr, Date& dt);
    std::istream& operator>>(std::istream& istr, Date& dt);
}

#endif // !SDDS_DATE_H