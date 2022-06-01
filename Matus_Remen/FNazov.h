#pragma once
#include "Filter.h"
#include "KompozitnyFilter.h"
#include "UzemnaJednotka.h"
#include "FilterSHodnotou.h"

template<typename O, typename ValueType>

class FilterUJNazov : Filter<UzemnaJednotka*> {
public:
	FilterUJNazov(UzemnaJednotka*, string nazov) : FilterSHodnotou(new KriteriumUJNazov(), nazov) {

	}

	virtual ~FilterUJNazov() = default;

};

