#pragma once
#include "KriteriumUJVzdelaniePocet.h"
#include "VZDELANIE_enum.h"
#include "UzemnaJednotka.h"
#include "UZEMNEJEDNOTKY.h"
#include "FilterInterval.h"


class FilterUJVzdelaniePocet : public FilterInterval<UzemnaJednotka, int> {

public:

	FilterUJVzdelaniePocet(VZDELANIE_ENUM typVzdelania, int minimum, int maximum);
};
FilterUJVzdelaniePocet::FilterUJVzdelaniePocet(VZDELANIE_ENUM typVzdelania, int minimum, int maximum) :
	FilterInterval(new KriteriumUJVzdelaniePocet(typVzdelania), minimum, maximum)
{
}