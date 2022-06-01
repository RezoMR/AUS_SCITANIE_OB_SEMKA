#pragma once
#include "Kriterium.h"

#include "Filter.h"

template<typename O, typename ValueType>

class FilterSKriteriom : public Filter<O> {

private:

	Kriterium<O, ValueType>* kriterium;

public:
	FilterSKriteriom(Kriterium<O, ValueType>* k) {
		kriterium = k;
	}

	~FilterSKriteriom() {
		delete kriterium;
	}

	bool pass(O& object) override {
		return passFilter(kriterium->evaluate(object));
	}

protected:
	virtual bool passFilter(ValueType value) = 0;
};

