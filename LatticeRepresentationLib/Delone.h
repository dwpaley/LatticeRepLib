#ifndef DELAUNAY_H
#define DELAUNAY_H

#include "S6.h"
#include "B4.h"
#include "MatD7.h"
#include "Selling.h"
#include <set>
class D7;
class MatG6;
class MatD7;

class Delone {

public:
   template<typename TVEC>
   static bool Reduce(const TVEC& d, TVEC& dd) {
      S6 s6out;
      const bool b = Selling::Reduce(S6(d), s6out);
      dd = s6out;
      return b;
   }

   template<typename TVEC, typename TMAT>
   static bool Reduce(const TVEC& d, TMAT& m, TVEC& dd) {
      MatS6 mS6;
      S6 s6out;
      const bool b = Reduce(S6(d), mS6, s6out, 0.0);
      m = mS6;
      dd = d6out;
      return b;
   }

   static bool Reduce(const S6& d, MatS6& m, S6& dd, const double delta);
   static bool Reduce(const S6& d, MatS6& m, S6& dd);
   static D7 sort(const D7& d, MatD7& m);
   static bool IsReduced(const G6& v);
   static bool IsReduced(const G6& v, const double delta);
   static bool IsDelone( const D7& v, const double delta = 1.0E-6 );
         static std::vector<MatD7> GetD7Reflections();

private:
   static int GenMaxMinKey(const D7& d);
   static unsigned long FindRefl(const unsigned long key, const D7& random, std::set<unsigned long>& sr);
};

#endif   //  DELAUNAY_H

