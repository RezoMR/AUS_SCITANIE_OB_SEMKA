
#pragma once
#include "../structures/table/unsorted_sequence_table.h"
#include "Kriterium.h"


using namespace std;
class Triedenie {

private:

	bool PodlaNazvu = false;

	bool VzdelaniePocet = false;
	bool VzdelaniePodiel = false;

	bool VekSkupinaPocet = false;

	bool Vzostupne = false;
	bool Zostupne;

	VZDELANIE_ENUM typVzdelania;
	EVS_ENUM typEVS;



public:

	void tried(structures::SequenceTable<std::string, UzemnaJednotka*>* vsetko, structures::SequenceTable<std::string, UzemnaJednotka*>* pomocna) {

		bool typ = false;
		bool pris = false;
		bool vzpocet = false;
		bool vzpodiel = false;
		bool vspocet = false;
		//bool vspodiel = false;

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

			/*
			if (vspodiel == true) {
				cout << "Filter VekovaSkupinaPodiel____6   <-" << "\n";
			}
			else {
				cout << "Filter VekovaSkupinaPodiel____6" << "\n";
			}
			*/
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

			/*if (vyber == 6) {
				vspodiel = true;
			}*/
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
				typVzdelania = BEZUKONCENEHO;
				break;
			case 2:
				typVzdelania = ZAKLADNE;
				break;
			case 3:
				typVzdelania = UCNOVSKE;
				break;
			case 4:
				typVzdelania = STREDNE;
				break;
			case 5:
				typVzdelania = VYSSIE;
				break;
			case 6:
				typVzdelania = VYSOKOSKOLSKE;
				break;
			case 7:
				typVzdelania = BEZVZDELANIA;
				break;
			case 8:
				typVzdelania = NEZISTENE;
				break;
			}
			FilterUJVzdelaniePodiel* fvzPod = new FilterUJVzdelaniePodiel(typVzdelania, VZMinimalnaPodiel, VZMaximalnaPodiel);
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

		//finalny vypis
		system("cls");
		for (structures::TableItem<std::string, UzemnaJednotka*>* item : *vsetko) {
			if (filtre->pass(*item->accessData())) {
				vyfiltrovane->insert(item->getKey(), item->accessData());
			}
		}
		if (vyfiltrovane->size() != 0) {
			cout << "Vyberte podla coho chcete triedit: " << "\n";

			cout << "Nazov" << "\n";
			if (vzpocet == true) {
				cout << "Vzdelaniepocet" << "\n";
			}
			if (vzpodiel == true) {
				cout << "VzdelaniePodiel" << "\n";
			}
			if (vspocet == true) {
				cout << "VekovaSkupinaPocet" << "\n";
			}
			string vybraneTriedenie = "";
			cin >> vybraneTriedenie;

			int ako;
			cout << "Zostupne_____1" << "\n";
			cout << "Vzostupne____2" << "\n";

			cin >> ako;
			bool vzostupne = false;
			if (ako = 2) {
				vzostupne = true;
			}


			system("cls");

			if (vybraneTriedenie == "Nazov") {

			}
			if (vybraneTriedenie == "Vzdelaniepocet") {
				cout << "Vyber Vzdelanie:" << "\n";
				cout << "BEZUKONCENEHO:" << "\n";
				cout << "ZAKLADNE:" << "\n";
				cout << "UCNOVSKE:" << "\n";
				cout << "VYSSIE:" << "\n";
				cout << "VYSOKOSKOLSKE:" << "\n";
				cout << "BEZVZDELANIA" << "\n";
				cout << "NEZISTENE:" << "\n";





			}
			if (vybraneTriedenie == "VzdelaniePodiel") {

			}
			if (vybraneTriedenie == "VekovaSkupinaPocet") {

			}
		}
		else {
			cout << "Neboli vyfiltrovane ziadne uj" << "\n";
		}




		delete filtre;

	}


	void sortHelper(structures::UnsortedSequenceTable<std::string, UzemnaJednotka*>& table, int min, int max, bool paVzostupne, bool paPodlaNazvu, bool paVzdelaniePocet, bool paVzdelaniePodiel, bool paVekSkupinaPocet, VZDELANIE_ENUM patypVzdelania, EVS_ENUM patypEVS) {


		if (PodlaNazvu)
		{
			std::string pivot = table.getItemAtIndex((min + max) / 2).accessData()->getNazov();

			int lavy = min;
			int pravy = max;

			do
			{
				if (paVzostupne)
				{
					while (table.getItemAtIndex(lavy).accessData()->getNazov() < pivot)
					{
						lavy++;
					}
					while (table.getItemAtIndex(pravy).accessData()->getNazov() > pivot)
					{
						pravy--;
					}
				}
				else { //ak nie je bool paVzostupne true tak -> zostupne
					while (table.getItemAtIndex(lavy).accessData()->getNazov() > pivot)
					{
						lavy++;
					}
					while (table.getItemAtIndex(pravy).accessData()->getNazov() < pivot)
					{
						pravy--;
					}
				}

				if (lavy <= pravy)
				{
					table.swap(lavy, pravy);
					lavy++;
					pravy--;
				}
			} while (lavy <= pravy);

			if (min < pravy)
			{
				sortHelper(table, min, pravy, paVzostupne, paPodlaNazvu, paVzdelaniePocet, paVzdelaniePodiel, paVekSkupinaPocet, patypVzdelania, patypEVS);
			}
			if (lavy < max)
			{
				sortHelper(table, lavy, max, paVzostupne, PodlaNazvu, paVzdelaniePocet, paVzdelaniePodiel, paVekSkupinaPocet, patypVzdelania, typEVS);
			}
		}


		if (VzdelaniePocet)
		{
			int hlavnyKluc = table.getItemAtIndex((min + max) / 2).accessData()->vratVzdelanie()->vratPocet(typVzdelania);

			int lavy = min;
			int pravy = max;


			do
			{
				if (paVzostupne)
				{
					while (table.getItemAtIndex(lavy).accessData()->vratVzdelanie()->vratPocet(typVzdelania) < hlavnyKluc)
					{
						lavy++;
					}
					while (table.getItemAtIndex(pravy).accessData()->vratVzdelanie()->vratPocet(typVzdelania) > hlavnyKluc)
					{
						pravy--;
					}
				}
				else { // zostupne
					while (table.getItemAtIndex(lavy).accessData()->vratVzdelanie()->vratPocet(typVzdelania) > hlavnyKluc)
					{
						lavy++;
					}
					while (table.getItemAtIndex(pravy).accessData()->vratVzdelanie()->vratPocet(typVzdelania) < hlavnyKluc)
					{
						pravy--;
					}
				}

				if (lavy <= pravy)
				{
					table.swap(lavy, pravy);
					lavy++;
					pravy--;
				}
			} while (lavy <= pravy);

			if (min < pravy)
			{
				sortHelper(table, min, pravy, paVzostupne, PodlaNazvu, paVzdelaniePocet, paVzdelaniePodiel, paVekSkupinaPocet, patypVzdelania, typEVS);
			}
			if (lavy < max)
			{
				sortHelper(table, lavy, max, paVzostupne, PodlaNazvu, paVzdelaniePocet, paVzdelaniePodiel, paVekSkupinaPocet, patypVzdelania, typEVS);
			}
		}



		if (VzdelaniePodiel)
		{
			double prve = table.getItemAtIndex((min + max) / 2).accessData()->vratPocetVzdelanie(typVzdelania);
			double druhe = table.getItemAtIndex((min + max) / 2).accessData()->vratPocetLudi();
			double pivot = (prve / druhe);


			double lavy = min;
			double pravy = max;

			do
			{
				if (paVzostupne)
				{
					while (table.getItemAtIndex(lavy).accessData()->vratPocetVzdelanie(typVzdelania) < pivot)
					{
						lavy++;
					}
					while (table.getItemAtIndex(pravy).accessData()->vratPocetVzdelanie(typVzdelania) > pivot)
					{
						pravy--;
					}
				}
				else { // zostupne
					while (table.getItemAtIndex(lavy).accessData()->vratPocetVzdelanie(typVzdelania) > pivot)
					{
						lavy++;
					}
					while (table.getItemAtIndex(pravy).accessData()->vratPocetVzdelanie(typVzdelania) < pivot)
					{
						pravy--;
					}
				}

				if (lavy <= pravy)
				{
					table.swap(lavy, pravy);
					lavy++;
					pravy--;
				}
			} while (lavy <= pravy);

			if (min < pravy)
			{
				sortHelper(table, min, pravy, paVzostupne, PodlaNazvu, paVzdelaniePocet, paVzdelaniePodiel, paVekSkupinaPocet, patypVzdelania, typEVS);
			}
			if (lavy < max)
			{
				sortHelper(table, lavy, max, paVzostupne, PodlaNazvu, paVzdelaniePocet, paVzdelaniePodiel, paVekSkupinaPocet, patypVzdelania, typEVS);
			}
		}


		if (paVekSkupinaPocet)
		{
			int hlavnyKluc = table.getItemAtIndex((min + max) / 2).accessData()->getVekObyvatelov()->getPocetEkoVekSkupinuCelkovo(typEVS);

			int lavy = min;
			int pravy = max;


			do
			{
				if (vzostupne)
				{
					while (table.getItemAtIndex(lavy).accessData()->getVekObyvatelov()->getPocetEkoVekSkupinuCelkovo(typEvs) < hlavnyKluc)
					{
						lavy++;
					}
					while (table.getItemAtIndex(pravy).accessData()->getVekObyvatelov()->getPocetEkoVekSkupinuCelkovo(typEvs) > hlavnyKluc)
					{
						pravy--;
					}
				}
				else { // zostupne
					while (table.getItemAtIndex(lavy).accessData()->getVekObyvatelov()->getPocetEkoVekSkupinuCelkovo(typEvs) > hlavnyKluc)
					{
						lavy++;
					}
					while (table.getItemAtIndex(pravy).accessData()->getVekObyvatelov()->getPocetEkoVekSkupinuCelkovo(typEvs) < hlavnyKluc)
					{
						pravy--;
					}
				}

				if (lavy <= pravy)
				{
					table.swap(lavy, pravy);
					lavy++;
					pravy--;
				}
			} while (lavy <= pravy);

			if (min < pravy)
			{
				sortHelper(table, min, pravy, vzostupne, triedPodlaNazvu, triedPodlaVzdelaniePocet, triedPodlaVzdelaniePodiel, triedPodlaVekSkupinaPocet, triedPodlaVekSkupinaPodiel, typVzd, typEvs);
			}
			if (lavy < max)
			{
				sortHelper(table, lavy, max, vzostupne, triedPodlaNazvu, triedPodlaVzdelaniePocet, triedPodlaVzdelaniePodiel, triedPodlaVekSkupinaPocet, triedPodlaVekSkupinaPodiel, typVzd, typEvs);
			}
		}



		if (triedPodlaVekSkupinaPodiel)
		{
			double hlavnyKluc = table.getItemAtIndex((min + max) / 2).accessData()->getVekObyvatelov()->getPodielEvs(typEvs);

			double lavy = min;
			double pravy = max;

			do
			{
				if (vzostupne)
				{
					while (table.getItemAtIndex(lavy).accessData()->getVekObyvatelov()->getPodielEvs(typEvs) < hlavnyKluc)
					{
						lavy++;
					}
					while (table.getItemAtIndex(pravy).accessData()->getVekObyvatelov()->getPodielEvs(typEvs) > hlavnyKluc)
					{
						pravy--;
					}
				}
				else { // zostupne
					while (table.getItemAtIndex(lavy).accessData()->getVekObyvatelov()->getPodielEvs(typEvs) > hlavnyKluc)
					{
						lavy++;
					}
					while (table.getItemAtIndex(pravy).accessData()->getVekObyvatelov()->getPodielEvs(typEvs) < hlavnyKluc)
					{
						pravy--;
					}
				}

				if (lavy <= pravy)
				{
					table.swap(lavy, pravy);
					lavy++;
					pravy--;
				}
			} while (lavy <= pravy);

			if (min < pravy)
			{
				sortHelper(table, min, pravy, vzostupne, triedPodlaNazvu, triedPodlaVzdelaniePocet, triedPodlaVzdelaniePodiel, triedPodlaVekSkupinaPocet, triedPodlaVekSkupinaPodiel, typVzd, typEvs);
			}
			if (lavy < max)
			{
				sortHelper(table, lavy, max, vzostupne, triedPodlaNazvu, triedPodlaVzdelaniePocet, triedPodlaVzdelaniePodiel, triedPodlaVekSkupinaPocet, triedPodlaVekSkupinaPodiel, typVzd, typEvs);
			}
		}
	}


};