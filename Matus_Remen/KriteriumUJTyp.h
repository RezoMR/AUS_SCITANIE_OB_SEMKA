
#pragma once

#include "KriteriumUJ.h"
#include <string>
#include "UzemnaJednotka.h"


	class KriteriumUJTyp : public KriteriumUJ<UZEMNEJEDNOTKY> {

	public:
		UZEMNEJEDNOTKY evaluate(UzemnaJednotka& uj) override;
		
	};

	inline UZEMNEJEDNOTKY KriteriumUJTyp::evaluate(UzemnaJednotka& uj) {
		return uj.getTyp();
	}

