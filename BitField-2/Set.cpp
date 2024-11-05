#include "Set.h"
#include "BitField.h"
#include <cstdint>

Set::Set(size_t mp){
    _maxPover = mp;
    _bitField = BitField(_maxPover);
}

void Set::Display(){
    std::cout << "Max Pover: " << _maxPover << std::endl;
    _bitField.Display();
}

Set::~Set() {
    /* ничего */
}

Set::Set(const Set& tmp){ //конструктор копирования
    _maxPover = tmp._maxPover;
    _bitField = BitField(tmp._maxPover);
}

Set::Set(const BitField& bf){ //конструктор преобразования
    _maxPover = bf.GetLength();
    _bitField = BitField(_maxPover); // ??
    _bitField = bf; // ??
} 

Set& Set::operator() (const Set& tmp){
    return *this;
}

//operator BitField(const Set& _bitField); // чтобы статик каст работал, перегрузка ()

size_t Set::GetMaxPower(){
    return _maxPover;
}

void Set::InsertElem(uint64_t elem){
    _bitField.SetBit(elem);
}

void Set::DeleteElem(uint64_t elem){
    _bitField.ClrBit(elem);
}

bool Set::IsMember (uint64_t elem){
    return _bitField.GetBit(elem);
}

bool Set::operator==(const Set& tmp){
    return _bitField == tmp._bitField;
}

Set& Set::operator=(const Set& tmp){
    _bitField = tmp._bitField;
    _maxPover = tmp._maxPover;
    return *this;
}

// обЪединение 2 множеств
Set Set::operator+(const Set& tmp){
    if (_maxPover != tmp._maxPover) {
        throw "sets should have equal max power";
    }
    Set res(_maxPover);
    res._bitField = _bitField | tmp._bitField;
    return res;
}

Set Set::operator+(uint64_t tmp){
    Set res(_bitField);
    res._bitField.SetBit(tmp);
    return res;
}

Set Set::operator-(uint64_t tmp){
    Set res(_bitField);
    res._bitField.ClrBit(tmp);
    return res;
}

Set Set::operator*(const Set& tmp){
    if (_maxPover != tmp._maxPover) {
        throw "sets should have equal max power";
    }

    Set res(_maxPover);
    _bitField = _bitField & tmp._bitField;
    return res;
}

// операция дополнения множества
Set Set::operator~(){
    Set res(_bitField);
    res._bitField = ~_bitField;
}

std::istream& operator>>(std::istream& istr, Set& set);

std::ostream& operator<<(std::ostream& ostr, const Set& set){
    for (int i = 0; i < set._maxPover; i++) {
        ostr << (int)set._bitField.GetBit(i);
    }
    return ostr;
}