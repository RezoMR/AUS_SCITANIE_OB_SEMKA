#pragma once

#include "KriteriumUJ.h"
#include "EVS.h"

class KriteriumUJVekovaSkupinaPocet : public KriteriumUJ<int>{
private: 
	EVS_ENUM skupina;
public:
	int evaluate(UzemnaJednotka& uj);
	KriteriumUJVekovaSkupinaPocet(EVS_ENUM skup);

};
inline KriteriumUJVekovaSkupinaPocet::KriteriumUJVekovaSkupinaPocet(EVS_ENUM skup)
{
	skupina = skup;
}

inline int KriteriumUJVekovaSkupinaPocet::evaluate(UzemnaJednotka& uj) {
	switch (skupina) {
		case
		PREDPRODUKTIVNI:
			return uj.vratEVS(0);
			break;
			case
			PRODUKTIVNI:
				return uj.vratEVS(1);
				break;
			case
			POPRODUKTIVNI:
					return uj.vratEVS(2);
					break;

	}
	return 0;
}
