#pragma once
#include <string>

using namespace std;
class VzdelanieUJ {

private:
	structures::Array<int>* pocty;

public:
	//kon�truktor
	VzdelanieUJ() {
		pocty = new structures::Array<int>(8);
	}

	//de�truktor
	~VzdelanieUJ() {
		delete pocty;
	}

	//vr�ti po�et zadanej skupiny
	int vratPocet(int vz) {
		if (vz < 8 && vz >= 0) {
			return pocty->at(vz);
		}
		else {
			return false;
		}
	}

    //pripo��ta dan� vzdelanie
	void pripocitajKtoreKolko(int ktore, int kolko) {
		pocty->at(ktore) += kolko;
	}

	//vrati cele vzdelanie, atribut
	structures::Array<int>* vratVzdelanie() {
		return pocty;
	}


	//pripo��ta vzdelanie, vyuzivam pri praradovani
	void pripocitajVzdelanie(VzdelanieUJ* v) {
		for (int i = 0; i < pocty->size(); i++)
		{
			pocty->at(i) += v->vratVzdelanie()->at(i);
		}
	}

	//vrati pocet vsetk�ch
	int vratPocetVsetkych() {
		int sucet;
		for (int i = 0; i < pocty->size(); i++)
		{
			sucet += pocty->at(i);
		}
		return sucet;
	}


};
