#pragma once
#include "../structures/list/array_list.h"
#include "Filter.h"

template <typename ObjectType>
class KompozitnyFilter : public Filter<ObjectType>
{

protected:
	structures::ArrayList<Filter<ObjectType>*>* pouzite = new structures::ArrayList<Filter<ObjectType>*>();

public:
	KompozitnyFilter();
	~KompozitnyFilter();
	void pridajFilter(Filter<ObjectType>* filter);
};

template<typename ObjectType>
inline KompozitnyFilter<ObjectType>::KompozitnyFilter()
{
}

template<typename ObjectType>
inline KompozitnyFilter<ObjectType>::~KompozitnyFilter()
{
	delete pouzite;
	pouzite = nullptr;
}

template<typename ObjectType>
inline void KompozitnyFilter<ObjectType>::pridajFilter(Filter<ObjectType>* filter)
{
	pouzite->add(filter);
}


