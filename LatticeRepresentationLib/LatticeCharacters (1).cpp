#include "DeloneType.h"

DeloneType::DeloneType(const std::string& deloneType, 
	const std::string& bravaisType, const std::string& character, const std::pair<std::string, MatS6 >& fromCanon)
	: m_deloneName(deloneType)
	, m_bravaisType(bravaisType)
	, m_character(character)
	, m_toCentered_E3()
	, m_toCentered_S6(fromCanon.second)
	, m_matrices()
{
}

void DeloneType::AddToLabeledSellaMatricesForDeloneType(
   const std::string& label,
   const LabeledSellaMatrices& prjs, 
   const LabeledSellaMatrices& perps,
   const LabeledSellaMatrices& toCanons,
   const LabeledSellaMatrices& toCentereds) {
   m_matrices = LabeledSellaMatricesForDeloneType(label, prjs, perps, toCanons);
}