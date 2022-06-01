#pragma once
#include "Filter.h"
#include "KompozitnyFilter.h"
#include "UzemnaJednotka.h"
#include "KriteriumUJPrislusnost.h"
#include "FilterSHodnotou.h"



class FilterUJPrislusnost :public FilterSHodnotou<UzemnaJednotka, bool> 
{

	public:
	FilterUJPrislusnost(UzemnaJednotka* u);

	
};

inline FilterUJPrislusnost::FilterUJPrislusnost(UzemnaJednotka* u) :
	FilterSHodnotou(new KriteriumUJPrislusnost(*u), true)
{
}

