#pragma once

#include "KriteriumUJVzdelaniePocet.h"
#include "KriteriumUJVzdelaniePodiel.h"
#include "VZDELANIE_enum.h"
#include "UzemnaJednotka.h"
#include "UZEMNEJEDNOTKY.h"
#include "FilterInterval.h"


class FilterUJVzdelaniePodiel : public FilterInterval<UzemnaJednotka, double> {

public:
	FilterUJVzdelaniePodiel(VZDELANIE_ENUM typVzdelania, int minimum, int maximum);

};

inline FilterUJVzdelaniePodiel::FilterUJVzdelaniePodiel(VZDELANIE_ENUM typVzdelania, int minimum, int maximum) :
	FilterInterval(new KriteriumUJVzdelaniePodiel(typVzdelania), minimum, maximum)
{
}