// TestC3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

#include "C3.h"
#include "LRL_Cell.h"
#include "LRL_ReadLatticeData.h"
#include "LRL_ToString.h"
#include "MatS6.h"
#include "S6.h"
#include "S6Dist.h"
#include "Selling.h"


void TestC3Reduce() {
   S6 s6in("0.1 -0.2 -0.25 -100 -110 -120");
   S6 s6test;
   const bool b = Selling::Reduce(s6in, s6test);
   std::cout << s6in << std::endl << std::endl << std::endl;
   std::cout << s6test << std::endl << std::endl << std::endl;
   std::cout << C3(s6in) << std::endl << std::endl << std::endl;
   std::cout << C3(s6test) << std::endl << std::endl << std::endl;
   std::cout << "reduce by function" << std::endl;
   std::cout << C3::m_reductionFunctions[0](S6("0.1 -0.2 -0.25 -100 -110 -120")) << std::endl;
   std::cout << C3::m_reductionFunctions[1](S6("-0.2 -0.25 -100 0.1 -110 -120")) << std::endl;
   std::cout << C3::m_reductionFunctions[2](S6("-0.2 0.1 -0.25 -100 -110 -120")) << std::endl;
   std::cout << C3::m_reductionFunctions[3](S6("-0.2 -0.25 -100 -110 0.1 -120")) << std::endl;
   std::cout << C3::m_reductionFunctions[4](S6("-0.2 -0.25 0.1 -100 -110 -120")) << std::endl;
   std::cout << C3::m_reductionFunctions[5](S6("-0.2 -0.25 -100 -110 -120 0.1")) << std::endl;
   std::cout << std::endl;
}
/*  0.10000  -0.20000  -0.25000 -100.00000 -110.00000 -120.00000


 -0.10000  -0.10000 -109.90000 -100.10000  -0.15000 -119.90000


(0.100,-100.000) (-0.200,-110.000) (-0.250,-120.000)


(-0.100,-100.100) (-0.100,-0.150) (-109.900,-119.900)


reduce by function
(-0.100,-100.100) (-0.100,-0.150) (-109.900,-119.900)
(-0.300,-0.100) (-0.150,-99.900) (-109.900,-119.900)
(-0.100,-0.150) (-0.100,-110.100) (-99.900,-119.900)
(-0.100,-99.900) (0.000,-0.100) (-109.900,-119.900)
(-0.100,-0.500) (-99.900,-110.250) (-0.100,-120.100)
(-0.100,-0.150) (-109.900,-119.900) (-100.100,-0.100)

*/

int main()
{
   TestC3Reduce();

   LRL_Cell cell("10 12 15 91 92 93");
   S6 s6(cell);
   const C3 c3(s6);
   std::cout << c3 << std::endl << std::endl << std::endl;
   c3.report();
   std::cout << std::endl << std::endl;

   S6Dist s6dist(10000);
   for (unsigned long i = 0; i < 24; ++i) {
      std::cout << C3(S6(MatS6::GetReflection(i) * S6(c3))) << std::endl;
   }
   std::cout << std::endl << std::endl;

   //std::cout << C3(S6(S6Dist::Unreduce11(S6(c3)))) << std::endl;
   //std::cout << C3(S6(S6Dist::Unreduce21(S6(c3)))) << std::endl;
   //std::cout << C3(S6(S6Dist::Unreduce31(S6(c3)))) << std::endl;
   //std::cout << C3(S6(S6Dist::Unreduce41(S6(c3)))) << std::endl;
   //std::cout << C3(S6(S6Dist::Unreduce51(S6(c3)))) << std::endl;
   //std::cout << C3(S6(S6Dist::Unreduce61(S6(c3)))) << std::endl;
   //std::cout << std::endl << std::endl;

   //const std::vector< C3(*)(const C3&)> vr = C3::SetUnreduceFunctionPairs();

   //for (unsigned long i = 0; i < vr.size(); ++i) {
   //   std::cout << vr[i](c3) << std::endl;
   //}

   std::cout << std::endl << std::endl << LRL_ToString(c3) << std::endl;

   return 0;
}

