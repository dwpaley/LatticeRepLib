// TestBases.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>

#include "B4.h"
#include "C3.h"
#include "D7.h"
#include "G6.h"
#include "S6.h"
#include "LRL_Cell.h"

template<typename T1, typename T2>
int CheckEquality(const T1& t1, const T2& t2) {
   const double diff = (G6(t1) - G6(t2)).norm();
   int error = 0;
   if (diff / t1.norm() > 1.0E-10) {
      error = 1;
      std::cout << std::endl;
      std::cout << " DIFF " << diff << "  " << diff / t1.norm() << std::endl;
      std::cout << " t1 " << t1.GetName() << "  " << t1 << std::endl;
      std::cout << " t2 " << t2.GetName() << "  " << t2 << std::endl;
   }
   return error;
}

template<typename T>
int CheckFirstConstructors(const T& t, const LRL_Cell& cell) {
   int sum = 0;
   sum += CheckEquality(t, B4(cell));
   sum += CheckEquality(t, C3(cell));
   sum += CheckEquality(t, D7(cell));
   sum += CheckEquality(t, G6(cell));
   sum += CheckEquality(t, S6(cell));
   sum += CheckEquality(t, cell);
   return sum;
}

template<typename T>
int CheckFirstAssignments(const T& t, const LRL_Cell& cell) {
   int sum = 0;

   B4 xB4 = B4(cell);
   C3 xC3 = C3(cell);
   D7 xD7 = D7(cell);
   G6 xG6 = G6(cell);
   S6 xS6 = S6(cell);

   sum += CheckEquality(t, xB4);
   sum += CheckEquality(t, xC3);
   sum += CheckEquality(t, xD7);
   sum += CheckEquality(t, xG6);
   sum += CheckEquality(t, xS6);
   sum += CheckEquality(t, cell);
   return sum;
}

int CheckConstructors(const std::string& s) {
   int errorcount = 0;
   const LRL_Cell cell = LRL_Cell(s);
   errorcount += CheckFirstConstructors(B4(cell), cell);
   errorcount += CheckFirstConstructors(C3(cell), cell);
   errorcount += CheckFirstConstructors(D7(cell), cell);
   errorcount += CheckFirstConstructors(G6(cell), cell);
   errorcount += CheckFirstConstructors(S6(cell), cell);
   errorcount += CheckFirstConstructors(cell, cell);
   return errorcount;
}

int CheckAssignments(const std::string& s) {
   int errorcount = 0;
   const LRL_Cell cell = LRL_Cell(s);

   B4 xB4 = B4(cell);
   C3 xC3 = C3(cell);
   D7 xD7 = D7(cell);
   G6 xG6 = G6(cell);
   S6 xS6 = S6(cell);

   errorcount += CheckFirstAssignments(xB4, cell);
   errorcount += CheckFirstAssignments(xC3, cell);
   errorcount += CheckFirstAssignments(xD7, cell);
   errorcount += CheckFirstAssignments(xG6, cell);
   errorcount += CheckFirstAssignments(xS6, cell);
   errorcount += CheckFirstAssignments(cell, cell);
   return errorcount;
}


int main()
{
   const std::string cell(" 10 13 17 65 76 85");
   std::cout << "total errors for Constructors " << CheckConstructors(cell) << std::endl;
   std::cout << "total errors for Assignments " << CheckAssignments(cell) << std::endl;
   return 0;
}

