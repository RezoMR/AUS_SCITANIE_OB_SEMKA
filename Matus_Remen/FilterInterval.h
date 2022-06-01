#pragma once

#include "FilterSKriteriom.h"
#include "EVS.h"

template<typename O, typename ValueType>

class FilterInterval : public FilterSKriteriom<O, ValueType> {

private:
	ValueType minimum;
	ValueType maximum;
		
public:

	FilterInterval(Kriterium<O, ValueType>* kriterium, ValueType min, ValueType max) : FilterSKriteriom<O, ValueType>(kriterium) {
		minimum = min;
		maximum = max;
	}
	virtual ~FilterInterval() = default;

	bool passFilter(ValueType hodnota) {
		if (hodnota >= minimum && hodnota <= maximum)
		{
			return true;
		}
		else {
			return false;
		}
	}
};