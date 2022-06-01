
#pragma once
#include "CSVCitac.h"
#include "UzemnaJednotka.h"
#include "UZEMNEJEDNOTKY.h"
#include "VekUJ.h"
#include "bodoveVyhladavanie.h"
#include "Filtrovanie.h"
#include "Triedenie.h"

using namespace std;
class Priradovanie {


public:
	void prirad()
	{
		cout << "nacitavanie udajov" << "\n";
		CSVCitac* n = new CSVCitac();
		structures::SortedSequenceTable<string, UzemnaJednotka*>* kraje = n->nacitajKraje();
	    structures::SortedSequenceTable<string, UzemnaJednotka*>* obce = n->nacitajObce();
		structures::SortedSequenceTable<string, UzemnaJednotka*>* okresy = n->nacitajOkresy();


		//pomocne na riešenie duplicít
		//k¾úè je názov   
		structures::SortedSequenceTable<string, structures::LinkedList<UzemnaJednotka*>*>* duplicity = new structures::SortedSequenceTable<string, structures::LinkedList<UzemnaJednotka*>*>();
		//kluc je nazov
		structures::SortedSequenceTable<string,UzemnaJednotka*>* pomocnaBodoveVyh = new structures::SortedSequenceTable<string, UzemnaJednotka*>();
				

		structures::SortedSequenceTable<std::string, VzdelanieUJ*>* vzdelanie = n->nacitajVzdelanie();
		structures::SortedSequenceTable<std::string, VekUJ*>* veky = n->nacitajVek();

		UzemnaJednotka* Slovensko = new UzemnaJednotka("Slovensko");

		for (structures::TableItem<std::string, UzemnaJednotka*>* okres : *okresy) {
			pomocnaBodoveVyh->insert(okres->accessData()->getNazov(), okres->accessData());

		}
		for (structures::TableItem<std::string, UzemnaJednotka*>* kraj : *kraje) {
			pomocnaBodoveVyh->insert(kraj->accessData()->getNazov(), kraj->accessData());

		}


		Triedenie* t = new Triedenie();
		Filtrovanie* f = new Filtrovanie();
		bodoveVyhladavanie* bodVyh = new bodoveVyhladavanie();

		cout << "koniec nacitavanie udajov" << "\n";
		system("cls");
		cout << "hladanie duplicit" << "\n";

		for (structures::TableItem<std::string, UzemnaJednotka*>* item : *obce) {
			item->accessData()->setKod(item->getKey());
			if (pomocnaBodoveVyh->containsKey(item->accessData()->getNazov())) {
				if (duplicity->containsKey(item->accessData()->getNazov())) {
					duplicity->find(item->accessData()->getNazov())->add(item->accessData());
				}
				else {
					structures::LinkedList<UzemnaJednotka*>* x = new structures::LinkedList<UzemnaJednotka*>();
					x->add(item->accessData());
					x->add(pomocnaBodoveVyh->find(item->accessData()->getNazov()));
					duplicity->insert(item->accessData()->getNazov(), x);
				}

			}
			else {
				pomocnaBodoveVyh->insert(item->accessData()->getNazov(),item->accessData());
			}
		}
		cout << "koniec hladania duplicit" << "\n";


		system("cls");
		cout << "zaciatok priradovania veku a vzdelania obciam" << "\n";
		int i = 0;
		for (structures::TableItem<std::string, UzemnaJednotka*>* item : *obce) {
			if (veky->containsKey(item->getKey())) {
				item->accessData()->setVek(veky->find(item->getKey()));
			}
			if (vzdelanie->containsKey(item->getKey())) {
				item->accessData()->setVzdelanie(vzdelanie->find(item->getKey()));
			}
			i++;
			item->accessData()->setTyp(UZEMNEJEDNOTKY::OBEC);
		}
		cout << "dokoncene priradovanie veku a vzdelania obciam" << "\n";
		system("cls");


		cout << "zaciatok prepajania a priradovania obci okresom" << "\n";

		for (structures::TableItem<std::string, UzemnaJednotka*>* obec : *obce) {
			string kod = obec->getKey().substr(0, 6);

			obec->accessData()->setVyssia(okresy->find(kod));
			okresy->find(kod)->setNizsie(obec->accessData());
			okresy->find(kod)->pripocitajVeky(obec->accessData()->vratVek());
			okresy->find(kod)->pripocitajVzdelania(obec->accessData()->vratVzdelanie());

		}
		cout << "koniec prepajania a priradovania priradovania obci okresom" << "\n";
		system("cls");

		cout << "zaciatok prepajania a priradovania okresov krajom" << "\n";
		for (structures::TableItem<std::string, UzemnaJednotka*>* kraj : *kraje) {
			string kod = kraj->getKey().substr(7, 8);
			for (structures::TableItem<std::string, UzemnaJednotka*>* okres : *okresy) {
				string kodOkres = okres->getKey().substr(2, 3);
				int vys = kodOkres.compare(kod);
				if (vys == 0) {
					okres->accessData()->setVyssia(kraje->find(kraj->getKey()));
					kraj->accessData()->pripocitajVeky(okres->accessData()->vratVek());
					kraj->accessData()->pripocitajVzdelania(okres->accessData()->vratVzdelanie());
					okres->accessData()->setTyp(UZEMNEJEDNOTKY::OKRES);
				}

			}
			Slovensko->pripocitajVeky(kraj->accessData()->vratVek());
			Slovensko->pripocitajVzdelania(kraj->accessData()->vratVzdelanie());
			Slovensko->setVyssia(nullptr);
			Slovensko->setKod("SK");
			kraj->accessData()->setTyp(UZEMNEJEDNOTKY::KRAJ);
		}

		cout << "koniec prepajania a priradovania okresov krajom" << "\n";
		cout << "kompletizovanie" << "\n";

		structures::SortedSequenceTable<std::string, UzemnaJednotka*>* vsetko = new structures::SortedSequenceTable<std::string, UzemnaJednotka*>;
		vsetko->insert(Slovensko->getKod(), Slovensko);
		for (structures::TableItem<std::string, UzemnaJednotka*>* obec : *obce) {
			vsetko->insert(obec->getKey(), obec->accessData());
		}
		for (structures::TableItem<std::string, UzemnaJednotka*>* okres : *okresy) {
			vsetko->insert(okres->getKey(), okres->accessData());
		}
		for (structures::TableItem<std::string, UzemnaJednotka*>* kraj : *kraje) {
			vsetko->insert(kraj->getKey(), kraj->accessData());
		}

		cout << "koniec kompletizacie" << "\n";

		system("cls");
		
		
		cout << "Vyberte co chcete vykonat: (zadajte cislo)" << "\n";
		cout << "Bodove vyhladavanie_________1" << "\n";
		cout << "Filtrovanie_________________2" << "\n";
		cout << "Triedenie___________________3" << "\n";
		cout << "Koniec______________________9" << "\n";
		int vyber;
		cin >> vyber;
		string hladana = "";
		int dupl;
		UzemnaJednotka uj;
		switch (vyber) {
		case 1:
			cout << "Zadajte nazov uzemnej jednotky: " << "\n";
			while (true) {
				if (hladana != "") {
					break;
				}
				getline(cin, hladana);
			}

			if (duplicity->containsKey(hladana)) {
				for (int i = 0; i < duplicity->find(hladana)->size(); i++)
				{
					cout << hladana << " " << duplicity->find(hladana)->at(i)->getVyssiaNazov() << "   " << i << "\n";
				}
				cout << "zadajte cislo uzemnej jednotky, ktoru chcete vybrat:" << "\n";
				cin >> dupl;
				string selectnuty = duplicity->find(hladana)->at(dupl)->getKod();

				switch (vsetko->find(selectnuty)->getTyp()) {
				case OBEC:
					bodVyh->vyhladajObec(vsetko->find(selectnuty));
					break;
				case OKRES:
					bodVyh->vyhladajOkres(vsetko->find(selectnuty));
					break;
				case KRAJ:
					bodVyh->vyhladajKraj(vsetko->find(selectnuty));
					break;
				}
			}
			else {
				string kod = pomocnaBodoveVyh->find(hladana)->getKod();

				switch (vsetko->find(kod)->getTyp()) {
				case OBEC:
					bodVyh->vyhladajObec(vsetko->find(kod));
					break;
				case OKRES:
					bodVyh->vyhladajOkres(vsetko->find(kod));
					break;
				case KRAJ:
					bodVyh->vyhladajKraj(vsetko->find(kod));
					break;
				}
			}
			break;
		case 2:
			//filtrovanie
				f->Filtruj(vsetko, pomocnaBodoveVyh);
			break;
		case 3:
			//triedenie
			cout << "Zacinam triedenie: " << "\n";
			structures::UnsortedSequenceTable<std::string, UzemnaJednotka*>* tr = f->FiltrujDoTriedenia(vsetko, pomocnaBodoveVyh);
			cout << "Vyberte ako chcete zoradit: " << "\n";
			cout << "Zostupne_____1 " << "\n";
			cout << "Vzostupne____2 " << "\n";
			bool vybranySposob = false;
			int ako;
			cin >> ako;
			if (ako == 2) {
				vybranySposob = true;
			}
			cout << "Vyberte, podla coho chcete triedit: " << "\n";
			cout << "Podla vybraných filtrov: " << "\n";
			cout << "Nazov______________1" << "\n";
			cout << "VekSkupinaPocet___________2" << "\n";
			cout << "VzdelaniePocet_____3" << "\n";
			cout << "VzdelaniePodiel____4 " << "\n";

			int vybranie = 0;
			cin >> vybranie;
			switch (vybranie) {
			case 1:
				t->sort(tr, vyber, KriteriumUJNazov(), 0, tr->size());
				break;
			case 2:
				EVS_ENUM vekKtorePocet;
				cout << "Vyberte podla ktorej vekovej skupiny: " << "\n";
				cout << "PREDPRODUKTIVNY___1:" << "\n";
				cout << "PRODUKTIVNY_______2:" << "\n";
				cout << "POPRODUKTIVNY_____3:" << "\n";

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
				t->sort(tr, vyber, KriteriumUJVekovaSkupinaPocet(vekKtorePocet), 0, tr->size())
				break;

			case 3:
				VZDELANIE_ENUM vzdelanieKtorePocet;
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

				t->sort(tr, vyber, KriteriumUJVzdelaniePocet(vzdelanieKtorePocet), 0, tr->size());
				break;
			case 4:
				VZDELANIE_ENUM vzdelanieKtorePocet;
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

				t->sort(tr, vyber, KriteriumUJVzdelaniePodiel(vzdelanieKtorePocet), 0, tr->size());
				break;
			}
			
			delete tr;
			break;
		}

		delete t;
		delete f;
		delete bodVyh;
		delete pomocnaBodoveVyh;
		delete Slovensko;
		delete vsetko;
		for (auto item : *kraje) {
			if (item->accessData() != nullptr) {
				delete item->accessData();
			}
		}
		delete kraje;
		for (auto item : *obce) {
			if (item->accessData() != nullptr) {
				delete item->accessData();
			}
		}
		delete obce;
		for (auto item : *okresy) {
			if (item->accessData() != nullptr) {
				delete item->accessData();
			}
		}
		delete okresy;
		delete n;

		for (auto item : *duplicity) {
			delete item->accessData();
		}
		delete duplicity;

		
		delete veky;

		
		delete vzdelanie;



		//cout << "koniec";
	}
	
};
