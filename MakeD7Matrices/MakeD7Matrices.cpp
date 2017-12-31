// MakeD7Matrices.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "D7Dist.h"

std::string MakeD7MatrixFunctions(const std::string& s, const int n) {
   std::ostringstream ostr;
   ostr << "   std::vector<std::vector<double> Matrices_" << s << " () {" << std::endl;
   for (int i = 0; i < n; ++i) {
      ostr << "fn" + s << " ();" << std::endl;
   }
   ostr << "}" << std::endl;
   return ostr.str();
}

std::string WriteOneMatrix(const std::string& s, const int n,  const double m[49]) {
   std::ostringstream ostr;
   ostr << "static std::vector<void(*)(const double[], double[]) fn" << s << n << "(const double d[], double d[]) {" << std::endl;
   ostr << "   double out[7]" << std::endl;

   //int nout = 0;
   //for (int j = 0; j < 49; j += 7) {
   //   for (int k = 0; k < 7; ++k) {
   //      ostr << "   out[nout] += m[j+k] * d[k];" << std::endl;
   //   }
   //   ostr << "   ++nout;" << std::endl;
   //}

   ostr << "}" << std::endl;
   return ostr.str();
}

//static std::vector<C3(*)(const C3&)>

int main()
{
   for ( unsigned long mat=0; mat<9; ++mat) {
      std::cout << WriteOneMatrix("d7prj", mat, d7prj[mat]);
   }
   std::cout << MakeD7MatrixFunctions("d7prj", 9) << std::endl;

   return 0;
}

