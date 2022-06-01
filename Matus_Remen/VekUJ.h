#pragma once
#include <string>
#include "../structures/array/array.h"

using namespace std;
class VekUJ {

private:

	structures::Array<int>* muzi;
	structures::Array<int>* zeny;
	structures::Array<int>* VSmuzi;
	structures::Array<int>* VSzeny;


public:

	//konstruktor
	VekUJ() {
		muzi = new structures::Array<int>(101);
		zeny = new structures::Array<int>(101);
		VSmuzi = new structures::Array<int>(3);
		VSzeny = new structures::Array<int>(3);
	}



	//destruktor
	~VekUJ() {
		delete muzi;
		delete zeny;
		delete VSmuzi;
		delete VSzeny;
	}
	/*
	//settery
	void setMuzi(structures::Array<int>* a) {
		muzi = a;
	}
	void setZeny(structures::Array<int>* a) {
		zeny = a;
	}
	//settery EVS
	void setVSMuzi(structures::Array<int>* a) {
		VSmuzi = a;
	}
	void setVSZeny(structures::Array<int>* a) {
		VSzeny = a;
	}
	//koniec settery

	*/
	//pripocitanie, vyuzivam v priradovani 
	void pripocitajVek(VekUJ* v) {
		for (int i = 0; i < muzi->size(); i++) {
			muzi->at(i) += v->getMuzi()->at(i);
		}
		for (int i = 0; i < zeny->size(); i++) {
			zeny->at(i)+= v->getZeny()->at(i);
		}
		for (int i = 0; i < VSmuzi->size(); i++) {
			VSmuzi->at(i) += v->getVSMuzi()->at(i);
		}
		for (int i = 0; i < VSzeny->size(); i++) {
			VSzeny->at(i) += v->getVSZeny()->at(i);
		}
	}
	//koniec pripocitaviana




	//pouzivam pri nacitavani
	void pripocitajVSMuziPRVA(int kolko) {
		VSmuzi->at(0) += kolko;
	}
	void pripocitajVSMuziDRUHA(int kolko) {
		VSzeny->at(1) += kolko;
	}
	void pripocitajVSMuziTRETIA(int kolko) {
		VSmuzi->at(2) += kolko;
	}

	void pripocitajVSZenyPRVA(int kolko) {
		VSzeny->at(0) += kolko;
	}
	void pripocitajVSZenyDRUHA(int kolko) {
		VSzeny->at(1) += kolko;
	}
	void pripocitajVSZenyTRETIA(int kolko) {
		VSzeny->at(2) += kolko;
	}



	//nastavi vek na urcitom mieste
	void nastavVekKtoryKolkoMuzi(int ktory, int kolko) {
		muzi->at(ktory) = kolko;
	}
	void nastavVekKtoryKolkoZeny(int ktory, int kolko) {
		zeny->at(ktory) = kolko;
	}
	

	//vracia pocet podla zadaného veku
	int vratPocetMuzovPodlaVeku(int cislo) {
		if (cislo >= 0 && cislo <= 100) {
			return muzi->at(cislo);
		}
		else {
			return 0;
		}
		
	}
	int vratPocetZienPodlaVeku(int cislo) {
		if (cislo >= 0 && cislo <= 100) {
			return zeny->at(cislo);
		}
		else {
			return 0;
		}

	}

	//vrati pocet ludi na zadanom veku
	int vratVekOboch(int ktore) {
		int dokopy = muzi->at(ktore) + zeny->at(ktore);
		return dokopy;
	}
	//koniec vracania vekov
	

	//vraciam atribúty veky
	structures::Array<int>* getMuzi() {
		return muzi;
	}
	structures::Array<int>* getZeny() {
		return zeny;
	}

	//vraciam vekove skupiny
	structures::Array<int>* getVSZeny() {
		return VSzeny;
	}
	structures::Array<int>* getVSMuzi() {
		return VSmuzi;
	}



	//vratim celkovy pocet Ludi
	int vratPocetLudi() {
		int pocet = 0;
		for (int i = 0; i < muzi->size(); i++)
		{
			pocet += muzi->at(i);
		}
		for (int i = 0; i < zeny->size(); i++)
		{
			pocet += zeny->at(i);
		}
		return pocet;
	}
	
	//vrati pocet ludi v danej ekonomickej vekovej skupine
	int vratPocetEVS(int ktora) {
			int pocet = 0;
			pocet += VSzeny->at(ktora);
			pocet += VSmuzi->at(ktora);
			return pocet;
	}

	
};
