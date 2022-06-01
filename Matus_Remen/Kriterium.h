#pragma once


	template<typename O, typename T>
	class Kriterium {

	public:
		virtual T evaluate(O& o) = 0;
		virtual ~Kriterium() = default;


	};


