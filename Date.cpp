/*
Final Project Milestone 54
Module: Date
Filename: Date.cpp
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
#include <ctime>
#include <iomanip>
#include "Date.h"
#include "Utils.h"

using namespace std;

namespace sdds
{
    bool Date::validate() {
        bool flag = false;
        
        if (year >= minyear && year <= maxyear) {
            if (month >= 1 && month <= 12) {
                if (day >= 1 && day <= ut.daysOfMon(month, year)){
                    m_state = "";
                    m_state = valid;
                    flag = true;
                }
                else {
                    m_state = "Invalid day in date";
                    m_state = invalid_day;
                    flag = false;
                }
            }
            else {
                m_state = "Invalid month in date";
                m_state = invalid_month;
                flag = false;
            }
        }
        else {
            m_state = "Invalid year in date";
            m_state = invalid_year;
            flag = false;
        }
        return flag;
    };

    int Date::uniqueValue() {
        return year * 372 + month * 31 + day;
    };

    void Date::set(int yy, int mm, int dd) {
        year = yy;
        month = mm;
        day = dd;
    };
    Date::Date() {
        m_formatted = true;
        year = 0;
        month = 0;
        day = 0;
        ut.getSystemDate(&year, &month, &day);
    };
    Date::Date(int yy, int mm, int dd) {
        m_formatted = true;
        set(yy, mm, dd);
        validate();
    };
    Date& Date::operator=(const Date& dt) {
        if (this != &dt) {
            m_formatted = dt.m_formatted;
            set(dt.year, dt.month, dt.day);
        }
        return *this;
    };

    //comparison
    bool Date::operator==(const Date& rhs) {
        int compare = rhs.year * 372 + rhs.month * 31 + rhs.day;
        return ( this->uniqueValue() == compare);
    };
    bool Date::operator!=(const Date& rhs) {
        int compare = rhs.year * 372 + rhs.month * 31 + rhs.day;
        return !(this->uniqueValue() == compare);
    };
    bool Date::operator<(const Date& rhs) {
        int compare = rhs.year * 372 + rhs.month * 31 + rhs.day;
        return this->uniqueValue() < compare;
    };
    bool Date::operator>(const Date& rhs) {
        int compare = rhs.year * 372 + rhs.month * 31 + rhs.day;
        return this->uniqueValue() > compare;
    };
    bool Date::operator<=(const Date& rhs) {
        int compare = rhs.year * 372 + rhs.month * 31 + rhs.day;
        return this->uniqueValue() <= compare;
    };
    bool Date::operator>=(const Date& rhs) {
        int compare = rhs.year * 372 + rhs.month * 31 + rhs.day;
        return this->uniqueValue() >= compare;
    };
    //accessor or getter
    const Status& Date::state(){
        return m_state;
    };
    
    //modifier
    Date& Date::formatted(bool attribute) {
        m_formatted = attribute;
        return *this;
    };
    Date::operator bool() const {
        return m_formatted;
    };
    std::ostream& Date::write(std::ostream& ostr) const {
        if (m_formatted) {
            ostr << year << "/";
            ostr.width(2);
            ostr.fill('0');
            ostr << month << "/" << day;
        }
        else {
            int v = year % 100;
            ostr << v;
            ostr.width(2);
            ostr.fill('0');
            ostr << month << day;
        }
        ostr.fill(' '); // reset fill
        return ostr;
    };
    istream& Date::read(istream& istr) {
        int count = 0; //check number of digits
        int m_count_val, m_val; //m_count_val for counting digits
        istr >> m_val;

        if (!cin.fail()) {
            //calculate how many digits are in there
            m_count_val = m_val;
            do {
                m_count_val /= 10;
                ++count;
            } while (m_count_val != 0);

            //If the value is a four digits integer then the Date is read as: MMDD and the year is set to the current system year.
            if (count <= 4) //added == 2 for "12", should throw incorrect month (in example)
            {
                day = m_val % 100;
                month = m_val / 100;

                //current year
                time_t t = time(0);
                tm* now = localtime(&t);
                year = 1900 + now->tm_year; //2022
            }

            //If the value is a six digits integer then the date is read as: YYMMDD.
            else if (count <= 6)
            {
                day = m_val % 100;
                month = (m_val % 10000) / 100;
                year = m_val / 10000 + 2000;
            }

            if (!validate()) {
                istr.setstate(ios::badbit);
            }
        }
        else {
            //non-integer
            istr.setstate(ios::badbit);
            m_state = "Invalid date value";
            m_state = 0;
        }


        return istr;
    };
    std::ostream& operator<<(std::ostream& ostr, Date& dt) {
        return dt.write(ostr);
    };
    std::istream& operator>>(std::istream& istr, Date& dt) {
        return dt.read(istr);
    };
}