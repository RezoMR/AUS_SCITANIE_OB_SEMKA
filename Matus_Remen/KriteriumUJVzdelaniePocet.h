#pragma once

#include "KriteriumUJ.h"


	class KriteriumUJVzdelaniePocet : public KriteriumUJ<int> {
	private:
		VZDELANIE_ENUM vzdelanie;

	public:
		int evaluate(UzemnaJednotka& uj) override;
		KriteriumUJVzdelaniePocet(VZDELANIE_ENUM vzdelaniee);
	};

	inline KriteriumUJVzdelaniePocet::KriteriumUJVzdelaniePocet(VZDELANIE_ENUM vzdelaniee)
	{
		vzdelanie = vzdelaniee;
	}

	inline int KriteriumUJVzdelaniePocet::evaluate(UzemnaJednotka& uj) {
		int ktore;
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
		return uj.vratPocetVzdelanie(ktore);
	}

