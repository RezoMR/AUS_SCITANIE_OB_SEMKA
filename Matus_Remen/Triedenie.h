
#pragma once
#include "../structures/table/unsorted_sequence_table.h"
#include "Kriterium.h"
#include "../structures/table/sorting/quick_sort.h"


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

	template<typename K, typename T, typename H>
	void sort(structures::UnsortedSequenceTable<K, T*>& tabulka, bool vzostupne, Kriterium<T, H>& krit, int min, int max) {
		    T* obj = tabulka.getItemAtIndex((min + max) / 2).accessData();
			H pivot = krit.evaluate(*obj);
			int lavy = min;
			int pravy = max;
			
			if (vzostupne)
			{
				do
				{
					while (krit.evaluate(*tabulka.getItemAtIndex(lavy).accessData()) < pivot)
					{
						lavy++;
					}
					while (krit.evaluate(*tabulka.getItemAtIndex(pravy).accessData()) > pivot)
					{
						pravy--;
					}
					if (lavy <= pravy) {
						tabulka.swap(lavy, pravy);
						lavy++;
						pravy--;
					}
				} while (lavy <= pravy);
				if (min< pravy) {
					sort(tabulka,true , krit,min,pravy);
				}
				if (min < max) {
					sort(tabulka, true, krit,lavy, max);
				}

			} else { //ak nie je bool paVzostupne true tak -> zostupne
				do {

					while (krit.evaluate(*tabulka.getItemAtIndex(lavy).accessData()) > pivot) {
						lavy++;
					}
					while (krit.evaluate(*tabulka.getItemAtIndex(pravy).accessData()) < pivot) {
						pravy--;
					}
					if (lavy <= pravy) {
						tabulka.swap(lavy, pravy);
						lavy++;
						pravy--;
					}
				} while (lavy <= pravy);
				if (min < pravy) {
					sort(tabulka, false, krit,min, pravy);
				}
				if (lavy < max) {
					sort(tabulka,false, krit,lavy, max);
				}
			}
		}
};