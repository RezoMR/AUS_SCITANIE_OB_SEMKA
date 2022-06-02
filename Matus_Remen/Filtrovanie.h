#pragma once
#include "Filter.h"
#include "FilterInterval.h"
#include "FilterAND.h"




#include "FNazov.h"
#include "FUJTyp.h"
#include "FilterUJPrislusnost.h"
#include "FilterUJVzdelaniePocet.h"
#include "FilterUJVzdelaniePodiel.h"
#include "FilterUJVekovaSkupinaPocet.h"
#include "FilterUJVekovaSkupinaPodiel.h"


#include "../structures/table/unsorted_sequence_table.h"
#include "FilterUJVekovaSkupinaPodiel.h"


using namespace std;
class Filtrovanie {

private:


public:

	void Filtruj(structures::SequenceTable<std::string, UzemnaJednotka*>* vsetko, structures::SequenceTable<std::string, UzemnaJednotka*>* pomocna) {


		bool typ = false;
		bool pris = false;
		bool vzpocet = false;
		bool vzpodiel = false;
		bool vspocet = false;
		bool vspodiel = false;

		FilterAND<UzemnaJednotka>* filtre = new FilterAND<UzemnaJednotka>();


		//structures::UnsortedSequenceTable<string, UzemnaJednotka*>* vyfiltrovane = new structures::UnsortedSequenceTable<string, UzemnaJednotka*>();


		int vyber = 0;
		while (vyber != 99) {
			system("cls");
			//filtrovanie
			cout << "Vyberte ktory filter chcete pouzit:" << "\n";
			//cout << "Filter Nazov" << "\n"
			cout << "Potvrd vyber__________________99" << "\n";
			cout << "\n";

			if (typ == true) {
				cout << "Filter Typ____________________1   <-" << "\n";
			}
			else {
				cout << "Filter Typ____________________1" << "\n";
			}

			if (pris == true) {
				cout << "Filter Prislusnost____________2   <-" << "\n";
			}
			else {
				cout << "Filter Prislusnost____________2" << "\n";
			}
			if (vzpocet == true) {
				cout << "Filter VzdelaniePocet_________3   <-" << "\n";
			}
			else {
				cout << "Filter VzdelaniePocet_________3" << "\n";
			}
			if (vzpodiel == true) {
				cout << "Filter VzdelaniePodiel________4   <-" << "\n";
			}
			else {
				cout << "Filter VzdelaniePodiel________4" << "\n";
			}
			if (vspocet == true) {
				cout << "Filter VekovaSkupinaPocet_____5   <-" << "\n";
			}
			else {
				cout << "Filter VekovaSkupinaPocet_____5" << "\n";
			}

			
			if (vspodiel == true) {
				cout << "Filter VekovaSkupinaPodiel____6   <-" << "\n";
			}
			else {
				cout << "Filter VekovaSkupinaPodiel____6" << "\n";
			}
			
			cin >> vyber;

			if (vyber == 1) {
				typ = true;
			}
			if (vyber == 2) {
				pris = true;
			}
			if (vyber == 3) {
				vzpocet = true;
			}
			if (vyber == 4) {
				vzpodiel = true;
			}
			if (vyber == 5) {
				vspocet = true;
			}
			if (vyber == 6) {
				vspodiel = true;
			}
		}


		int vybranie = 0;
		if (typ == true) {
			cout << "Filter Typ" << "\n";
			cout << "\n";

			cout << "Zadajte typ:" << "\n";
			cout << "KRAJ____1" << "\n";
			cout << "OKRES___2" << "\n";
			cout << "OBEC____3" << "\n";
			cin >> vybranie;
			UZEMNEJEDNOTKY vybranyTyp;
			switch (vybranie) {
			case 1:
				vybranyTyp = UZEMNEJEDNOTKY::KRAJ;
				break;
			case 2:
				vybranyTyp = UZEMNEJEDNOTKY::OKRES;
				break;
			case 3:
				vybranyTyp = UZEMNEJEDNOTKY::OBEC;
				break;
			}
			FilterUJTyp* fut = new FilterUJTyp(vybranyTyp);
			filtre->pridajFilter(fut);
		}
		system("cls");

		if (pris == true) {
			string hladana;
			cout << "Filter Prislusnost" << "\n";
			cout << "\n";
			cout << "Zadajte UzemnuJednotku: " << "\n";

			while (true) {
				if (hladana != "") {
					break;
				}
				getline(cin, hladana);
			}
			string kod = pomocna->find(hladana)->getKod();

			FilterUJPrislusnost* pris = new FilterUJPrislusnost(vsetko->find(kod));
			filtre->pridajFilter(pris);
		}

		system("cls");

		if (vzpocet == true) {
			int VZminimalnaPocet;
			int VZmaximalnaPocet;
			VZDELANIE_ENUM vzdelanieKtorePocet;
			cout << "Filter VzdelaniePocet: " << "\n";
			cout << "\n";
			cout << "Zadajte minimalnu hodnotu:" << "\n";
			cin >> VZminimalnaPocet;
			cout << "Zadajte maximalnu hodnotu:" << "\n";
			cin >> VZmaximalnaPocet;
			cout << "Zadajte typ vzdelania:" << "\n";
			cout << "Vyberte Vzdelanie:" << "\n";
			cout << "BEZUKONCENEHO____1" << "\n";
			cout << "ZAKLADNE_________2" << "\n";
			cout << "UCNOVSKE_________3" << "\n";
			cout << "STREDNE__________4" << "\n";
			cout << "VYSSIE___________5" << "\n";
			cout << "VYSOKOSKOLSKE____6" << "\n";
			cout << "BEZVZDELANIA_____7" << "\n";
			cout << "NEZISTENE________8" << "\n";
			int hodnota = 0;
			cin >> hodnota;
			switch (hodnota) {
			case 1:
				vzdelanieKtorePocet = BEZUKONCENEHO;
				break;
			case 2:
				vzdelanieKtorePocet = ZAKLADNE;
				break;
			case 3:
				vzdelanieKtorePocet = UCNOVSKE;
				break;
			case 4:
				vzdelanieKtorePocet = STREDNE;
				break;
			case 5:
				vzdelanieKtorePocet = VYSSIE;
				break;
			case 6:
				vzdelanieKtorePocet = VYSOKOSKOLSKE;
				break;
			case 7:
				vzdelanieKtorePocet = BEZVZDELANIA;
				break;
			case 8:
				vzdelanieKtorePocet = NEZISTENE;
				break;
			}

			FilterUJVzdelaniePocet* fvzPoc = new FilterUJVzdelaniePocet(vzdelanieKtorePocet, VZminimalnaPocet, VZmaximalnaPocet);
			filtre->pridajFilter(fvzPoc);

		}

		if (vzpodiel == true) {
			int VZMinimalnaPodiel;
			int VZMaximalnaPodiel;
			VZDELANIE_ENUM vzdelanieKtorePodiel;

			cout << "Filter VzdelaniePodiel" << "\n";
			cout << "Zadajte minimalnu hodnotu:" << "\n";
			cin >> VZMinimalnaPodiel;
			cout << "Zadajte maximalnu hodnotu:" << "\n";
			cin >> VZMaximalnaPodiel;
			cout << "Zadajte typ vzdelania:" << "\n";
			cout << "Vyberte Vzdelanie:" << "\n";
			cout << "BEZUKONCENEHO____1" << "\n";
			cout << "ZAKLADNE_________2" << "\n";
			cout << "UCNOVSKE_________3" << "\n";
			cout << "STREDNE__________4" << "\n";
			cout << "VYSSIE___________5" << "\n";
			cout << "VYSOKOSKOLSKE____6" << "\n";
			cout << "BEZVZDELANIA_____7" << "\n";
			cout << "NEZISTENE________8" << "\n";
			int hodnota = 0;
			cin >> hodnota;
			switch (hodnota) {
			case 1:
				vzdelanieKtorePodiel = BEZUKONCENEHO;
				break;
			case 2:
				vzdelanieKtorePodiel = ZAKLADNE;
				break;
			case 3:
				vzdelanieKtorePodiel = UCNOVSKE;
				break;
			case 4:
				vzdelanieKtorePodiel = STREDNE;
				break;
			case 5:
				vzdelanieKtorePodiel = VYSSIE;
				break;
			case 6:
				vzdelanieKtorePodiel = VYSOKOSKOLSKE;
				break;
			case 7:
				vzdelanieKtorePodiel = BEZVZDELANIA;
				break;
			case 8:
				vzdelanieKtorePodiel = NEZISTENE;
				break;
			}
			FilterUJVzdelaniePodiel* fvzPod = new FilterUJVzdelaniePodiel(vzdelanieKtorePodiel, VZMinimalnaPodiel, VZMaximalnaPodiel);
			filtre->pridajFilter(fvzPod);
		}

		if (vspocet == true) {
			int VSMinimalnaPocet;
			int VSMaximalnaPocet;
			EVS_ENUM vekKtorePocet;

			cout << "Filter VekovaSkupinaPocet" << "\n";
			cout << "Zadajte minimalnu hodnotu:" << "\n";
			cin >> VSMinimalnaPocet;
			cout << "Zadajte maximalnu hodnotu:" << "\n";
			cin >> VSMaximalnaPocet;
			cout << "Zadajte typ EVS:" << "\n";
			cout << "PREDPRODUKTIVNA_______1" << "\n";
			cout << "PRODUKTIVNA___________2" << "\n";
			cout << "POPRODUKTIVNA_________3" << "\n";
			int hodnota = 0;
			cin >> hodnota;
			switch (hodnota) {
			case 1:
				vekKtorePocet = PREDPRODUKTIVNI;
				break;
			case 2:
				vekKtorePocet = PRODUKTIVNI;
				break;
			case 3:
				vekKtorePocet = POPRODUKTIVNI;
				break;
			}

			FilterUJVekovaSkupinaPocet* VsPocet = new FilterUJVekovaSkupinaPocet(vekKtorePocet, VSMinimalnaPocet, VSMaximalnaPocet);
			filtre->pridajFilter(VsPocet);
		}
		
		if (vspodiel == true) {
			int VSMinimalnaPodiel;
			int VSMaximalnaPodiel;
			EVS_ENUM vekKtorePodiel;

			cout << "Filter VekovaSkupinaPodiel" << "\n";
			cout << "Zadajte minimalnu hodnotu:" << "\n";
			cin >> VSMinimalnaPodiel;
			cout << "Zadajte maximalnu hodnotu:" << "\n";
			cin >> VSMaximalnaPodiel;
			cout << "Zadajte typ EVS:" << "\n";
			cout << "PREDPRODUKTIVNA_______1" << "\n";
			cout << "PRODUKTIVNA___________2" << "\n";
			cout << "POPRODUKTIVNA_________3" << "\n";
			int hodnota = 0;
			cin >> hodnota;
			switch (hodnota) {
			case 1:
				vekKtorePodiel = PREDPRODUKTIVNI;
				break;
			case 2:
				vekKtorePodiel = PRODUKTIVNI;
				break;
			case 3:
				vekKtorePodiel = POPRODUKTIVNI;
				break;
			}
			FilterUJVekovaSkupinaPodiel* VsPodiel = new FilterUJVekovaSkupinaPodiel(vekKtorePodiel, VSMinimalnaPodiel, VSMaximalnaPodiel);
			filtre->pridajFilter(VsPodiel);
		}
		

		//finalny vypis
		system("cls");
		for (structures::TableItem<std::string, UzemnaJednotka*>* item : *vsetko) {
			if (filtre->pass(*item->accessData())) {
				cout << "--------------------------------" << "Informacie" << "\n";
				KriteriumUJNazov* KNazov = new KriteriumUJNazov();
				cout << "Nazov: " << KNazov->evaluate(*item->accessData()) << "\n";
				delete KNazov;
				KriteriumUJTyp* Ktyp = new KriteriumUJTyp();
				cout << "Typ: " << item->accessData()->vypisTyp(Ktyp->evaluate(*item->accessData())) << "\n";
				delete Ktyp;
				cout << "Pocet obyvatelov: " << item->accessData()->vratPocetLudi() << "\n";
				if (vspocet == true) {
					cout << "--------------------------------" << "Vekove skupiny" << "\n";
					KriteriumUJVekovaSkupinaPocet* KVSpocet = new KriteriumUJVekovaSkupinaPocet(PREDPRODUKTIVNI);
					cout << "Predproduktivny: " << KVSpocet->evaluate(*item->accessData()) << "\n";
					delete KVSpocet;
					KVSpocet = new KriteriumUJVekovaSkupinaPocet(PRODUKTIVNI);
					cout << "Produktivny: " << KVSpocet->evaluate(*item->accessData()) << "\n";
					delete KVSpocet;

					KVSpocet = new KriteriumUJVekovaSkupinaPocet(POPRODUKTIVNI);
					cout << "Poproduktivny: " << KVSpocet->evaluate(*item->accessData()) << "\n";
					delete KVSpocet;

				}
				if (vspodiel == true) {
					cout << "--------------------------------" << "Vekove skupiny" << "\n";
					KriteriumUJVekovaSkupinaPodiel* KVSpocet = new KriteriumUJVekovaSkupinaPodiel(PREDPRODUKTIVNI);
					cout << "Predproduktivny: " << KVSpocet->evaluate(*item->accessData()) << "\n";
					delete KVSpocet;
					KVSpocet = new KriteriumUJVekovaSkupinaPodiel(PRODUKTIVNI);
					cout << "Produktivny: " << KVSpocet->evaluate(*item->accessData()) << "\n";
					delete KVSpocet;

					KVSpocet = new KriteriumUJVekovaSkupinaPodiel(POPRODUKTIVNI);
					cout << "Poproduktivny: " << KVSpocet->evaluate(*item->accessData()) << "\n";
					delete KVSpocet;
				}
				if (vzpocet == true) {
					KriteriumUJVzdelaniePocet* KVZPocet = new KriteriumUJVzdelaniePocet(BEZUKONCENEHO);
					cout << "Bezukonceneho: " << KVZPocet->evaluate(*item->accessData()) << "\n";
					delete KVZPocet;
					cout << "\n";
					KVZPocet = new KriteriumUJVzdelaniePocet(ZAKLADNE);
					cout << "Zakladne: " << KVZPocet->evaluate(*item->accessData()) << "\n";
					delete KVZPocet;

					cout << "\n";
					KVZPocet = new KriteriumUJVzdelaniePocet(UCNOVSKE);
					cout << "Ucnovske: " << KVZPocet->evaluate(*item->accessData()) << "\n";
					delete KVZPocet;

					cout << "\n";
					KVZPocet = new KriteriumUJVzdelaniePocet(STREDNE);
					cout << "Stredne: " << KVZPocet->evaluate(*item->accessData()) << "\n";
					delete KVZPocet;

					cout << "\n";
					KVZPocet = new KriteriumUJVzdelaniePocet(VYSSIE);
					cout << "Vyssie: " << KVZPocet->evaluate(*item->accessData()) << "\n";
					delete KVZPocet;

					cout << "\n";
					KVZPocet = new KriteriumUJVzdelaniePocet(VYSOKOSKOLSKE);
					cout << "Vysokoskolske: " << KVZPocet->evaluate(*item->accessData()) << "\n";
					delete KVZPocet;

					cout << "\n";
					KVZPocet = new KriteriumUJVzdelaniePocet(BEZVZDELANIA);
					cout << "Bez Vzdelania: " << KVZPocet->evaluate(*item->accessData()) << "\n";
					delete KVZPocet;

					cout << "\n";
					KVZPocet = new KriteriumUJVzdelaniePocet(NEZISTENE);
					cout << "Nezistene: " << KVZPocet->evaluate(*item->accessData()) << "\n";
					delete KVZPocet;

					//cout << "--------------------------------" << "\n";
					cout << "\n";
					cout << "\n";

				}
				if (vzpodiel == true) {

					KriteriumUJVzdelaniePodiel* KVZPodiel = new KriteriumUJVzdelaniePodiel(BEZUKONCENEHO);
					cout << "Podiel Bezukonceneho: " << KVZPodiel->evaluate(*item->accessData()) << "\n";
					delete KVZPodiel;
					cout << "\n";

					KVZPodiel = new KriteriumUJVzdelaniePodiel(ZAKLADNE);
					cout << "Podiel Zakladne: " << KVZPodiel->evaluate(*item->accessData()) << "\n";;
					delete KVZPodiel;
					cout << "\n";

					KVZPodiel = new KriteriumUJVzdelaniePodiel(UCNOVSKE);
					cout << "Podiel Ucnovske: " << KVZPodiel->evaluate(*item->accessData()) << "\n";
					delete KVZPodiel;
					cout << "\n";

					KVZPodiel = new KriteriumUJVzdelaniePodiel(STREDNE);
					cout << "Podiel Stredne: " << KVZPodiel->evaluate(*item->accessData()) << "\n";
					delete KVZPodiel;
					cout << "\n";

					KVZPodiel = new KriteriumUJVzdelaniePodiel(VYSSIE);
					cout << "Podiel Vyssie: " << KVZPodiel->evaluate(*item->accessData()) << "\n";
					delete KVZPodiel;
					cout << "\n";

					KVZPodiel = new KriteriumUJVzdelaniePodiel(VYSOKOSKOLSKE);
					cout << "Podiel Vysokoskolske: " << KVZPodiel->evaluate(*item->accessData()) << "\n";
					delete KVZPodiel;
					cout << "\n";

					KVZPodiel = new KriteriumUJVzdelaniePodiel(BEZVZDELANIA);
					cout << "Podiel Bezvzdelania: " << KVZPodiel->evaluate(*item->accessData()) << "\n";
					delete KVZPodiel;
					cout << "\n";

					KVZPodiel = new KriteriumUJVzdelaniePodiel(NEZISTENE);
					cout << "Podiel Nezistene: " << KVZPodiel->evaluate(*item->accessData()) << "\n";
					delete KVZPodiel;
					//cout << "--------------------------------" << "\n";
					cout << "\n";
					cout << "\n";

				}
				cout << "########################################################" << "\n";
			}
		}
		delete filtre;
	}

	structures::UnsortedSequenceTable<string, UzemnaJednotka*>* FiltrujDoTriedenia(structures::SequenceTable<std::string, UzemnaJednotka*>* vsetko, structures::SequenceTable<std::string, UzemnaJednotka*>* pomocna) {

		bool typ = false;
		bool pris = false;
		bool vzpocet = false;
		bool vzpodiel = false;
		bool vspocet = false;
		bool vspodiel = false;

		FilterAND<UzemnaJednotka>* filtre = new FilterAND<UzemnaJednotka>();


		structures::UnsortedSequenceTable<string, UzemnaJednotka*>* vyfiltrovane = new structures::UnsortedSequenceTable<string, UzemnaJednotka*>();


		int vyber = 0;
		while (vyber != 99) {
			system("cls");
			//filtrovanie
			cout << "Vyberte ktory filter chcete pouzit:" << "\n";
			//cout << "Filter Nazov" << "\n"
			cout << "Potvrd vyber__________________99" << "\n";
			cout << "\n";

			if (typ == true) {
				cout << "Filter Typ____________________1   <-" << "\n";
			}
			else {
				cout << "Filter Typ____________________1" << "\n";
			}

			if (pris == true) {
				cout << "Filter Prislusnost____________2   <-" << "\n";
			}
			else {
				cout << "Filter Prislusnost____________2" << "\n";
			}
			if (vzpocet == true) {
				cout << "Filter VzdelaniePocet_________3   <-" << "\n";
			}
			else {
				cout << "Filter VzdelaniePocet_________3" << "\n";
			}
			if (vzpodiel == true) {
				cout << "Filter VzdelaniePodiel________4   <-" << "\n";
			}
			else {
				cout << "Filter VzdelaniePodiel________4" << "\n";
			}
			if (vspocet == true) {
				cout << "Filter VekovaSkupinaPocet_____5   <-" << "\n";
			}
			else {
				cout << "Filter VekovaSkupinaPocet_____5" << "\n";
			}

			
			if (vspodiel == true) {
				cout << "Filter VekovaSkupinaPodiel____6   <-" << "\n";
			}
			else {
				cout << "Filter VekovaSkupinaPodiel____6" << "\n";
			}
			
			cin >> vyber;

			if (vyber == 1) {
				typ = true;
			}
			if (vyber == 2) {
				pris = true;
			}
			if (vyber == 3) {
				vzpocet = true;
			}
			if (vyber == 4) {
				vzpodiel = true;
			}
			if (vyber == 5) {
				vspocet = true;
			}

			if (vyber == 6) {
				vspodiel = true;
			}
		}


		int vybranie = 0;
		if (typ == true) {
			cout << "Filter Typ" << "\n";
			cout << "\n";

			cout << "Zadajte typ:" << "\n";
			cout << "KRAJ____1" << "\n";
			cout << "OKRES___2" << "\n";
			cout << "OBEC____3" << "\n";
			cin >> vybranie;
			UZEMNEJEDNOTKY vybranyTyp;
			switch (vybranie) {
			case 1:
				vybranyTyp = UZEMNEJEDNOTKY::KRAJ;
				break;
			case 2:
				vybranyTyp = UZEMNEJEDNOTKY::OKRES;
				break;
			case 3:
				vybranyTyp = UZEMNEJEDNOTKY::OBEC;
				break;
			}
			FilterUJTyp* fut = new FilterUJTyp(vybranyTyp);
			filtre->pridajFilter(fut);
		}
		system("cls");

		if (pris == true) {
			string hladana;
			cout << "Filter Prislusnost" << "\n";
			cout << "\n";
			cout << "Zadajte UzemnuJednotku: " << "\n";

			while (true) {
				if (hladana != "") {
					break;
				}
				getline(cin, hladana);
			}
			string kod = pomocna->find(hladana)->getKod();

			FilterUJPrislusnost* pris = new FilterUJPrislusnost(vsetko->find(kod));
			filtre->pridajFilter(pris);
		}

		system("cls");

		if (vzpocet == true) {
			int VZminimalnaPocet;
			int VZmaximalnaPocet;
			VZDELANIE_ENUM vzdelanieKtorePocet;
			cout << "Filter VzdelaniePocet: " << "\n";
			cout << "\n";
			cout << "Zadajte minimalnu hodnotu:" << "\n";
			cin >> VZminimalnaPocet;
			cout << "Zadajte maximalnu hodnotu:" << "\n";
			cin >> VZmaximalnaPocet;
			cout << "Zadajte typ vzdelania:" << "\n";
			cout << "Vyberte Vzdelanie:" << "\n";
			cout << "BEZUKONCENEHO____1" << "\n";
			cout << "ZAKLADNE_________2" << "\n";
			cout << "UCNOVSKE_________3" << "\n";
			cout << "STREDNE__________4" << "\n";
			cout << "VYSSIE___________5" << "\n";
			cout << "VYSOKOSKOLSKE____6" << "\n";
			cout << "BEZVZDELANIA_____7" << "\n";
			cout << "NEZISTENE________8" << "\n";
			int hodnota = 0;
			cin >> hodnota;
			switch (hodnota) {
			case 1:
				vzdelanieKtorePocet = BEZUKONCENEHO;
				break;
			case 2:
				vzdelanieKtorePocet = ZAKLADNE;
				break;
			case 3:
				vzdelanieKtorePocet = UCNOVSKE;
				break;
			case 4:
				vzdelanieKtorePocet = STREDNE;
				break;
			case 5:
				vzdelanieKtorePocet = VYSSIE;
				break;
			case 6:
				vzdelanieKtorePocet = VYSOKOSKOLSKE;
				break;
			case 7:
				vzdelanieKtorePocet = BEZVZDELANIA;
				break;
			case 8:
				vzdelanieKtorePocet = NEZISTENE;
				break;
			}

			FilterUJVzdelaniePocet* fvzPoc = new FilterUJVzdelaniePocet(vzdelanieKtorePocet, VZminimalnaPocet, VZmaximalnaPocet);
			filtre->pridajFilter(fvzPoc);

		}

		if (vzpodiel == true) {
			int VZMinimalnaPodiel;
			int VZMaximalnaPodiel;
			VZDELANIE_ENUM vzdelanieKtorePodiel;

			cout << "Filter VzdelaniePodiel" << "\n";
			cout << "Zadajte minimalnu hodnotu:" << "\n";
			cin >> VZMinimalnaPodiel;
			cout << "Zadajte maximalnu hodnotu:" << "\n";
			cin >> VZMaximalnaPodiel;
			cout << "Zadajte typ vzdelania:" << "\n";
			cout << "Vyberte Vzdelanie:" << "\n";
			cout << "BEZUKONCENEHO____1" << "\n";
			cout << "ZAKLADNE_________2" << "\n";
			cout << "UCNOVSKE_________3" << "\n";
			cout << "STREDNE__________4" << "\n";
			cout << "VYSSIE___________5" << "\n";
			cout << "VYSOKOSKOLSKE____6" << "\n";
			cout << "BEZVZDELANIA_____7" << "\n";
			cout << "NEZISTENE________8" << "\n";
			int hodnota = 0;
			cin >> hodnota;
			switch (hodnota) {
			case 1:
				vzdelanieKtorePodiel = BEZUKONCENEHO;
				break;
			case 2:
				vzdelanieKtorePodiel = ZAKLADNE;
				break;
			case 3:
				vzdelanieKtorePodiel = UCNOVSKE;
				break;
			case 4:
				vzdelanieKtorePodiel = STREDNE;
				break;
			case 5:
				vzdelanieKtorePodiel = VYSSIE;
				break;
			case 6:
				vzdelanieKtorePodiel = VYSOKOSKOLSKE;
				break;
			case 7:
				vzdelanieKtorePodiel = BEZVZDELANIA;
				break;
			case 8:
				vzdelanieKtorePodiel = NEZISTENE;
				break;
			}
			FilterUJVzdelaniePodiel* fvzPod = new FilterUJVzdelaniePodiel(vzdelanieKtorePodiel, VZMinimalnaPodiel, VZMaximalnaPodiel);
			filtre->pridajFilter(fvzPod);
		}

		if (vspocet == true) {
			int VSMinimalnaPocet;
			int VSMaximalnaPocet;
			EVS_ENUM vekKtorePocet;

			cout << "Filter VekovaSkupinaPocet" << "\n";
			cout << "Zadajte minimalnu hodnotu:" << "\n";
			cin >> VSMinimalnaPocet;
			cout << "Zadajte maximalnu hodnotu:" << "\n";
			cin >> VSMaximalnaPocet;
			cout << "Zadajte typ EVS:" << "\n";
			cout << "PREDPRODUKTIVNA_______1" << "\n";
			cout << "PRODUKTIVNA___________2" << "\n";
			cout << "POPRODUKTIVNA_________3" << "\n";
			int hodnota = 0;
			cin >> hodnota;
			switch (hodnota) {
			case 1:
				vekKtorePocet = PREDPRODUKTIVNI;
				break;
			case 2:
				vekKtorePocet = PRODUKTIVNI;
				break;
			case 3:
				vekKtorePocet = POPRODUKTIVNI;
				break;
			}

			FilterUJVekovaSkupinaPocet* VsPocet = new FilterUJVekovaSkupinaPocet(vekKtorePocet, VSMinimalnaPocet, VSMaximalnaPocet);
			filtre->pridajFilter(VsPocet);
		}
		
		if (vspodiel == true) {
			int VSMinimalnaPodiel;
			int VSMaximalnaPodiel;
			EVS_ENUM vekKtorePodiel;

			cout << "Filter VekovaSkupinaPodiel" << "\n";
			cout << "Zadajte minimalnu hodnotu:" << "\n";
			cin >> VSMinimalnaPodiel;
			cout << "Zadajte maximalnu hodnotu:" << "\n";
			cin >> VSMaximalnaPodiel;
			cout << "Zadajte typ EVS:" << "\n";
			cout << "PREDPRODUKTIVNA_______1" << "\n";
			cout << "PRODUKTIVNA___________2" << "\n";
			cout << "POPRODUKTIVNA_________3" << "\n";
			int hodnota = 0;
			cin >> hodnota;
			switch (hodnota) {
			case 1:
				vekKtorePodiel = PREDPRODUKTIVNI;
				break;
			case 2:
				vekKtorePodiel = PRODUKTIVNI;
				break;
			case 3:
				vekKtorePodiel = POPRODUKTIVNI;
				break;
			}
			FilterUJVekovaSkupinaPodiel* VsPodiel = new FilterUJVekovaSkupinaPodiel(vekKtorePodiel, VSMinimalnaPodiel, VSMaximalnaPodiel);
			filtre->pridajFilter(VsPodiel);
		}
		

		//finalny vypis
		system("cls");
		for (structures::TableItem<std::string, UzemnaJednotka*>* item : *vsetko) {
			if (filtre->pass(*item->accessData())) {
				vyfiltrovane->insert(item->getKey(), item->accessData());
			}
		}
		delete filtre;
		return vyfiltrovane;
	}



};