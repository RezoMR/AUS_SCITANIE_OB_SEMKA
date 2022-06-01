#pragma once

#include "KriteriumUJ.h"

class KriteriumUJVekPocet : public KriteriumUJ<int> {
private:
	int vek;
	string pohlavie;
public:
	int evaluate(UzemnaJednotka& uj) override;
	KriteriumUJVekPocet(string pohlaviee, int vekk);


};

inline int KriteriumUJVekPocet::evaluate(UzemnaJednotka& uj) {
	
	if (pohlavie == "muz") {
		
		return uj.vratPocetMuzovPodlaVeku(vek);
	}
	if (pohlavie == "zena") {
		return uj.vratPocetZienPodlaVeku(vek);
	}
	
}

inline KriteriumUJVekPocet::KriteriumUJVekPocet(string pohlaviee, int vekk)
{
	vek = vekk;
	pohlavie = pohlaviee;
}
