#pragma once
#include "Filter.h"
#include "KompozitnyFilter.h"
#include "UzemnaJednotka.h"
#include "../Matus_Remen/UZEMNEJEDNOTKY.h"
#include "KriteriumUJTyp.h"
#include "FilterSHodnotou.h"


class FilterUJTyp :public FilterSHodnotou<UzemnaJednotka, UZEMNEJEDNOTKY> {
public: FilterUJTyp(UZEMNEJEDNOTKY typ);
	
};



inline FilterUJTyp::FilterUJTyp(UZEMNEJEDNOTKY typ) :
	FilterSHodnotou(new KriteriumUJTyp(), typ)
{
}


