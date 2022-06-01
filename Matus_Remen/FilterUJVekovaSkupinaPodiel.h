/*
#pragma once
#include "KriteriumUjVekovaSkupinaPodiel.h"
#include "VZDELANIE_enum.h"
#include "UzemnaJednotka.h"
#include "FilterInterval.h"



class FilterUJVekovaSkupinaPodiel : public FilterInterval<UzemnaJednotka, int> {

public:

	FilterUJVekovaSkupinaPodiel(EVS_ENUM vekovaSkupina, int minimum, int maximum);

};

 FilterUJVekovaSkupinaPodiel::FilterUJVekovaSkupinaPodiel(EVS_ENUM vekovaSkupina, int minimum, int maximum) :
	 FilterInterval(new KriteriumUJVekovaSkupinaPodiel(vekovaSkupina), minimum, maximum)
{
}

 */