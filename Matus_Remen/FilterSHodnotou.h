#pragma once

#include "FilterSKriteriom.h"

template<typename O, typename ValueType>

class FilterSHodnotou : public FilterSKriteriom<O, ValueType> {

private:
	ValueType hodnota;

protected:
	bool passFilter(ValueType value) override;

public:
	FilterSHodnotou(Kriterium<O, ValueType>* kriterium, ValueType h);
};

template<typename O, typename ValueType>
inline bool FilterSHodnotou<O, ValueType>::passFilter(ValueType value)
{
	return hodnota == value;
}

template<typename O, typename ValueType>
inline FilterSHodnotou<O, ValueType>::FilterSHodnotou(Kriterium<O, ValueType>* kriterium, ValueType value):
	FilterSKriteriom<O, ValueType>::FilterSKriteriom(kriterium),
	hodnota(value)
{
}
