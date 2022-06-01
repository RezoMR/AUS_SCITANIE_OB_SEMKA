#pragma once

#include "matrix.h"
#include <stdexcept>
#include "../vector/vector.h"
#include "../utils.h"

namespace structures
{
	/// <summary> Implementacia matice v suvislej pamati. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v matici. </typepram>
	template<typename T>
	class CoherentMatrix
		: public Matrix<T>
	{
	public:
		/// <summary>
		///	Konstruktor. Vytvori maticu o danom pocte riadkov a stlpcov.
		/// Polozky su inicializovane na "nulovu" hodnotu typu T.
		/// </summary>
		/// <param name="rowCount"> Pocet riadkov. </param>
		/// <param name="columnCount"> Pocet stlpcov. </param>
		CoherentMatrix(size_t pocetRiadkov, size_t pocetStlpcov);

		/// <summary> Inicializuje tuto maticu ako kopiu matice odovzdanej ako parameter. </summary>
		/// <param name = "other"> Odkaz na maticu, z ktorej sa prevezmu vlastnosti. </param>
		CoherentMatrix(CoherentMatrix& other);

		/// <summary> Destruktor. </summary>
		~CoherentMatrix();

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
		T& at(int pocetRiadkov, int pocetStlpcov) override;

		/// <summary> Mapovacia funkcia, ktora prevedie index do koherentnej matice. </summary>
		/// <param name = "riadok"> Index v poli. </param>
		/// <param name = "stlpec"> Index v poli. </param>
		/// <returns> Index vo vektore. </returns>
		int mapFunction(int pocetRiadkov, int pocetStlpcov) const;
	private:
		//atribúty
		size_t pocetRiadkov_;
		size_t pocetStlpcov_;
		Vector* coherentMat_;
		size_t size_;
	};

	template<typename T>
	inline CoherentMatrix<T>::CoherentMatrix(size_t pocetRiadkov, size_t pocetStlpcov):
		coherentMat_(new Vector(pocetRiadkov * pocetStlpcov * sizeof(T)))
	{
		//TODO Zadanie 1: CoherentMatrix
		pocetRiadkov_ = pocetRiadkov;
		pocetStlpcov_ = pocetStlpcov;
		size_ = pocetRiadkov * pocetStlpcov;
	}

	template<typename T>
	inline CoherentMatrix<T>::CoherentMatrix(CoherentMatrix& other) :
		coherentMat_(new Vector(*(other.coherentMat_))),
		size_(other.size()),
		pocetRiadkov_(other.getRowCount()),
		pocetStlpcov_(other.getColumnCount())
	{
		//TODO Zadanie 1: CoherentMatrix
		//kopirovaci konstruktor
	}

	template<typename T>
	inline CoherentMatrix<T>::~CoherentMatrix()
	{
		//TODO Zadanie 1: CoherentMatrix
		//deštruktor
		delete coherentMat_;
		coherentMat_ = nullptr;
		size_ = 0;
		pocetRiadkov_ = 0;
		pocetStlpcov_ = 0;
	}

	template<typename T>
	inline Structure& CoherentMatrix<T>::assign(Structure& other)
	{
		//TODO Zadanie 1: CoherentMatrix
		if (this != &other) {

			CoherentMatrix<T>& druhy = dynamic_cast<CoherentMatrix<T>&> (other);
			if (pocetRiadkov_ != druhy.getRowCount() || pocetStlpcov_ != druhy.getColumnCount()) {
				throw std::invalid_argument("Array sizes are not the same!");
			}
			coherentMat_->assign(*(druhy.coherentMat_));
		}
		return *this;
	}

	template<typename T>
	inline bool CoherentMatrix<T>::equals(Structure& other)
	{
		//TODO Zadanie 1: CoherentMatrix
		CoherentMatrix<T>* druhy = dynamic_cast<CoherentMatrix<T>*>(&other);
		if (druhy != nullptr) {
			return coherentMat_->equals(*druhy->coherentMat_);
		}
		else {
			return false;
		}
	}

	template<typename T>
	inline size_t CoherentMatrix<T>::size()
	{
		//TODO Zadanie 1: CoherentMatrix
		return size_;
	}

	template<typename T>
	inline size_t CoherentMatrix<T>::getRowCount()
	{
		//TODO Zadanie 1: CoherentMatrix
		return pocetRiadkov_;
	}

	template<typename T>
	inline size_t CoherentMatrix<T>::getColumnCount()
	{
		//TODO Zadanie 1: CoherentMatrix
		return pocetStlpcov_;
	}

	template<typename T>
	inline T& CoherentMatrix<T>::at(int pocetRiadkov, int pocetStlpcov)
	{
		//TODO Zadanie 1: CoherentMatrix
		// 1, pomocou mapovacej funckie ziskaj index vo vektore
		// 2, pomocou getBytePointer ziskaj ukazovatel na byte vo vektore na indexe z kroku 1
		// 3, pretypuj ukazovatel z kroku 2 na T*
		// vrat hodnotu podukazovatelom z kroku 3

		//dynamic cast je vhodny pre objekty
		//reinterpret cast neriesi konverzie

		int vectorIndex = mapFunction(pocetRiadkov, pocetStlpcov);
		byte* ptrByte = coherentMat_->getBytePointer(vectorIndex);
		T* ptrT = reinterpret_cast<T*>(ptrByte);

		return *ptrT;
	}
	template<typename T>
	inline int CoherentMatrix<T>::mapFunction(int pocetRiadkov, int pocetStlpcov) const
	{
		Utils::rangeCheckExcept(pocetRiadkov, pocetRiadkov_, "Zadal si vacsi index riadku ako je velkost matice!");
		Utils::rangeCheckExcept(pocetStlpcov, pocetStlpcov_, "Zadal si vacsi index stlpca ako je velkost matice!");
		int index = (pocetRiadkov * pocetStlpcov_ + pocetStlpcov) * sizeof(T);
		return index;
	}
}