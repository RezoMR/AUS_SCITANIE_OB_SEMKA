
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

		KriteriumUJVekovaSkupinaPodiel* KVekPodiel = nullptr;
		KriteriumUJVekovaSkupinaPocet* KVekPocet = nullptr;
		KriteriumUJVzdelaniePodiel* KVZPodiel = nullptr;
		KriteriumUJVzdelaniePocet* KVZPocet = nullptr;
		KriteriumUJNazov* KNazov = new KriteriumUJNazov();




		CSVCitac* n = new CSVCitac();
		structures::SortedSequenceTable<string, UzemnaJednotka*>* kraje = n->nacitajKraje();
	    structures::SortedSequenceTable<string, UzemnaJednotka*>* obce = n->nacitajObce();
		structures::SortedSequenceTable<string, UzemnaJednotka*>* okresy = n->nacitajOkresy();


		EVS_ENUM vekKtorePocet;

		//pomocne na riešenie duplicít
		//k¾úè je názov   
		structures::SortedSequenceTable<string, structures::LinkedList<UzemnaJednotka*>*>* duplicity = new structures::SortedSequenceTable<string, structures::LinkedList<UzemnaJednotka*>*>();
		//kluc je nazov
		structures::SortedSequenceTable<string,UzemnaJednotka*>* pomocnaBodoveVyh = new structures::SortedSequenceTable<string, UzemnaJednotka*>();
				

		structures::SortedSequenceTable<std::string, VzdelanieUJ*>* vzdelanie = n->nacitajVzdelanie();
		structures::SortedSequenceTable<std::string, VekUJ*>* veky = n->nacitajVek();

		UzemnaJednotka* Slovensko = new UzemnaJednotka("Slovensko");

		int size;
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
			item->accessData()->setKod(item->getKey());
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
			kraj->accessData()->setKod(kraj->getKey());
			string kod = kraj->getKey().substr(7, 8);
			for (structures::TableItem<std::string, UzemnaJednotka*>* okres : *okresy) {
				okres->accessData()->setKod(okres->getKey());
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

		for (structures::TableItem<std::string, UzemnaJednotka*>* okres : *okresy) {
			string zadany = "";
			zadany = okres->accessData()->getNazov();
			pomocnaBodoveVyh->insert(zadany, okres->accessData());
		}

		for (structures::TableItem<std::string, UzemnaJednotka*>* kraj : *kraje) {
			string zadany = "";
			zadany = kraj->accessData()->getNazov();
			pomocnaBodoveVyh->insert(zadany, kraj->accessData());
		}
		//system("pause");
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
		int hodnta;
		int hodnot = 0;
		int hodnota = 0;
		VZDELANIE_ENUM vzdelanieKtorePocet;
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
				//UzemnaJednotka* u = pomocnaBodoveVyh->find(hladana);
				//cout << kod << "\n";
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
			cout << "VekSkupinaPodiel___________5" << "\n";

			int vybranie = 0;
			cin >> vybranie;
			switch (vybranie) {


			//triedenie podla nazvu
			case 1:
				size = tr->size();

				t->sort(*tr, vybranySposob, *KNazov, 0, tr->size() - 1);

				for (auto item : *tr) {

					cout << item->accessData()->getNazov() << "\n";
					cout << "________________________________________" << "\n";
				}

				break;


			//triedenie podla pocet vekova skupina
			case 2:
				cout << "Vyberte podla ktorej vekovej skupiny: " << "\n";
				cout << "PREDPRODUKTIVNY___1:" << "\n";
				cout << "PRODUKTIVNY_______2:" << "\n";
				cout << "POPRODUKTIVNY_____3:" << "\n";
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
				 KVekPocet = new KriteriumUJVekovaSkupinaPocet(vekKtorePocet);
			     t->sort(*tr, vybranySposob, *KVekPocet, 0, tr->size()-1);

				 for (auto item : *tr) {
					KriteriumUJNazov* KNazov = new KriteriumUJNazov();
					 cout << "Nazov: " << KNazov->evaluate(*item->accessData()) << "\n";
					 delete KNazov;
					 KriteriumUJVekovaSkupinaPocet* KVSpocet = new KriteriumUJVekovaSkupinaPocet(PREDPRODUKTIVNI);
					 cout << "Predproduktivny: " << KVSpocet->evaluate(*item->accessData()) << "\n";
					 delete KVSpocet;
					 KVSpocet = new KriteriumUJVekovaSkupinaPocet(PRODUKTIVNI);
					 cout << "Produktivny: " << KVSpocet->evaluate(*item->accessData()) << "\n";
					 delete KVSpocet;
					 KVSpocet = new KriteriumUJVekovaSkupinaPocet(POPRODUKTIVNI);
					 cout << "Poproduktivny: " << KVSpocet->evaluate(*item->accessData()) << "\n";
					 delete KVSpocet;
					 cout << "##################################################" << "\n";
				 }

				break;


			//triedenie vzdelanie pocet
			case 3:
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
				cin >> hodnot;
				switch (hodnot) {
				case 1:
					vzdelanieKtorePocet = BEZUKONCENEHO;
					KVZPocet = new KriteriumUJVzdelaniePocet(vzdelanieKtorePocet);
					break;
				case 2:
					vzdelanieKtorePocet = ZAKLADNE;
					KVZPocet = new KriteriumUJVzdelaniePocet(vzdelanieKtorePocet);
					break;
				case 3:
					vzdelanieKtorePocet = UCNOVSKE;
					KVZPocet = new KriteriumUJVzdelaniePocet(vzdelanieKtorePocet);
					break;
				case 4:
					vzdelanieKtorePocet = STREDNE;
					KVZPocet = new KriteriumUJVzdelaniePocet(vzdelanieKtorePocet);
					break;
				case 5:
					vzdelanieKtorePocet = VYSSIE;
					KVZPocet = new KriteriumUJVzdelaniePocet(vzdelanieKtorePocet);
					break;
				case 6:
					vzdelanieKtorePocet = VYSOKOSKOLSKE;
					KVZPocet = new KriteriumUJVzdelaniePocet(vzdelanieKtorePocet);
					break;
				case 7:
					vzdelanieKtorePocet = BEZVZDELANIA;
					KVZPocet = new KriteriumUJVzdelaniePocet(vzdelanieKtorePocet);
					break;
				case 8:
					vzdelanieKtorePocet = NEZISTENE;
					KVZPocet = new KriteriumUJVzdelaniePocet(vzdelanieKtorePocet);
					break;
				}

				if (KVZPocet) {
					t->sort(*tr, true, *KVZPocet, 0, tr->size()-1);
				}

				for (auto item : *tr) {

					cout << item->accessData()->getNazov() << "\n";
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
					cout << "##################################################" << "\n";
				}
				break;


				//triedenie podla vzdelanie podiel
			case 4:
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
				
				cin >> hodnta;
				switch (hodnta) {
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
				KVZPodiel = new KriteriumUJVzdelaniePodiel(vzdelanieKtorePocet);
				t->sort(*tr, vyber, *KVZPodiel, 0, tr->size()-1);

				for (auto item : *tr) {

					cout << item->accessData()->getNazov() << "\n";
					KriteriumUJVzdelaniePodiel* KVZPocet = new KriteriumUJVzdelaniePodiel(BEZUKONCENEHO);
					cout << "Bezukonceneho: " << KVZPocet->evaluate(*item->accessData()) << "\n";
					delete KVZPocet;
					cout << "\n";
					KVZPocet = new KriteriumUJVzdelaniePodiel(ZAKLADNE);
					cout << "Zakladne: " << KVZPocet->evaluate(*item->accessData()) << "\n";
					delete KVZPocet;

					cout << "\n";
					KVZPocet = new KriteriumUJVzdelaniePodiel(UCNOVSKE);
					cout << "Ucnovske: " << KVZPocet->evaluate(*item->accessData()) << "\n";
					delete KVZPocet;

					cout << "\n";
					KVZPocet = new KriteriumUJVzdelaniePodiel(STREDNE);
					cout << "Stredne: " << KVZPocet->evaluate(*item->accessData()) << "\n";
					delete KVZPocet;

					cout << "\n";
					KVZPocet = new KriteriumUJVzdelaniePodiel(VYSSIE);
					cout << "Vyssie: " << KVZPocet->evaluate(*item->accessData()) << "\n";
					delete KVZPocet;

					cout << "\n";
					KVZPocet = new KriteriumUJVzdelaniePodiel(VYSOKOSKOLSKE);
					cout << "Vysokoskolske: " << KVZPocet->evaluate(*item->accessData()) << "\n";
					delete KVZPocet;

					cout << "\n";
					KVZPocet = new KriteriumUJVzdelaniePodiel(BEZVZDELANIA);
					cout << "Bez Vzdelania: " << KVZPocet->evaluate(*item->accessData()) << "\n";
					delete KVZPocet;

					cout << "\n";
					KVZPocet = new KriteriumUJVzdelaniePodiel(NEZISTENE);
					cout << "Nezistene: " << KVZPocet->evaluate(*item->accessData()) << "\n";
					delete KVZPocet;
					cout << "##################################################" << "\n";
				}


				break;

				//triedenie podla vekova skupina podiel
			case 5:
				//vekova skupina podiel
				cout << "Vyberte podla ktorej vekovej skupiny: " << "\n";
				cout << "PREDPRODUKTIVNY___1:" << "\n";
				cout << "PRODUKTIVNY_______2:" << "\n";
				cout << "POPRODUKTIVNY_____3:" << "\n";
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
				KVekPodiel = new KriteriumUJVekovaSkupinaPodiel(vekKtorePocet);
				t->sort(*tr, vyber, *KVekPodiel, 0, tr->size()-1);

				for (auto item : *tr) {
					KriteriumUJNazov* KNazov = new KriteriumUJNazov();
					cout << "Nazov: " << KNazov->evaluate(*item->accessData()) << "\n";
					delete KNazov;
					KriteriumUJVekovaSkupinaPodiel* KVSpocet = new KriteriumUJVekovaSkupinaPodiel(PREDPRODUKTIVNI);
					cout << "Predproduktivny: " << KVSpocet->evaluate(*item->accessData()) << "\n";
					delete KVSpocet;
					KVSpocet = new KriteriumUJVekovaSkupinaPodiel(PRODUKTIVNI);
					cout << "Produktivny: " << KVSpocet->evaluate(*item->accessData()) << "\n";
					delete KVSpocet;
					KVSpocet = new KriteriumUJVekovaSkupinaPodiel(POPRODUKTIVNI);
					cout << "Poproduktivny: " << KVSpocet->evaluate(*item->accessData()) << "\n";
					delete KVSpocet;
					cout << "##################################################" << "\n";
				}
				break;


			}
			
			delete tr;
			break;
		}




		delete KVekPodiel;
		delete KVekPocet;
		delete KVZPodiel;
		delete KNazov;
		delete KVZPocet;
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
