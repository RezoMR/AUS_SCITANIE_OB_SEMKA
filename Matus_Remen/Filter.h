#pragma once
#include "../structures/table/sorted_sequence_table.h"
#include "Kriterium.h"

template<typename O>
class Filter {
public:
	virtual bool pass(O& o) = 0;
	virtual ~Filter() = default;
};