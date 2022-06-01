#include <iostream>
#include "CSVCitac.h"
#include "../structures/heap_monitor.h"
#include "Priradovanie.h"
#include "../structures/table/sorted_sequence_table.h"

int main() {
	initHeapMonitor();
	Priradovanie* p = new Priradovanie();
	p->prirad();
	//CSVCitac* p = new CSVCitac();
	//p->nacitajVek();


	delete p;
	return 0;
}