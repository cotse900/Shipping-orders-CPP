/*
Final Project Milestone 54
Module: Utils
Filename: Utils.h
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
#ifndef SDDS_UTILS_H
#define SDDS_UTILS_H

//for parsing unknown size char[]
#include <string>
#include <fstream>

namespace sdds {
   const int sdds_testYear = 2022;
   const int sdds_testMon = 03;
   const int sdds_testDay = 31;
   const int bufsize = 32767;
   class Utils {
      bool m_testMode = false;
   public:
      void getSystemDate(int* year = nullptr, int* mon = nullptr, int* day = nullptr);
      int daysOfMon(int mon, int year)const;
      void testMode(bool testmode = true);

      void alocpy(char*& destination, const char* source);
      int getint(const char* prompt = nullptr);
      int getint(int min, int max, const char* prompt = nullptr, const char* errMes = nullptr);
      int getResponse(int min, int max, const char* prompt = nullptr, const char* errMes = nullptr);
      double getdouble(double min, double max, const char* prompt = nullptr, const char* errMes = nullptr);
      void extractChar(std::istream& istr, char ch) const;
      void getDescription(char*& destination, std::ifstream& ifstr);
      void StringToCharArr(std::string from, char*& to);
      void GetString(char*& to);
   };
   extern Utils ut;
}

#endif // !SDDS_UTILS_H
