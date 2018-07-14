// PatLv_Reduction.cpp : Defines the entry point for the console application.
//

#include "D7.h"
#include "GenerateRandomLattice.h"
#include "LRL_Cell_Degrees.h"
#include "Niggli.h"
#include "Pattlv.h"


int main()
{
   int seed(19191);
   GenerateRandomLattice<G6> grl(seed);
   S6 test;
   S6 s6out;
   G6 g6out;
   S6 deout;
   const unsigned long nReduceSamples = 10;
   for (unsigned long i = 0; i < nReduceSamples; ++i) {
      test = grl.GenerateExtreme();
      std::cout << std::endl;
      G6 nigout;
      Niggli::Reduce(G6(test), nigout);
      S6 selout;
      Selling::Reduce(test, selout);
      const bool b = Pattlv::ReduceS6ToNiggli(test, g6out);
      if (!b) std::cout << "FALSE" << std::endl;
      std::cout << "Selling" << D7(selout) << std::endl;
      std::cout << "Niggli                    " << D7(nigout) << std::endl;
      std::cout << "new reduction trial output" << D7(g6out) << std::endl;
      if ((g6out - nigout).norm() < 1.0E-5) std::cout << "OK " << std::endl;

      std::cout << std::endl;
      //Selling::Reduce(test, s6out);
      //Delone::Reduce(test, deout);
      //Niggli::Reduce(G6(test), g6out);

      //std::cout << "input (extreme) " << LRL_Cell_Degrees(test) << std::endl;
      //std::cout << "Niggli reduced " << LRL_Cell_Degrees(g6out) << std::endl;
      //std::cout << "Selling reduced " << LRL_Cell_Degrees(s6out) << std::endl;
      //std::cout << "Delone reduced " << LRL_Cell_Degrees(deout) << std::endl;
      //std::cout << "Allman " << LRL_Cell_Degrees(Allman::Reduce(g6out)) << std::endl << std::endl;
   }

   return 0;
}

