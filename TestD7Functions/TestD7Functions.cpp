// TestD7Functions.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cmath>
#include <iostream>

#include "D7DMS.h"
#include "D7Perp.h"
#include "D7Prj.h"
#include "D7Refl.h"

#include "D7Dist.h"
#include "D7Dist_cpp.h"
#include "D7.h"

#include "LRL_CreateFileName.h"
#include "LRL_ToString.h"

template<typename T>
std::vector<double> Multiply(const T m[], const double v[]) {
   std::vector<double> out(7, 0.0);

   int index = 0;
   for (int k = 0; k < 49; k += 7) {
      for (int n = 0; n < 7; ++n) {
         out[index] += m[k + n] * v[n];
      }
      ++index;
   }
   return out;
}


double vnorm(const double d1[], const double d2[]) {
   double sum = 0;
   for (unsigned long i = 0; i < 7; ++i)
      sum += (d1[i] - d2[i])*(d1[i] - d2[i]);
   return sqrt(sum);
}

template<typename T>
unsigned long Tester(std::vector< void(*)(const double[], double[])> vfun, const T d7matrix[][49]) {
   std::vector<double> v(7);
   std::vector<double> out(7, 0.0);
   unsigned long errorCount = 0;

   for (unsigned long i = 0; i < 7; ++i)
      v[i] = rand();

   for (unsigned long i = 0; i < vfun.size(); ++i) {
      vfun[i](v.data(), out.data());
      const std::vector<double> vd = Multiply(d7matrix[i], v.data());
      const double norm = vnorm(vd.data(), out.data());
      if (norm > 0.0) {
         ++errorCount;
         std::cout << "i=" << i << "  " << norm << std::endl;
         std::cout << LRL_ToString(out) << std::endl;
         std::cout << LRL_ToString(vd) << std::endl;
      }
   }
   return errorCount;
}

void CompareMatrixAndFunction() {
   std::vector< void(*)(const double[], double[])> vpr = GetProjectorFunctions();
   std::cout << "Projectors, errors " << Tester(vpr, d7prj) << std::endl;

   std::vector< void(*)(const double[], double[])> vpe = GetPerpFunctions();
   std::cout << "Perps, errors " << Tester(vpe, d7prj_perp) << std::endl;

   std::vector< void(*)(const double[], double[])> vrf = GetReflectionFunctions();
   std::cout << "Reflections, errors " << Tester(vrf, D7Refl) << std::endl;

   std::vector< void(*)(const double[], double[])> vdm = GetDMSFunctions();
   std::cout << "DMS, errors " << Tester(vdm, D7MS) << std::endl;
}

void CompareTiming() {
   const unsigned long count = 1000;

   std::vector<D7> p1, p2;
   for (unsigned long i = 0; i < count; ++i) {
      p1.push_back(20 * D7::rand());
      p2.push_back(20 * D7::rand());
   }

    std::cout << LRL_CreateFileName::Create("", "") << std::endl;
  for (unsigned long i = 0; i < count; ++i) {
      const double d_cpp = D7Dist_cpp(p1[i].data(), p2[i].data());
   }

   std::cout << LRL_CreateFileName::Create("", "") << std::endl;
   for (unsigned long i = 0; i < count; ++i) {
      const double d_hjb = D7Dist(p1[i].data(), p2[i].data());
   }

   std::cout << LRL_CreateFileName::Create("", "") << std::endl;
   std::cout << std::endl;
}

int main()
{
   CompareMatrixAndFunction();
   CompareTiming();
   return 0;
}

