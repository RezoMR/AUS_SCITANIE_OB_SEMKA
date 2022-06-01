#pragma once

#include "KriteriumUJ.h"
#include <string>

class KriteriumUJNazov : public KriteriumUJ<string> {

public:
	string evaluate(UzemnaJednotka& uj);
	KriteriumUJNazov();
	

};
inline string KriteriumUJNazov::evaluate(UzemnaJednotka& uj) {
	return uj.getNazov();
}
inline KriteriumUJNazov::KriteriumUJNazov() {

}
