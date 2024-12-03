#include "Set.h"
#include "BitField.h"
#include <cstdint>
#include <vector>

Set::Set(size_t mp){
    _maxPover = mp;
    _bitField = BitField(_maxPover);
}

void Set::Display() const{
    std::cout << "Max Pover: " << _maxPover << std::endl;
    _bitField.Display();
}

void Set::DisplaySet(){
    _bitField.Display();
    std::cout << std::endl;
}

Set::~Set() {
    /* ничего*/
}

Set::Set(const Set& tmp){ //конструктор копирования
    _maxPover = tmp._maxPover;
    _bitField = tmp._bitField;
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

void Set::InsElem(uint64_t elem){
    _bitField.SetBit(elem);
}

void Set::DelElem(uint64_t elem){
    _bitField.ClrBit(elem);
}

bool Set::IsMember (uint64_t elem){
    return _bitField.GetBit(elem);
}

bool Set::operator==(const Set& tmp) const{
    return _bitField == tmp._bitField;
}

bool Set::operator!= (const Set &s){
    /*return !(*this == s);*/
    return !(_bitField == s._bitField);
}

Set& Set::operator=(const Set& tmp){
    if (this != &tmp){
        _bitField = tmp._bitField;
        _maxPover = tmp._maxPover;
    }
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
    /*Set res(_bitField);
    res._bitField.SetBit(tmp);*/
    Set res(*this);
    res.InsElem(tmp);
    return res;
}

Set Set::operator-(uint64_t tmp){
    Set res(_bitField);
    res._bitField.ClrBit(tmp);

    return res;
}

Set Set::operator*(const Set& tmp){
    
    Set LeftOperand(*this);
    Set RightOperand(tmp);

    this->Display();
    tmp.Display();

    if (LeftOperand._maxPover < RightOperand._maxPover){
        LeftOperand._bitField.ChangeNumberBits(RightOperand._maxPover);
        LeftOperand._maxPover = RightOperand._maxPover;
        std::cout << "LeftOperand._maxPover = " << (size_t)LeftOperand._maxPover << std::endl;
        std::cout << "RightOperand._maxPover = " << (size_t)RightOperand._maxPover << std::endl;

    }

    else if (LeftOperand._maxPover > RightOperand._maxPover){
        RightOperand._bitField.ChangeNumberBits(LeftOperand._maxPover);
        RightOperand._maxPover = LeftOperand._maxPover;
    }

    // Всё что ниже - ничего не менял

    Set res(LeftOperand._maxPover);
    res._bitField = LeftOperand._bitField & RightOperand._bitField;
    return res;
}

// операция дополнения множества
Set Set::operator~(){
    /*Set res(_bitField);
    res._bitField = ~_bitField;
    return res;*/

    Set result(GetMaxPower());
    _maxPover = GetMaxPower();
    for (size_t i = 0; i < _maxPover; i++) {
        if (!IsMember(i)== true) {// тек эл не входит то добовлем его 
            result.InsElem(i);
        }
    }
    return result;
}

std::ostream& operator<<(std::ostream& ostr, const Set& set){
    for (int i = 0; i < set._maxPover; i++) {
        ostr << (int)set._bitField.GetBit(i);
    }
    return ostr;
}

std::vector<uint64_t> Set::GetPrimary() {
    // вектор простых чисел
    std::vector<uint64_t> res;
    size_t p = 2;
    
    while (true)
    {    
        for (size_t i = 2*p; i < _maxPover; i=i+p /*шагаем по p*/){
            this->DelElem(i);
        }
        bool flag = 0;
        for (size_t i = p+1; i < _maxPover; i++){
            if (this->IsMember(i)){
                p = i;
                flag = 1;
                break;
            }
            
        }
        if(!flag){
            break;
        }
    }

    for (size_t i = 1; i < _maxPover; i++){
        if(this->IsMember(i)){
            res.push_back(i);
        }
    }

    return res;
}
