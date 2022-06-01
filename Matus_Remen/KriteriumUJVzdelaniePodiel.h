#pragma once

#include "KriteriumUJ.h"

class KriteriumUJVzdelaniePodiel : public KriteriumUJ<double> {
private:
	VZDELANIE_ENUM vzdelanie;
public:
	double evaluate(UzemnaJednotka& uj) override;
	KriteriumUJVzdelaniePodiel(VZDELANIE_ENUM vzdelaniee);
};

inline double KriteriumUJVzdelaniePodiel::evaluate(UzemnaJednotka& uj) {
	int ktore =0;
	string vypis;
	switch (vzdelanie) {
	case BEZUKONCENEHO:
		ktore = 0;
		break;
	case ZAKLADNE:
		ktore = 1;
		break;
	case UCNOVSKE:
		ktore = 2;
		break;
	case STREDNE:
		ktore = 3;
		break;
	case VYSSIE:
		ktore = 4;
		break;
	case VYSOKOSKOLSKE:
		ktore = 5;
		break;
	case BEZVZDELANIA:
		ktore = 6;
		break;
	case NEZISTENE:
		ktore = 7;
		break;
	}
	double podiel = 0;
	double prve = (double)uj.vratPocetVzdelanie(ktore);
	double druhe = (double)uj.vratPocetLudi();

	podiel = prve / druhe;
	podiel = podiel * 100;
	return podiel;
}

inline KriteriumUJVzdelaniePodiel::KriteriumUJVzdelaniePodiel(VZDELANIE_ENUM vzdelaniee)
{
	vzdelanie = vzdelaniee;
}
