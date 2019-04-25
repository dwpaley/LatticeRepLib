#ifndef LabeledSellaMatricesForDeloneType_H
#define LabeledSellaMatricesForDeloneType_H

#include <string>
#include <vector>

#include "MatS6.h"
#include "S6_Ordinals.h"
#include "StoreResults.h"

class LabeledSellaMatricesForDeloneType {
public:
   LabeledSellaMatricesForDeloneType(){}
   LabeledSellaMatricesForDeloneType(
      const std::string& label,
      const LabeledSellaMatrices& prjs,
      const LabeledSellaMatrices& perps,
      const LabeledSellaMatrices& toCanons);
   std::vector<LabeledSellaMatricesForDeloneType>
      ProcessVectorMapToPerpsAndProjectors
      (const std::map<std::string, std::vector<S6_Ordinals> >& themap);

   size_t size() const { return m_perps.size(); }

   void WriteSellaMatrices( const std::vector<LabeledSellaMatricesForDeloneType>& matsForAllDeloneTypes) const;
   void WriteSellaMatrices(const std::string& functionName, const std::string& label, const std::vector<MatS6>& mat) const;

   void InsertMatricesForDeloneType(const std::string& s);
   std::vector<MatS6> GetPrj(const std::string& s);
   std::vector<MatS6> GetPerp(const std::string& s);
   std::vector<MatS6> GetTocanon(const std::string& s);

private:

   static double Fraction(const double d, const S6& s);
   static unsigned long Index6(const unsigned long i, const unsigned long j);
   static MatS6 ProjectorFromVector(const std::string& label, const S6& s);
   static MatS6 ToCanon(const S6& s);
   static MatS6 ToCanon(const S6_Ordinals& s);
   bool AlreadyHasThisProjector(const MatS6& m, const LabeledSellaMatricesForDeloneType& lsm) const;
   void DoPerps(const std::vector<LabeledSellaMatricesForDeloneType>& matsForAllDeloneTypes) const;
   void DoPrjs(const std::vector<LabeledSellaMatricesForDeloneType>& matsForAllDeloneTypes) const;
   void DoToCanon(const std::vector<LabeledSellaMatricesForDeloneType>& matsForAllDeloneTypes) const;

   std::string m_label;
   std::vector<MatS6> m_perps;
   std::vector<MatS6> m_prjs;
   std::vector<MatS6> m_toCanons;
};

#endif  // LabeledSellaMatricesForDeloneType_H