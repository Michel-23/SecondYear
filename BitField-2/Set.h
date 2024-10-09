#include "BitField.h"
#include <cstdint>

class Set{
private:
    BitField _bitField; // структура хранения нашего множества
    size_t _maxPover;
public:
    Set(size_t mp);
    Set(const Set& set);//конструктор копирования
    Set(const BitField& bf); //конструктор преобразования
    operator BitField(); // чтобы статик каст работал

    size_t GetMaxPower();
    void InsertElem(uint64_t elem); // добавить элементы
    void DeleteElem(uint64_t elem); // удалить элементы
    bool IsMember (uint64_t elem);

    bool operator==(const Set& tmp);
    Set& operator=(const Set& tmp);
    Set operator+(const Set& tmp); // обЪединение 2 множеств
    Set operator+(uint64_t tmp);
    Set operator-(uint64_t tmp);
    Set operator*(const Set& tmp);
    Set operator~(); // операция дополнения множества

    friend std::istream& operator>>(std::istream& istr, Set& set);
    friend std::ostream& operator<<(std::istream& istr, const Set& set);
};