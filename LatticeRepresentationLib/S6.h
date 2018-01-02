#ifndef S6_H
#define S6_H

#include "BasisBase.h"
#include "VecN.h"

class LRL_Cell;
class D7;
class B4;
class G6;

#include <ostream>
#include <string>

class S6 : private BasisBase<S6> {
public:
   friend std::ostream& operator<< (std::ostream&, const S6&);
   friend S6 operator* (const double d, const S6& ds);
   friend class D7;

   S6(void);
   S6(const G6& v6);
   S6(const double v[6]);
   S6(const S6& s6);
   S6(const LRL_Cell& c);
   S6(const VecN& v);
   S6(const D7& v7);
   S6(const B4& del);
   S6(const std::string& s);
   S6(const std::vector<double>& v);
   ~S6(void) {}


   S6& operator= (const S6& v);
   S6& operator= (const std::string& s);
   S6& operator= (const G6& v);
   S6& operator= (const D7& v);
   S6& operator= (const B4& v);
   S6& operator= (const LRL_Cell& v);
   S6& operator/= (const double d);
   S6& operator*= (const double d);
   S6 operator+ (const S6& ds) const;
   S6 operator- (const S6& ds) const;
   S6 operator+= (const S6& ds);
   S6 operator-= (const S6& ds);
   S6 operator* (const double d) const;
   S6 operator/ (const double d) const;
   S6 operator- (void) const; // unary
   bool operator== (const S6& s6) const;
   bool operator!= (const S6& s6) const;

   double operator[](const unsigned long n) const { return m_vec[n]; }
   double& operator[](const unsigned long n) { return m_vec[n]; }
   double DistanceBetween(const S6& v1, const S6& v2);
   unsigned long size(void) const { return 6; }
   double norm() const { return m_vec.norm(); }
   double norm(const S6& s6) const { return norm(s6); }
   double Norm() const { return m_vec.norm(); }
   double Norm(const S6& s6) const { return norm(s6); }

   std::vector<double> GetVector(void) const { return m_vec.GetVector(); }
   double* data() const { return const_cast<double*>(m_vec.data()); }
   void SetVector(const std::vector<double>& v) { m_vec = v; }
   bool GetValid(void) const { return m_valid; }
   void SetValid(const bool b) {m_valid = b; }

   double at(const unsigned long n) const { return m_vec[n]; }

   static S6 rand();
   static S6 randDeloneReduced();
   static S6 randDeloneUnreduced();
   static S6 rand(const double d);
   static S6 randDeloneReduced(const double d);
   static S6 randDeloneUnreduced(const double d);

   bool IsAllMinus() const;
   static std::string GetName(void) { return "S6, Selling scalars"; }

private:
   VecN m_vec;
   unsigned long m_dim;
   bool m_valid;
};


#endif