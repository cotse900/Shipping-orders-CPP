/*
Final Project Milestone 54
Module: Utils
Filename: Utils.cpp
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

#include <iostream>
#include <cstring>
#include <ctime>


#include "Utils.h"
using namespace std;
namespace sdds {
   Utils ut;
   void Utils::testMode(bool testmode) {
      m_testMode = testmode;
   }
   void Utils::getSystemDate(int* year, int* mon, int* day) {
      if (m_testMode) {
         if(day) *day = sdds_testDay;
         if(mon) *mon = sdds_testMon;
         if(year) *year = sdds_testYear;
      }
      else {
         time_t t = std::time(NULL);
         tm lt = *localtime(&t);
         if (day) *day = lt.tm_mday;
         if (mon) *mon = lt.tm_mon + 1;
         if (year) *year = lt.tm_year + 1900;
      }
   }
   int Utils::daysOfMon(int month, int year)const {
      int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
      int mon = (month >= 1 && month <= 12 ? month : 13)-1;
      return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
   }
   void Utils::alocpy(char*& destination, const char* source) {
       delete[] destination;
       destination = nullptr;
       if (source != nullptr) {
           destination = new char[strlen(source)+1];
           strcpy(destination, source);
       }
   };
   int Utils::getint(const char* prompt) {
       int input;
       char buf;
       bool flag = false;
       if (prompt)
           cout << prompt;
       do {
           cin >> input;
           if (!cin) {
               cout << "Bad integer value, retry: ";
               cin.clear();
               cin.ignore(bufsize, '\n');
           }
           else {
               cin.get(buf);
               if (buf != '\n') {
                   cout << "Enter an integer only. Retry: ";
                   cin.clear();
                   cin.ignore(bufsize, '\n');
               }
               else flag = true;
           }
       } while (!flag);
       return input;
   };
   int Utils::getint(int min, int max, const char* prompt, const char* errMes) {
       int input;
       char buf;
       bool flag = false;
       if (prompt)
           cout << prompt;
       do {
           cin >> input;
           if (!cin) {
               cout << errMes;
               cout << ", retry: ";
               cin.clear();
               cin.ignore(bufsize, '\n');
           }
           else {
               cin.get(buf);
               if (buf != '\n') {
                   cout << "Enter an integer only. Retry: ";
                   cin.clear();
                   cin.ignore(bufsize, '\n');
               }
               else if (input < min || input > max) {
                   cout << "Value out of range [" << min << "<=val<=" << max << "]: ";
               }
               else flag = true;
           }
       } while (!flag);
       return input;
   };

   //modified version of getInt for menu, allow hitting enter key to escape (return -1)
   int Utils::getResponse(int min, int max, const char* prompt, const char* errMes) {
       string str;
       bool flag = false;
       if (prompt)
           cout << prompt;
       do {
           getline(cin, str);
            if (str.size() == 0) {
                flag = true;
                return -1;
            }
            else if (stoi(str) < min || stoi(str) > max) {
                cout << "Value out of range [" << min << "<=val<=" << max << "]: ";
            }
            else flag = true;
       } while (!flag);
       return stoi(str);
   };

   double Utils::getdouble(double min, double max, const char* prompt, const char* errMes) {
       float input;
       char buf;
       bool flag = false;
       if (prompt)
           cout << prompt;
       do {
           cin >> input;
           if (!cin) {
               cout << errMes;
               cout << ", retry: ";
               cin.clear();
               cin.ignore(bufsize, '\n');
           }
           else {
               cin.get(buf);
               if (buf != '\n') {
                   cout << "Enter an number only. Retry: ";
                   cin.clear();
                   cin.ignore(bufsize, '\n');
               }
               else if (input < min || input > max) {
                   cout.setf(ios::fixed);
                   cout.precision(2);
                   cout << "Value out of range [" << min << "<=val<=" << max << "]: ";
               }
               else flag = true;
           }
       } while (!flag);
       return input;
   }

   void Utils::extractChar(std::istream& istr, char ch) const {
       if (ch == istr.peek()) {
           istr.ignore(1, ch);
       }
       else {
           istr.ignore(1000, ch);
           istr.setstate(ios::failbit);
       }
   };

   //Read unknown sized string from stream, allocate required memory to destination and copy the chars
   void Utils::getDescription(char*& destination, std::ifstream& ifstr)
   {
       if (ifstr.is_open()) {
           std::string temp;
           getline(ifstr, temp, '\t');
           destination = new char[temp.length() + 1];
           strcpy(destination, temp.c_str());
           destination[temp.length()] = '\0';
       }
   };

   //Copy string to char array, useful when we get input from user and save it to class member
   void Utils::StringToCharArr(std::string from, char*& to) {
       if (to != nullptr) {
           delete[] to;
       }
       to = new char[from.length() + 1];
       strcpy(to, from.c_str());
   }

   void Utils::GetString(char*& to) {
        std::string input;
        getline(cin, input);
        ut.StringToCharArr(input, to);
   }
}