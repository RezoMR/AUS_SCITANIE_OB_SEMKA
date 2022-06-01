
#pragma once

#include "KriteriumUJ.h"
#include <string>

class KriteriumUJPrislusnost : public KriteriumUJ<bool> {
private:
	UzemnaJednotka vyssi;
public:
	bool evaluate(UzemnaJednotka& uj);
	KriteriumUJPrislusnost(UzemnaJednotka vyssia);
};

inline bool KriteriumUJPrislusnost::evaluate(UzemnaJednotka& uj) {
	return uj.getPrislusnost(vyssi);
}

inline KriteriumUJPrislusnost::KriteriumUJPrislusnost(UzemnaJednotka vyssia)
{
	vyssi = vyssia;
}


