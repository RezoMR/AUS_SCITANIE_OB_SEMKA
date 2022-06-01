#pragma once

#include "list.h"

namespace structures
{
    // implementacne tipy: 
    //  - namiesto triedy List<T> mozete v triede DoubleLinkedList<T> 
    //    zdedit jednostranne zretazeny zoznam (LinkedList<T>).
    //    ak tak urobite, mozete mnoho metod odstranit a prekryt iba tie, 
    //    ktore maju z pohladu obojsmerne zretazeneho zoznamu vyznam a
    //    zvysok nechat na predka.
    //  - nezabudnite si vytvorit triedu pre prvok obojstranne zretazeneho zoznamu.
    //    opat tento prvok mozete zdedit z prvku jednostranne zretazeneho zoznamu.
    //  - ak vyuzijete dedicnost, budete moct vyuzit predkove iteratory, 
    //    takze ich nebudete musiet implementovat.

    /// <summary> Obojstranne zretazeny zoznam. </summary>
    /// <typeparam name = "T"> Typ dat ukladanych v zozname. </typepram>
    /// 
    template<typename T>
    class DoubleLinkedListItem : public DataItem<T>
    {
    public:
        /// <summary> Konstruktor. </summary>
        /// <param name = "data"> Data, ktore uchovava. </param>
        DoubleLinkedListItem(T data);

        /// <summary> Kopirovaci konstruktor. </summary>
        /// <param name = "other"> Prvok jednstranne zretazeneho zoznamu, z ktoreho sa prevezmu vlastnosti.. </param>
        DoubleLinkedListItem(DoubleLinkedListItem<T>& other);

        /// <summary> Destruktor. </summary>
        ~DoubleLinkedListItem();

        /// <summary> Getter nasledujuceho prvku zretazeneho zoznamu. </summary>
        /// <returns> Nasledujuci prvok zretazeneho zoznamu. </returns>
        DoubleLinkedListItem<T>* getNext();
        DoubleLinkedListItem<T>* getPrev();

        /// <summary> Setter nasledujuceho prvku zretazeneho zoznamu. </summary>
        /// <param name = "next"> Novy nasledujuci prvok zretazeneho zoznamu. </param>
        void setNext(DoubleLinkedListItem<T>* next);
        void setPrev(DoubleLinkedListItem<T>* previous);
    private:
        /// <summary> Nasledujuci prvok zretazeneho zoznamu. </summary>
        DoubleLinkedListItem<T>* next_;
        DoubleLinkedListItem<T>* prev_;
    };
    template<typename T>


    class DoubleLinkedList : public List<T>
    {
    public:
        /// <summary> Konstruktor. </summary>
        DoubleLinkedList();

        /// <summary> Kopirovaci konstruktor. </summary>
        /// <param name = "other"> DoubleLinkedList, z ktoreho sa prevezmu vlastnosti. </param>
        DoubleLinkedList(DoubleLinkedList<T>& other);

        /// <summary> Destruktor. </summary>
        ~DoubleLinkedList();

        /// <summary> Vrati pocet prvkov v zozname. </summary>
        /// <returns> Pocet prvkov v zozname. </returns>
        size_t size() override;

        /// <summary> Priradenie struktury. </summary>
        /// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
        /// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
        Structure& assign(Structure& other) override;

        /// <summary> Porovnanie struktur. </summary>
        /// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
        /// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
        bool equals(Structure& other) override;

        /// <summary> Vrati adresou prvok na indexe. </summary>
        /// <param name = "index"> Index prvku. </param>
        /// <returns> Adresa prvku na danom indexe. </returns>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        T& at(int index) override;

        /// <summary> Priradenie struktury. </summary>
        /// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
        /// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
        bool maData(const T& data);

        /// <summary> Prida prvok do zoznamu. </summary>
        /// <param name = "data"> Pridavany prvok. </param>
        void add(const T& data) override;

        /// <summary> Vlozi prvok do zoznamu na dany index. </summary>
        /// <param name = "data"> Pridavany prvok. </param>
        /// <param name = "index"> Index prvku. </param>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        /// <remarks> Ak je ako index zadana hodnota poctu prvkov (teda prvy neplatny index), metoda insert sa sprava ako metoda add. </remarks>
        void insert(const T& data, int index) override;

        /// <summary> Odstrani prvy vyskyt prvku zo zoznamu. </summary>
        /// <param name = "data"> Odstranovany prvok. </param>
        /// <returns> true, ak sa podarilo prvok zo zoznamu odobrat, false inak. </returns>
        bool tryRemove(const T& data) override;

        /// <summary> Odstrani zo zoznamu prvok na danom indexe. </summary>
        /// <param name = "index"> Index prvku. </param>
        /// <returns> Odstraneny prvok. </returns>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        T removeAt(int index) override;

        /// <summary> Vrati index prveho vyskytu prvku v zozname. </summary>
        /// <param name = "data"> Prvok, ktoreho index sa hlada. </param>
        /// <returns> Index prveho vyskytu prvku v zozname, ak sa prvok v zozname nenachadza, vrati -1. </returns>
        int getIndexOf(const T& data) override;

        /// <summary> Vymaze zoznam. </summary>
        void clear() override;

        /// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
        /// <returns> Iterator na zaciatok struktury. </returns>
        /// <remarks> Zabezpecuje polymorfizmus. </remarks>
        Iterator<T>* getBeginIterator() override;

        /// <summary> Vrati skutocny iterator na koniec struktury </summary>
        /// <returns> Iterator na koniec struktury. </returns>
        /// <remarks> Zabezpecuje polymorfizmus. </remarks>
        Iterator<T>* getEndIterator() override;
    private:
        size_t size_;

        DoubleLinkedListItem<T>* first_;

        DoubleLinkedListItem<T>* last_;

    private:
        DoubleLinkedListItem<T>* getItemAtIndex(int index);
    private:
        /// <summary> Iterator pre LinkedList. </summary>
        class DoubleLinkedListIterator : public Iterator<T>
        {
        public:
            /// <summary> Konstruktor. </summary>
            /// <param name = "position"> Pozicia v zretazenom zozname, na ktorej zacina. </param>
            DoubleLinkedListIterator(DoubleLinkedListItem<T>* position);

            /// <summary> Destruktor. </summary>
            ~DoubleLinkedListIterator();

            /// <summary> Operator priradenia. Priradi do seba hodnotu druheho iteratora. </summary>
            /// <param name = "other"> Druhy iterator. </param>
            /// <returns> Vrati seba po priradeni. </returns>
            Iterator<T>& operator=(Iterator<T>& other) override;

            /// <summary> Porovna sa s druhym iteratorom na nerovnost. </summary>
            /// <param name = "other"> Druhy iterator. </param>
            /// <returns> True, ak sa iteratory nerovnaju, false inak. </returns>
            bool operator!=(Iterator<T>& other) override;

            /// <summary> Vrati data, na ktore aktualne ukazuje iterator. </summary>
            /// <returns> Data, na ktore aktualne ukazuje iterator. </returns>
            T operator*() override;

            /// <summary> Posunie iterator na dalsi prvok v strukture. </summary>
            /// <returns> Iterator na dalsi prvok v strukture. </returns>
            /// <remarks> Zvycajne vrati seba. Ak vrati iny iterator, povodny bude automaticky zruseny. </remarks>
            Iterator<T>& operator++() override;

        private:
            /// <summary> Aktualna pozicia v zozname. </summary>
            DoubleLinkedListItem<T>* position_;
        };
    };

    template<typename T>
    inline DoubleLinkedList<T>::DoubleLinkedList() :
        size_(0),
        first_(nullptr),
        last_(nullptr)
    {

    }

    template<typename T>
    inline DoubleLinkedList<T>::DoubleLinkedList(DoubleLinkedList<T>& other) :
        DoubleLinkedList<T>()
    {
        assign(other);
    }

    template<typename T>
    inline DoubleLinkedList<T>::~DoubleLinkedList()
    {
        clear();

    }

    template<typename T>
    inline size_t DoubleLinkedList<T>::size()
    {
        return size_;
    }

    template<typename T>
    inline Structure& DoubleLinkedList<T>::assign(Structure& other)
    {

        if (this != &other) {
            DoubleLinkedList<T>& otherDoubleLinkedList = dynamic_cast<DoubleLinkedList<T>&>(other);
            clear();
            DoubleLinkedListItem<T>* otherItem = otherDoubleLinkedList.first_;
            while (otherItem != nullptr) {
                add(otherItem->accessData());
                otherItem = otherItem->getNext();
            }
        }
        return *this;

    }

    template<typename T>
    inline bool DoubleLinkedList<T>::equals(Structure& other)
    {
        DoubleLinkedList<T>* otherDoubleLinkedList = dynamic_cast<DoubleLinkedList<T>*>(&other);
        if (otherDoubleLinkedList == nullptr) {
            return false;
        }

        DoubleLinkedListItem<T>* item = first_;
        DoubleLinkedListItem<T>* otherItem = otherDoubleLinkedList->first_;

        while (item != nullptr) {
            if (item->accessData() != otherItem->accessData()) {
                return false;
            }
            item = item->getNext();
            otherItem = otherItem->getNext();
        }

        return true;

    }

    template<typename T>
    inline T& DoubleLinkedList<T>::at(int index)
    {
        return getItemAtIndex(index)->accessData();
    }

    //pomocnaMetoda//pomocnaMetoda//pomocnaMetoda//pomocnaMetoda//pomocnaMetoda//pomocnaMetoda//pomocnaMetoda//pomocnaMetoda//pomocnaMetoda//
    //pomocnaMetoda//pomocnaMetoda//pomocnaMetoda//pomocnaMetoda//pomocnaMetoda//pomocnaMetoda//pomocnaMetoda//pomocnaMetoda//pomocnaMetoda//

    template<typename T>
    inline bool DoubleLinkedList<T>::maData(const T& data)
    {
        bool vysledok = false;
        int index = 0;
        for (T element : *this)
        {
            if (element == data)
            {
                vysledok = true;
                break;
            }
            ++index;
        }
        return vysledok;
    }

    //pomocnaMetoda//pomocnaMetoda//pomocnaMetoda//pomocnaMetoda//pomocnaMetoda//pomocnaMetoda//pomocnaMetoda//pomocnaMetoda//pomocnaMetoda//
    //pomocnaMetoda//pomocnaMetoda//pomocnaMetoda//pomocnaMetoda//pomocnaMetoda//pomocnaMetoda//pomocnaMetoda//pomocnaMetoda//pomocnaMetoda//

    template<typename T>
    inline void DoubleLinkedList<T>::add(const T& data)
    {
        DoubleLinkedListItem<T>* newDoubleLinkedListItem = new DoubleLinkedListItem<T>(data);
        if (size_ == 0 && first_ == nullptr && last_ == nullptr) {
            first_ = newDoubleLinkedListItem;
            last_ = newDoubleLinkedListItem;
        }
        else {
            last_->setNext(newDoubleLinkedListItem);
            newDoubleLinkedListItem->setPrev(last_);
            last_ = newDoubleLinkedListItem;
        }
        size_++;
    }

    template<typename T>
    inline void DoubleLinkedList<T>::insert(const T& data, int index)
    {
        
        auto* newItem = new DoubleLinkedListItem<T>(data);
        if (index == size_)
        {
            add(data);
        }
            if (index == 0)
            {

                newItem->setNext(first_);
                first_->setPrev(newItem);
                first_ = newItem;
            }
            else
            {
                DoubleLinkedListItem<T>* previousItem = getItemAtIndex(index - 1);
                newItem->setPrev(previousItem);
                newItem->setNext(previousItem->getNext());
                previousItem->getNext()->setPrev(newItem);
                previousItem->setNext(newItem);
            }
            size_++;
    }

    template<typename T>
    inline bool DoubleLinkedList<T>::tryRemove(const T& data)
    {
        int index = getIndexOf(data);
        if (index != -1) {
            removeAt(index);
            return true;
        }
        else {
            return false;
        }
    }

    template<typename T>
    inline T DoubleLinkedList<T>::removeAt(int index)
    {
        Utils::rangeCheckExcept(index, size_, "Invalid index");
        DoubleLinkedListItem<T>* mazany = getItemAtIndex(index);

        if (index == 0)
        {
            mazany = first_;
            if (size_ == 1)
            {
                first_ = nullptr;
                last_ = nullptr;
            }
            else {
                mazany->getNext()->setPrev(nullptr);
                first_ = mazany->getNext();
            }
        }
        else {
            mazany = getItemAtIndex(index);
            if (index == size_ - 1) {
                last_ = mazany->getPrev();
                last_->setNext(nullptr);
            }
            else {
                mazany->getPrev()->setNext(mazany->getNext());
                mazany->getNext()->setPrev(mazany->getPrev());
            }
        }
        T result = mazany->accessData();
        delete mazany;
        size_--;
        return result;




    }

    template<typename T>
    inline int DoubleLinkedList<T>::getIndexOf(const T& data)
    {
        int index = 0;
        for (T element : *this)
        {
            if (element == data)
            {
                return index;
            }
            ++index;
        }
        return -1;

    }

    template<typename T>
    inline void DoubleLinkedList<T>::clear()
    {
        if (size_ != 0) {
            DoubleLinkedListItem<T>* itemToDelete = first_;

            while (itemToDelete != nullptr) {
                DoubleLinkedListItem<T>* nextItem = itemToDelete->getNext();
                delete itemToDelete;
                itemToDelete = nextItem;
            }

            size_ = 0;
            first_ = nullptr;
            last_ = nullptr;
        }
    }

    template<typename T>
    inline Iterator<T>* DoubleLinkedList<T>::getBeginIterator()
    {
        return new DoubleLinkedListIterator(first_);
    }

    template<typename T>
    inline Iterator<T>* DoubleLinkedList<T>::getEndIterator()
    {
        return new DoubleLinkedListIterator(nullptr);
    }

    template<typename T>
    inline DoubleLinkedListItem<T>* DoubleLinkedList<T>::getItemAtIndex(int index)
    {
        Utils::rangeCheckExcept(index, size_, "Invalid index GetItemAtIndex");
        int polka = size_ / 2;
        if (index < polka) {
            DoubleLinkedListItem<T>* current = first_;
            for (int i = 0; i < index; i++) {
                current = current->getNext();
            }
            return current;

        }
        else {
            DoubleLinkedListItem<T>* current = last_;

            for (int i = size_ - 1; i > index; i--) {
                current = current->getPrev();
            }

            return current;

        }

    }


    //item//item//item//item//item//item//item//item//item//item//item//item//item//item//item//item//item//item//item//item//item//item//item//item//item//item//item
    //item//item//item//item//item//item//item//item//item//item//item//item//item//item//item//item//item//item//item//item//item//item//item//item//item//item//item

    template<typename T>
    inline DoubleLinkedListItem<T>::DoubleLinkedListItem(T data) :
        DataItem<T>(data),
        next_(nullptr),
        prev_(nullptr)
    {
    }

    template<typename T>
    inline DoubleLinkedListItem<T>::DoubleLinkedListItem(DoubleLinkedListItem<T>& other) :
        DataItem<T>(other),
        next_(other.next_)
        previous_(other.previous_)
    {
    }


    template<typename T>
    inline DoubleLinkedListItem<T>::~DoubleLinkedListItem()
    {
        next_ = nullptr;
        prev_ = nullptr;
    }

    template<typename T>
    inline DoubleLinkedListItem<T>* DoubleLinkedListItem<T>::getNext()
    {
        return next_;
    }
    template<typename T>
    inline DoubleLinkedListItem<T>* DoubleLinkedListItem<T>::getPrev()
    {
        return prev_;
    }

    template<typename T>
    inline void DoubleLinkedListItem<T>::setNext(DoubleLinkedListItem<T>* next)
    {
        next_ = next;
    }
    template<typename T>
    inline void DoubleLinkedListItem<T>::setPrev(DoubleLinkedListItem<T>* previous)
    {
        prev_ = previous;
    }

    //iterastos//iterastos//iterastos//iterastos//iterastos//iterastos//iterastos//iterastos//iterastos//iterastos//iterastos//iterastos//iterastos//iterastos//iterastos//
    //iterastos//iterastos//iterastos//iterastos//iterastos//iterastos//iterastos//iterastos//iterastos//iterastos//iterastositerastos//iterastos//iterastos//iterastos//


    template<typename T>
    inline DoubleLinkedList<T>::DoubleLinkedListIterator::DoubleLinkedListIterator(DoubleLinkedListItem<T>* position) :
        position_(position)
    {
    }

    template<typename T>
    inline DoubleLinkedList<T>::DoubleLinkedListIterator::~DoubleLinkedListIterator()
    {
        position_ = nullptr;

    }

    template<typename T>
    inline Iterator<T>& DoubleLinkedList<T>::DoubleLinkedListIterator::operator=(Iterator<T>& other)
    {
        position_ = dynamic_cast<DoubleLinkedList<T>::DoubleLinkedListIterator&>(other).position_;
        return *this;
    }

    template<typename T>
    inline bool DoubleLinkedList<T>::DoubleLinkedListIterator::operator!=(Iterator<T>& other)
    {
        return dynamic_cast<DoubleLinkedList<T>::DoubleLinkedListIterator&>(other).position_ != position_;
    }

    template<typename T>
    inline T DoubleLinkedList<T>::DoubleLinkedListIterator::operator*()
    {
        return position_->accessData();
    }

    template<typename T>
    inline Iterator<T>& DoubleLinkedList<T>::DoubleLinkedListIterator::operator++()
    {
        position_ = position_->getNext();
        return *this;
    };

    

   
}
