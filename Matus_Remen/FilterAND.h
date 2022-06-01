#pragma once
#include "KompozitnyFilter.h"
template<typename O>

class FilterAND : public KompozitnyFilter<O> {
public:
	bool pass(O& object) override;
	~FilterAND();
};

template<typename O>
inline bool FilterAND<O>::pass(O& object) {

	for (Filter<O>* filter : *KompozitnyFilter<O>::pouzite) {
		if (!filter->pass(object)) {
			return false;
		}
	}
	return true;
}

template<typename O>
inline FilterAND<O>::~FilterAND()
{
	for (Filter<O>* filter : *KompozitnyFilter<O>::pouzite) {
		delete filter;
	}
}
