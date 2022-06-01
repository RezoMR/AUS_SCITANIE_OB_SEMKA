#pragma once

#include "KriteriumUJ.h"
#include "Kriterium.h"
#include "EVS.h"

class KriteriumUJVekovaSkupinaPodiel : public KriteriumUJ<double> {

public:
	KriteriumUJVekovaSkupinaPodiel(EVS_ENUM skupinaa);
	double evaluate(UzemnaJednotka& uj);
private:
	EVS_ENUM skupina;
};

inline KriteriumUJVekovaSkupinaPodiel::KriteriumUJVekovaSkupinaPodiel(EVS_ENUM skupinaa) :
  skupina(skupinaa)
{
}
inline double KriteriumUJVekovaSkupinaPodiel::evaluate(UzemnaJednotka& uj) {
		double vysledok = 0;
		double prve = 0;
		double druhe = 0;
		switch (skupina) {
			case PREDPRODUKTIVNI:
				prve = (double)uj.vratEVS(0);
				druhe = (double)uj.vratPocetLudi();
				vysledok = prve / druhe;
				vysledok = vysledok * 100;
				return vysledok;
				break;
				case
				PRODUKTIVNI:
					prve = (double)uj.vratEVS(1);
					druhe = (double)uj.vratPocetLudi();
					vysledok = prve / druhe;
					vysledok = vysledok * 100;
					return vysledok;
					break;
					case
					POPRODUKTIVNI:
						prve = (double)uj.vratEVS(2);
						druhe = (double)uj.vratPocetLudi();
						vysledok = prve / druhe;
						vysledok = vysledok * 100;
						return vysledok;
						break;

		}
		return vysledok;
}

