#pragma once
#include "../structures/heap_monitor.h"

#include "VzdelanieUJ.h"
#include "UZEMNEJEDNOTKY.h"
#include "VekUJ.h"
#include "../structures/table/sorted_sequence_table.h"

using namespace std;

class UzemnaJednotka {
private:

	int pocetObyvatelov;
	std::string nazov;
	UzemnaJednotka* vyssia;
	UZEMNEJEDNOTKY typUzemnejJednotky;
	VekUJ* vek;
	VzdelanieUJ* vzdelanie;
	std::string kod;

	//nizsia uzemna jednotka
	structures::SortedSequenceTable<std::string, UzemnaJednotka*>* nizsie = new structures::SortedSequenceTable<std::string, UzemnaJednotka*>();


public:
	//konstruktory destruktor
	UzemnaJednotka(std::string nazovv) {
		nazov = nazovv;
		vek = new VekUJ();
		vzdelanie = new VzdelanieUJ();
	}
	UzemnaJednotka() {
	}
	~UzemnaJednotka() {
		delete nizsie;
		delete vek;
		delete vzdelanie;
	}

	//settery
	void setNizsie(UzemnaJednotka* a) {
		if (!nizsie->containsKey(a->getKod())) {
			nizsie->insert(a->getKod(), a);
		}

	}
	void setTyp(UZEMNEJEDNOTKY typp) {
		typUzemnejJednotky = typp;
	}
	void setVzdelanie(VzdelanieUJ* vz) {
		delete vzdelanie;
		vzdelanie = vz;
	}

	void setVyssia(UzemnaJednotka* uj) {
		vyssia = uj;
	}
	void setKod(std::string s) {
		kod = s;
	}
	void setVek(VekUJ* paVek) {
		delete vek;
		vek = paVek;
		//vek->vytvorSkupiny();
		pocetObyvatelov = vek->vratPocetLudi();
	}

	//gettery
	int vratPocetMuzovPodlaVeku(int vekk) {
		return vek->vratPocetMuzovPodlaVeku(vekk);
	}
	int vratPocetZienPodlaVeku(int vekk) {
		return vek->vratPocetZienPodlaVeku(vekk);
	}
	int vratEVS(int ktora) {
		return vek->vratPocetEVS(ktora);
	}
	
	string vypisTyp(UZEMNEJEDNOTKY typUzemnejJednotkyy) {
		string vysledok;
		switch (typUzemnejJednotkyy) {
			case
			KRAJ:
				vysledok = "kraj";
				break;
				case
				OKRES:
					vysledok = "okres";
					break;
					case
					OBEC:
						vysledok = "obec";
						break;
						case
						STAT:
							vysledok = "stat";
							break;
		}
		return vysledok;
	}
	int vratPocetLudi() {
		return vek->vratPocetLudi();
	}

	string getNazov() {
		return nazov;
	}
	UZEMNEJEDNOTKY getTyp() {
		return typUzemnejJednotky;
	}
	string getKod() {
		return kod;
	}
	int vratPocetVzdelanie(int vz) {
		return vzdelanie->vratPocet(vz);
	}
	string getVyssiaNazov() {
		return vyssia->getNazov();
	}

	UzemnaJednotka* getVyssia() {
		return vyssia;
	}

	VekUJ* vratVek() {
		return vek;
	}
	VzdelanieUJ* vratVzdelanie() {
		return vzdelanie;
	}
	bool getPrislusnost(UzemnaJednotka u) {

		if (typUzemnejJednotky == OBEC) {
			if (u.getTyp() == OKRES) {
				if (getVyssia()->getKod() == u.getKod()) {
					return true;
				}
			}
		}
		if (typUzemnejJednotky == OBEC) {
			if (u.getTyp() == KRAJ) {
				if (getVyssia()->getVyssia()->getKod() == u.getKod()) {
					return true;
				}
			}
		}
		if (typUzemnejJednotky == OKRES) {
			if (u.getTyp() == KRAJ) {
				if (getVyssia()->getKod() == u.getKod()) {
					return true;
				}
			}
		}
		
		return false;
	}
	int vratPocetVsetkychVzdelanie() {
		return vzdelanie->vratPocetVsetkych();
	}

	//pridaj Cisla veky
	void pripocitajVeky(VekUJ* v) {
		vek->pripocitajVek(v);
	}

	//pridaj cisla vzdelanie
	void pripocitajVzdelania(VzdelanieUJ* v) {
		vzdelanie->pripocitajVzdelanie(v);
	}


};