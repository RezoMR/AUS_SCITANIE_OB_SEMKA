#pragma once

#include "KriteriumUjVekovaSkupinaPocet.h"


#include "EVS.h"
#include "UzemnaJednotka.h"
#include "FilterInterval.h"

//#include "FilterInterval.h"

class FilterUJVekovaSkupinaPocet : public FilterInterval<UzemnaJednotka, int> {

public:

	FilterUJVekovaSkupinaPocet(EVS_ENUM vekovaSkupina, int minimum, int maximum);

};

FilterUJVekovaSkupinaPocet::FilterUJVekovaSkupinaPocet(EVS_ENUM vekovaSkupina, int minimum, int maximum) :
	FilterInterval(new KriteriumUJVekovaSkupinaPocet(vekovaSkupina), minimum, maximum)
{
}