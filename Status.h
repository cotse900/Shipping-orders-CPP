/*
Final Project Milestone 54
Module: Status
Filename: Status.h
Version 1.0
Author	Chungon Tse, 154928188, Section NDD, cotse@myseneca.ca
Revision History
-----------------------------------------------------------
Date      Reason
2022/3/20  Preliminary release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_STATUS_H
#define SDDS_STATUS_H
#include <iostream>
namespace sdds
{
    class Status
    {
        char* m_state{};
        int m_val;
        void setEmpty();
        void set(const char* status);
    public:
        //constructor
        Status();
        Status(const char* status);
        Status(int val);
        Status(const Status& st);
        Status& operator=(const Status& st);
        Status& operator=(const char* message);
        Status& operator=(const int val);
        ~Status();
        //type conversion
        operator int() const;
        operator const char* () const;
        operator bool() const;
        Status& clear();
        std::ostream& print(std::ostream& ostr, bool state = true) const;
    };
    std::ostream& operator<<(std::ostream& ostr, const Status& st);

}
#endif // !SDDS_STATUS_H