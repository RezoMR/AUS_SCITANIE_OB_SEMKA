
#pragma once
#include "KriteriumUjVekovaSkupinaPodiel.h"
#include "VZDELANIE_enum.h"
#include "UzemnaJednotka.h"
#include "FilterInterval.h"



class FilterUJVekovaSkupinaPodiel : public FilterInterval<UzemnaJednotka, double> {

public:

	FilterUJVekovaSkupinaPodiel(EVS_ENUM vekovaSkupina, double minimum, double maximum);

};

 FilterUJVekovaSkupinaPodiel::FilterUJVekovaSkupinaPodiel(EVS_ENUM vekovaSkupina, double minimum, double maximum) :
	 FilterInterval(new KriteriumUJVekovaSkupinaPodiel(vekovaSkupina), minimum, maximum)
{
}

 