/*
Final Project Milestone 54
Module: Status
Filename: Status.cpp
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
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Status.h"

using namespace std;
namespace sdds
{
    //private methods
    void Status::setEmpty() {
        m_state = nullptr;
    };
    void Status::set(const char* status) {
        if (status != nullptr && status[0] != '\0') {
            m_state = new char[strlen(status) + 1];
            strcpy(m_state, status);
        }
        else {
            setEmpty();
        }
    };
    //constructor
    Status::Status() {
        setEmpty();
        m_val = 0;
    };
    Status::Status(const char* status) {
        set(status);
        m_val = 0;
    };
    Status::Status(int val) {
        m_val = val;
    };
    Status::Status(const Status& st) {
        set(st.m_state);
        m_val = st.m_val;
    };
    Status& Status::operator=(const Status& st) {
        if (this != &st) {
            set(st.m_state);
            m_val = 0;
        }
        return *this;
    };
    Status& Status::operator=(const char* message) {
        if (message) {
            m_state = new char[strlen(message) + 1];
            strcpy(m_state, message);
            m_val = 0;
        }
        return *this;
    };
    Status& Status::operator=(const int val) {
        m_val = val;
        return *this;
    };
    Status::~Status() {
        delete[] m_state;
        m_state = nullptr;
    };
    //type conversion
    Status::operator int() const {
        return m_val;
    };
    Status::operator const char* () const {
        return m_state;
    };
    Status::operator bool() const {
        bool flag = false;
        if (m_state == nullptr) flag = true;
        return flag;
    };
    Status& Status::clear() {
        delete[] m_state;
        m_state = nullptr;
        m_val = 0;
        return *this;
    };
    std::ostream& Status::print(std::ostream& ostr, bool state) const {
        if (*this) {
            if (!state && m_val !=0) {
                ostr << m_val;
            }
        }
        else {
            if (m_val != 0) {
                ostr << "ERR#" << m_val << ": "; //print "ERR#1: " if it is number (not abc)
            }
            ostr << m_state;
        }
        return ostr;
    };
    std::ostream& operator<<(std::ostream& ostr, const Status& st) {
        if (!st) {
            st.print(ostr,false);
        }
        return ostr;
    };
}