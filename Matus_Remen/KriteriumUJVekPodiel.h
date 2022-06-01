#pragma once

#include "KriteriumUJ.h"

class KriteriumUJVekPodiel : public KriteriumUJ<double> {
private:
	int vek;
	string pohlavie;

public:
	double evaluate(UzemnaJednotka& uj) override;
	KriteriumUJVekPodiel(int vekk, string pohlaviee) {
		vek = vekk;
		pohlavie = pohlaviee;
	}


};

inline double KriteriumUJVekPodiel::evaluate(UzemnaJednotka& uj) {
	double pomer;
	int vybrany = 0;

	if (pohlavie == "muz") {
		
		vybrany = uj.vratPocetMuzovPodlaVeku(vek);
	}
	if (pohlavie == "zena") {
		vybrany = uj.vratPocetZienPodlaVeku(vek);
	}
	
	int vsetko = uj.vratPocetLudi();
	pomer = vybrany / vsetko;
	return (pomer*100);
}