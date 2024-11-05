#include "BitField.h"
#include <cstdint>

// если 1 - число входит в множество, если 0 - не входит

class Set{
private:
    BitField _bitField; // структура хранения нашего множества
    size_t _maxPover; // мощность
public:
    Set(size_t mp);
    void Display();
    ~Set();
    Set(const Set& tmp);
    Set(const BitField& bf);
    Set& operator() (const Set& tmp);
    size_t GetMaxPower();
    void InsertElem(uint64_t elem);
    void DeleteElem(uint64_t elem);
    bool IsMember (uint64_t elem);
    bool operator==(const Set& tmp);
    Set& operator=(const Set& tmp);
    Set operator+(const Set& tmp);
    Set operator+(uint64_t tmp);
    Set operator-(uint64_t tmp);
    Set operator*(const Set& tmp);
    Set operator~();
    friend std::istream& operator>>(std::istream& istr, Set& set);
    friend std::ostream& operator<<(std::ostream& ostr, const Set& set);
};