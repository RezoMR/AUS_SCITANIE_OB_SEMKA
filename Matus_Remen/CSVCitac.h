#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <array>
#include "../structures/list/array_list.h"
#include "../structures/list/linked_list.h"
#include "../structures/table/sorted_sequence_table.h"
#include "../structures/heap_monitor.h"
#include "VzdelanieUJ.h"
#include "VekUJ.h"
#include "UzemnaJednotka.h"


using namespace std;
class CSVCitac {
public:

	
	structures::SortedSequenceTable<std::string, UzemnaJednotka*>* nacitajKraje() {
		string fname = "../CSVSubory/kraje.csv";

		vector<vector<string>> content;
		vector<string> row;
		string line, word;

		fstream file(fname, ios::in);
		if (file.is_open())
		{
			while (getline(file, line))
			{
				row.clear();

				stringstream str(line);

				while (getline(str, word, ','))
					row.push_back(word);
				content.push_back(row);
			}
		}
		else {
			cout << "Nepodarilo sa otvorit \n";
	}

		structures::SortedSequenceTable<string, UzemnaJednotka*>* vysledok = new structures::SortedSequenceTable<string, UzemnaJednotka*>();
		structures::LinkedList<string>* vsetko = new structures::LinkedList<string>();				//vsetko musim deletnut

		for (int i = 0; i < content.size(); i++)
		{
			std::string row = "";
			for (int j = 0; j < content[i].size(); j++)
			{
				row += content[i][j];
			}
			row += ";"; // pre zistovanie ukoncenia neskor
			vsetko->add(row);

		}

		//upravi na nazov a kod
		vsetko->removeAt(0);
		for (int i = 0; i < vsetko->size(); i++)
		{
			int counter = 0;
			while (counter != 4) {
				if (vsetko->at(i).at(0) == ';') {
					counter++;
				}
				vsetko->at(i).erase(0, 1);
			}
			vsetko->at(i).erase(vsetko->at(i).size()-1, 1);
		}
		//koniec upravi na nazov a kod

		structures::LinkedList<string>* kod = new structures::LinkedList<string>();   //musim deletnut
		kod->assign(*vsetko);

		//vypise nazov 
		for (int i = 0; i < vsetko->size(); i++)
		{
			while (vsetko->at(i).at(vsetko->at(i).size() - 1) != ';') {
				vsetko->at(i).erase(vsetko->at(i).size() - 1, 1);
			}
			vsetko->at(i).erase(vsetko->at(i).size() - 1, 1);
		}
		//koniec vypisu nazvu

		//vypise kod
		for (int i = 0; i < kod->size(); i++)
		{
			int counter = 0;
			while (counter != 1) {
				if (kod->at(i).at(0) == ';') {
					counter++;
				}
				kod->at(i).erase(0, 1);
			}
		}
		//koniec vypis kodu
	
		for (int i = 0; i < vsetko->size(); i++) {
			vysledok->insert(kod->at(i), new UzemnaJednotka(vsetko->at(i)));
		}
		
		delete vsetko;
		delete kod;
		return vysledok;
	}

	

	structures::SortedSequenceTable<std::string, UzemnaJednotka*>* nacitajObce() {
		string fname = "../CSVSubory/obce.csv";

		vector<vector<string>> content;
		vector<string> row;
		string line, word;

		fstream file(fname, ios::in);
		if (file.is_open())
		{
			while (getline(file, line))
			{
				row.clear();

				stringstream str(line);

				while (getline(str, word, ','))
					row.push_back(word);
				content.push_back(row);
			}
		}
		else {
			cout << "Nepodarilo sa otvorit \n";
		}
		structures::LinkedList<string>* vsetko = new structures::LinkedList<string>();
		structures::SortedSequenceTable<string, UzemnaJednotka*>* vysledok = new structures::SortedSequenceTable<string, UzemnaJednotka*>();

		for (int i = 0; i < content.size(); i++)
		{
			std::string row = "";
			for (int j = 0; j < content[i].size(); j++)
			{
				row += content[i][j];
			}
			row += ";"; // pre zistovanie ukoncenia neskor
			vsetko->add(row);

		}


		//oreze na kod a nazov
		vsetko->removeAt(0);
		for (int i = 0; i < vsetko->size(); i++)
		{
			int pocitadlo = 0;
			int prva = 0;
			bool bol = false;
			for (int y = 0; y < vsetko->at(i).size(); y++)
			{
				if (vsetko->at(i).at(y) == ';') {
					pocitadlo++;
				}
				if (pocitadlo == 1 && bol == false) {
					prva = y;
					bol = true;
				}
				if (pocitadlo == 3) {
					vsetko->at(i).erase(y, vsetko->at(i).size());
					vsetko->at(i).erase(0, prva+1);
				}
			}
		}
		//koniec orezavania

		structures::LinkedList<string>* kod = new structures::LinkedList<string>();
		kod->assign(*vsetko);


		//nazov
		for (int i = 0; i < vsetko->size(); i++)
		{
			int counter = 0;
			while (counter != 1) {
				if (vsetko->at(i).at(0) == ';') {
					counter++;
				}
				vsetko->at(i).erase(0, 1);
			}
			//cout << vsetko->at(i) << "\n";
		}
		//koniec nazov
		
		//kod
		for (int i = 0; i < kod->size(); i++)
		{
			while (kod->at(i).at(kod->at(i).size() - 1) != ';') {
				kod->at(i).erase(kod->at(i).size() - 1, 1);
			}
			kod->at(i).erase(kod->at(i).size() - 1, 1);
		}
		//koniec kod

		for (int i = 0; i < vsetko->size(); i++) {
			vysledok->insert(kod->at(i), new UzemnaJednotka(vsetko->at(i)));	
		}



		//koniec pridanie do vysledku
		delete vsetko;
		delete kod;
		return vysledok;
	}


	structures::SortedSequenceTable<std::string, UzemnaJednotka*>* nacitajOkresy() {
		string fname = "../CSVSubory/okresy.csv";

		vector<vector<string>> content;
		vector<string> row;
		string line, word;

		fstream file(fname, ios::in);
		if (file.is_open())
		{
			while (getline(file, line))
			{
				row.clear();

				stringstream str(line);

				while (getline(str, word, ','))
					row.push_back(word);
				content.push_back(row);
			}
		}
		else {
			cout << "Nepodarilo sa otvorit \n";
		}
		structures::LinkedList<string>* vsetko = new structures::LinkedList<string>();
		structures::SortedSequenceTable<string, UzemnaJednotka*>* vysledok = new structures::SortedSequenceTable<string, UzemnaJednotka*>();

		for (int i = 0; i < content.size(); i++)
		{
			std::string row = "";
			for (int j = 0; j < content[i].size(); j++)
			{
				row += content[i][j];
			}
			row += ";"; // pre zistovanie ukoncenia neskor
			vsetko->add(row);

		}


		//oreze na kod a nazov
		vsetko->removeAt(0);
		for (int i = 0; i < vsetko->size(); i++)
		{
			int pocitadlo = 0;
			int prva = 0;
			bool bol = false;
			for (int y = 0; y < vsetko->at(i).size(); y++)
			{
				if (vsetko->at(i).at(y) == ';') {
					pocitadlo++;
				}
				if (pocitadlo == 1 && bol == false) {
					prva = y;
					bol = true;
				}
				if (pocitadlo == 3) {
					vsetko->at(i).erase(y, vsetko->at(i).size());
					vsetko->at(i).erase(0, prva+1);
				}
			}
		}
		//koniec orezavania

		structures::LinkedList<string>* kod = new structures::LinkedList<string>();
		kod->assign(*vsetko);


		//nazov
		for (int i = 0; i < vsetko->size(); i++)
		{
			int counter = 0;
			while (counter != 1) {
				if (vsetko->at(i).at(0) == ';') {
					counter++;
				}
				vsetko->at(i).erase(0, 1);
			}
			//cout << vsetko->at(i) << "\n";
		}
		//koniec nazov

		//kod
		for (int i = 0; i < kod->size(); i++)
		{
			while (kod->at(i).at(kod->at(i).size() - 1) != ';') {
				kod->at(i).erase(kod->at(i).size() - 1, 1);
			}
			kod->at(i).erase(kod->at(i).size() - 1, 1);
		}
		//koniec kod

		for (int i = 0; i < vsetko->size(); i++) {
			vysledok->insert(kod->at(i), new UzemnaJednotka(vsetko->at(i)));
		}



		//koniec pridanie do vysledku
		delete vsetko;
		delete kod;
		return vysledok;
	}
	
	
	structures::SortedSequenceTable<string,VekUJ*>* nacitajVek() {

		string fname = "../CSVSubory/vek.csv";

		vector<vector<string>> content;
		vector<string> row;
		string line, word;


		fstream file(fname, ios::in);
		if (file.is_open())
		{
			while (getline(file, line))
			{
				row.clear();

				stringstream str(line);

				while (getline(str, word, ','))
					row.push_back(word);
				content.push_back(row);
			}
		}
		else {
			cout << "Nepodarilo sa otvorit \n";
		}
		

		structures::LinkedList<std::string>* pomocnyLL = new structures::LinkedList<std::string>;
		structures::SortedSequenceTable<string, VekUJ*>* vysledok = new structures::SortedSequenceTable<string, VekUJ*>();




		for (int i = 0; i < content.size(); i++)

		{

			std::string riadok = "";
			for (int j = 0; j < content[i].size(); j++)
			{
				riadok += content[i][j];
			}
			riadok += ";";
			pomocnyLL->add(riadok);
		}

		pomocnyLL->removeAt(0);
		for (int i = 0; i < pomocnyLL->size(); i++)
		{
			structures::Array<int>* cisla = new structures::Array<int>(202);
			string kodObce = pomocnyLL->at(i).substr(0, 12);
			pomocnyLL->at(i).erase(0, 13);
			VekUJ* vek = new VekUJ();
			//vymazem nazov..
			while (pomocnyLL->at(i).at(0) != ';') {
				pomocnyLL->at(i).erase(0, 1);
			}
			//vymazem bodkociarku
			pomocnyLL->at(i).erase(0, 1);

			//ukladanie cisel

			string riadok = pomocnyLL->at(i);
			
			int celkovo = 0;
			while (riadok != "") {
				
				int counter = 0;
				while (riadok.at(counter) != ';') {
					counter++;
				}
				int cislo = stoi(riadok.substr(0, counter));
				cisla->at(celkovo) = (cislo);
				celkovo++;
				riadok.erase(0, counter + 1);

			}

			for (int y = 0; y < 101; y++)
			{
				vek->nastavVekKtoryKolkoMuzi(y, cisla->at(y));

				if (y < 15) {
					vek->pripocitajVSMuziPRVA(cisla->at(y));
				}
				if (y >= 15 && y <= 64) {
					vek->pripocitajVSMuziDRUHA(cisla->at(y));
				}
				if (y > 64  && y <= 101) {
					vek->pripocitajVSMuziTRETIA(cisla->at(y));
				}

				vek->nastavVekKtoryKolkoZeny(y, cisla->at(y+101));

				if (y < 15) {
					vek->pripocitajVSZenyPRVA(cisla->at(y+101));
				}
				if (y >= 15 && y <= 64) {
					vek->pripocitajVSZenyDRUHA(cisla->at(y+101));
				}
				if (y > 64 && y <= 101) {
					vek->pripocitajVSZenyTRETIA(cisla->at(y+101));
				}

			}

			vysledok->insert(kodObce, vek);
			delete cisla;
		}

		delete pomocnyLL;
		return vysledok;
	}
		



	structures::SortedSequenceTable<std::string, VzdelanieUJ*>* nacitajVzdelanie() {
	
		string fname = "../CSVSubory/vzdelanie.csv";


		vector<vector<string>> content;
		vector<string> row;
		string line, word;

		

		fstream file(fname, ios::in);
		if (file.is_open())
		{
			while (getline(file, line))
			{
				row.clear();

				stringstream str(line);

				while (getline(str, word, ','))
					row.push_back(word);
				content.push_back(row);
			}
		}
		else {
			cout << "Nepodarilo sa otvorit \n";
		}
		
		structures::LinkedList<std::string>* pomocnyLL = new structures::LinkedList<std::string>;
		structures::SortedSequenceTable<std::string, VzdelanieUJ*>* vysledok = new structures::SortedSequenceTable<std::string, VzdelanieUJ*>();

		for (int i = 0; i < content.size(); i++)

		{
			
			std::string riadok = "";
			for (int j = 0; j < content[i].size(); j++)
			{
				riadok += content[i][j];
			}
			riadok += ";";
			pomocnyLL->add(riadok);
		}


		for (int i = 1; i < pomocnyLL->size(); i++)
		{
			string kodObce = pomocnyLL->at(i).substr(0, 12);
			pomocnyLL->at(i).erase(0, 13);
			VzdelanieUJ* vzdelanie = new VzdelanieUJ();

			//vymazem nazov..
			while (pomocnyLL->at(i).at(0) != ';') {
				pomocnyLL->at(i).erase(0, 1);
			}
			//vymazem bodkociarku
			pomocnyLL->at(i).erase(0, 1);
		

			//ukladanie cisel
			
			string riadok = pomocnyLL->at(i);
		
			int celkovo = 0;
			while (riadok != "") {
				
				int counter = 0;
				while (riadok.at(counter) != ';') {
					counter++;
				}
				int cislo = stoi(riadok.substr(0, counter));

				vzdelanie->pripocitajKtoreKolko(celkovo, cislo);

				celkovo++;
				riadok.erase(0, counter + 1);
			}
			vysledok->insert(kodObce, vzdelanie);
		}



		delete pomocnyLL;
		return vysledok;
	}
};


