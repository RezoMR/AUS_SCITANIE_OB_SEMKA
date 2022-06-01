#pragma once

#include "matrix.h"
#include <stdexcept>
#include "../array/array.h"

namespace structures
{
	/// <summary> Implementacia matice v nesuvislej pamati. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v matici. </typepram>
	template<typename T>
	class IncoherentMatrix
		: public Matrix<T>
	{
	public:
		/// <summary>
		///	Konstruktor. Vytvori maticu o danom pocte riadkov a stlpcov.
		/// Polozky su inicializovane na "nulovu" hodnotu typu T.
		/// </summary>
		/// <param name="rowCount"> Pocet riadkov. </param>
		/// <param name="columnCount"> Pocet stlpcov. </param>
		IncoherentMatrix(size_t rowCount, size_t columnCount);

		/// <summary> Inicializuje tuto maticu ako kopiu matice odovzdanej ako parameter. </summary>
		/// <param name = "other"> Odkaz na maticu, z ktorej sa prevezmu vlastnosti. </param>
		IncoherentMatrix(IncoherentMatrix& other);

		/// <summary> Destruktor. </summary>
		~IncoherentMatrix();

		/// <summary>
		/// Ak je to mozne (parametrom je matica, ktora ma rovnake rozmery ako ako aktualna matica),
		/// tak skopiruje vlastnosti z matice odovzdanej ako parameter.
		/// Ak to nie je mozne, vyhodi sa vynimka.
		/// </summary>
		/// <param name = "other"> Odkaz na strukturu, z ktorej maju prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary>
		/// Ak je parametrom matica a obsah porovnavanych matic je rovnaky,
		/// tak vrati hodnotu true. V opacnom pripade vrati hodnotu false.
		/// </summary>
		/// <param name="other"> Odkaz na strukturu, s ktorou sa ma tato matica porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equals(Structure& other) override;

		/// <summary> Pocet vsetkych prvkov v matici. </summary>
		/// <returns> Pocet prvkov v matici. </returns>
		size_t size() override;

		/// <summary> Vrati pocet riadkov v matici. </summary>
		/// <returns> Pocet riadkov matice. </returns>
		size_t getRowCount() override;

		/// <summary> Vrati pocet stlpcov matice. </summary>
		/// <returns> Pocet stlpcov matice. </returns>
		size_t getColumnCount() override;

		/// <summary> Vrati odkaz na prvok v danom riadku a stlpci. </summary>
		/// <param name="rowIndex"> Index riadku. </param>
		/// <param name="columnIndex"> Index stlpca. </param>
		/// <returns> Odkaz na prvok na danych indexoch. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index riadku alebo stlpca nepatri do matice. </exception>
		T& at(int rowIndex, int columnIndex) override;
	private: 
		size_t pocetRiadkov_;
		size_t pocetStlpcov_;
		Array<Array<T>*>* inCoherentMat_;
		size_t size_;
	};

	template<typename T>
	inline IncoherentMatrix<T>::IncoherentMatrix(size_t pocetRiadkov, size_t pocetStlpcov)

	{
		//TODO Zadanie 1: InCoherentMatrix
		//konštruktoros pumpos bicákos
		pocetRiadkov_ = pocetRiadkov;
		pocetStlpcov_ = pocetStlpcov;
		size_ = pocetRiadkov * pocetStlpcov;

		//
		inCoherentMat_ = new Array<Array<T>*>(pocetRiadkov);
		for (int i = 0; i < pocetRiadkov; i++)
		{
			inCoherentMat_->at(i) = new Array<T>(pocetStlpcov);
		}

	}

	template<typename T>
	inline IncoherentMatrix<T>::IncoherentMatrix(IncoherentMatrix& other):
		size_(other.size()),
		pocetRiadkov_(other.getRowCount()),
		pocetStlpcov_(other.getColumnCout())
	{
		//TODO Zadanie 1: InCoherentMatrix
		//Kopírovací konštruktor
		inCoherentMat_ = new (Array<Array<T>*>(other.getRowCount()));
			for (int i = 0; i < pocetRiadkov; i++)
			{
				inCoherentMat_->at(i) = new Array<T>(other.getColumnCout());
			}
	}

	template<typename T>
	inline IncoherentMatrix<T>::~IncoherentMatrix()
	{
		//TODO Zadanie 1: InCoherentMatrix
		//deštruktor
		for (int i = 0; i < getRowCount(); i++)
		{
			delete inCoherentMat_->at(i);
			inCoherentMat_->at(i) = nullptr;
		}
		delete inCoherentMat_;
		inCoherentMat_ = nullptr;
		size_ = 0;
		pocetRiadkov_ = 0;
		pocetStlpcov_ = 0;
	}

	template<typename T>
	inline Structure& IncoherentMatrix<T>::assign(Structure& other)
	{
		//TODO Zadanie 1: InCoherentMatrix
		if (this != &other) {
			IncoherentMatrix<T>& druhy = dynamic_cast<IncoherentMatrix<T>&> (other);
			if (pocetRiadkov_ != druhy.getRowCount() || pocetStlpcov_ != druhy.getColumnCount()) {
				throw std::invalid_argument("Array sizes are not the same!");
			}
			inCoherentMat_->assign(*(druhy.inCoherentMat_));
			for (int i = 0; i < getRowCount(); i++)
			{
				inCoherentMat_->at(i) == druhy.inCoherentMat_->at(i);
			}
		}
		return *this;
	}

	template<typename T>
	inline bool IncoherentMatrix<T>::equals(Structure& other)
	{
		//TODO Zadanie 1: InCoherentMatrix
		IncoherentMatrix<T>* druhy = dynamic_cast<IncoherentMatrix<T>*>(&other);
		int stlpce = static_cast<int>(druhy->getColumnCount());
		int riadky = static_cast<int>(druhy->getRowCount());
		if (druhy != nullptr && stlpce == pocetStlpcov_ && riadky == pocetRiadkov_){
			Array<T>* pomoc;
			for (size_t i = 0; i < pocetRiadkov_; i++)
			{
				pomoc = inCoherentMat_->at(i);
				if (!(pomoc->equals(*druhy->inCoherentMat_->at(i)))) {
					return false;
				}
			}
		}
		else {
			return false;
		}
	}

	template<typename T>
	inline size_t IncoherentMatrix<T>::size()
	{
		//TODO Zadanie 1: InCoherentMatrix
		return size_;
	}

	template<typename T>
	inline size_t IncoherentMatrix<T>::getRowCount()
	{
		//TODO Zadanie 1: InCoherentMatrix
		return pocetRiadkov_;
	}

	template<typename T>
	inline size_t IncoherentMatrix<T>::getColumnCount()
	{
		//TODO Zadanie 1: InCoherentMatrix
		return pocetStlpcov_;
	}

	template<typename T>
	inline T& IncoherentMatrix<T>::at(int pocetRiadkov, int pocetStlpcov)
	{
		//TODO Zadanie 1: InCoherentMatrix
		//
		Utils::rangeCheckExcept(pocetRiadkov, pocetRiadkov_, "Zadal si vacsi index riadku ako je velkost matice!");
		Utils::rangeCheckExcept(pocetStlpcov, pocetStlpcov_, "Zadal si vacsi index stlpca ako je velkost matice!");

		size_t pomocny = static_cast<size_t>(pocetStlpcov);
		return (*inCoherentMat_->at(pocetRiadkov)).at(pomocny);
	}
}