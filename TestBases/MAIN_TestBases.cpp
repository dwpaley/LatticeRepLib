// TestBases.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>

#include "B4.h"
#include "C3.h"
#include "D7.h"
#include "G6.h"
#include "S6.h"
#include "S6dist.h"
#include "Selling.h"
#include "LRL_Cell.h"
#include "LRL_Cell_Degrees.h"
#include "PairReporter.h"
#include "rhrand.h"
#include "StoreResults.h"


StoreResults<unsigned long, PairReporter<S6, LRL_Cell_Degrees> > g_storePositiveCount(4);
StoreResults<unsigned long, S6 > g_storePositiveCountFailed(4);
StoreResults<unsigned long, unsigned long > g_storeChoice(0);

static int s6RandomSeed = 1;
static RHrand rhrand(s6RandomSeed);

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

unsigned long CountPositive(const S6& s6) {
   unsigned long sum = 0;
   for (unsigned long i = 0; i < 6; ++i) sum += (s6[i] > 0.0) ? 1 : 0;
   return sum;
}

bool IsFlat(const LRL_Cell_Degrees& c) {
   for (unsigned long i = 3; i < 6; ++i) {
      if (c[0] > 0.0 && (c[i] < 0.0001 || c[i] > 179.999) ) return true;
   }
   return false;
}

S6 RandomUnreduceOne(const S6& s6) {
   const double choice = 12.0 * rhrand.urand();

   if (choice < 1) return S6Dist::Unreduce11(s6);
   else if (choice < 2) return S6Dist::Unreduce12(s6);
   else if (choice < 3) return S6Dist::Unreduce21(s6);
   else if (choice < 4) return S6Dist::Unreduce22(s6);
   else if (choice < 5) return S6Dist::Unreduce31(s6);
   else if (choice < 6) return S6Dist::Unreduce32(s6);
   else if (choice < 7) return S6Dist::Unreduce41(s6);
   else if (choice < 8) return S6Dist::Unreduce42(s6);
   else if (choice < 9) return S6Dist::Unreduce51(s6);
   else if (choice < 10) return S6Dist::Unreduce52(s6);
   else if (choice < 11) return S6Dist::Unreduce61(s6);
   return S6Dist::Unreduce62(s6);
}

S6 RandomUnreduceTwo(const S6& s6) {
   S6 s(s6);
   while (CountPositive(s) < 2)
      s = RandomUnreduceOne(s);
   return s;
}

S6 RandomUnreduceThree(const S6& s6) {
   S6 s(s6);
   while (CountPositive(s) < 3)
      s = RandomUnreduceOne(s);
   return s;
}

S6 randS6( void ) {
   S6 s6;
   for (unsigned long i = 0; i < 6; ++i)
      s6[i] = -rhrand.urand();

   const double choice = rhrand.urand();
   // the constants are chosen from results for 
   // random generation of valid cells !!!!!!!!!!!!!!!!
   // but they are somewhat random and can be adjusted.
   if (choice < 0.055) return s6;
   else if (choice < 0.68) return RandomUnreduceOne(s6);
   else return RandomUnreduceTwo(s6);
}

void TestTetrahedron() {


   for (unsigned long kkkk = 0; kkkk < 1000000; ++kkkk) {
      const S6 s6 = randS6();
      const double last = s6[5];
      const unsigned long positive = CountPositive(s6);
      const LRL_Cell_Degrees c = LRL_Cell_Degrees(s6);
      const PairReporter<S6, LRL_Cell_Degrees> dataPair(std::make_pair(s6, c));
      if (c.GetValid()) {
         g_storePositiveCount.Store(positive, dataPair);
      }
      else {
         double a = c[0];
         double alpha = c[3];
         if (positive == 0) {
            std::cout << " trouble 0  " << kkkk << std::endl;
            std::cout << dataPair << std::endl;
         }
         g_storePositiveCountFailed.Store(positive, s6);
      }
   }
   g_storePositiveCount.SetTitle("Valid Cells **********************************");
   g_storePositiveCountFailed.SetTitle("Invalid Cells **********************************");
   g_storePositiveCount.SetKeyName("#positive");
   g_storePositiveCountFailed.SetKeyName("#positive");

   g_storePositiveCount.ShowResults();
   g_storePositiveCountFailed.ShowResults();
   exit(0);
}

int main()
{
   TestTetrahedron();
   const std::string cell(" 10 13 17 65 76 85");
   std::cout << "total errors for Constructors " << CheckConstructors(cell) << std::endl;
   std::cout << "total errors for Assignments " << CheckAssignments(cell) << std::endl;
   C3 c1("1 2 3 4 5 6");
   C3 c2("6 5 4 3 2 1");
   C3 c3 = c1 + c2;
   std::cout << c1 << std::endl;
   std::cout << c2 << std::endl;
   std::cout << c3 << std::endl;
   std::cout << c3 - c1 << std::endl;
   return 0;
}

