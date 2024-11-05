#include "BitField.h"
#include <cstdint>
#include <iostream>
#include <cstdint>
#include <bitset>
#include <cstring>

size_t BitField::GetMemIndex(size_t n) const {
    if (n >= _sizeBit)
        throw "Bit out of range!";
    size_t index = n / (8 * sizeof(uint16_t));
    return index;
}

uint16_t BitField::GetMask(size_t n) const{
    return 1 << (n % 16);
}

BitField::BitField() {
    _sizeBit = 0;
    _memSize = 0;
    _mem = nullptr;
}

BitField::BitField(size_t len){
    _sizeBit = len;
    _memSize = (len / (8 * sizeof(uint16_t))) + (len % (8 * sizeof(uint16_t)) != 0);
    _mem = new uint16_t [_memSize];
    std::memset(_mem, 0, _memSize * sizeof(uint16_t));
}

void BitField::Display(){
    for (int i = 0; i < _memSize; i++){
        std::cout << std::bitset<16>(_mem[i]) << " ";
    }
    std::cout << std::endl;
}

void BitField::DisplayMem(){
    for (int i = 0; i < _memSize; i++){
        std::cout << (_mem[i]) << " ";
    }
    std::cout << std::endl;
}

BitField::~BitField(){
    delete[] _mem;
} 

BitField::BitField(const BitField& tmp){
    _sizeBit = tmp._sizeBit;
    _memSize = tmp._memSize;
    _mem = new uint16_t[_memSize];
    for (size_t i = 0; i < _memSize; i++) // memcpy(_mem, tmp._mem, sizeof(uint16_t)*_memSize);
        _mem[i] = tmp._mem[i];
}

size_t BitField::GetLength() const{
    return _sizeBit;
}

size_t BitField::GetMemSize(){
    return _memSize;
}

uint16_t* BitField::GetMem(){
    return _mem;
}

void BitField::SetBit(size_t n){
    if (n >= _sizeBit) {
        throw "Bit out of range";
    }
    _mem[GetMemIndex(n)] |= GetMask(n); // побитовое ИЛИ
}

void BitField::ClrBit(size_t n){
    uint16_t mask = GetMask(n);     // маска 0000000000001000 (если n=3)
    mask =~mask;                   // инвертируем => 1111111111110111
    _mem[GetMemIndex (n)] &= mask;
}

uint8_t BitField::GetBit(size_t n) const{
    if (n >= _sizeBit) {
        throw "Bit out of range!";
    }
    uint16_t res = (_mem[GetMemIndex(n)] >> (n % 16)) & 1;
    return (uint8_t)res;
}

BitField& BitField::operator=(const BitField& tmp){
    if (_sizeBit != tmp._sizeBit){
        delete [] _mem;
        _sizeBit = tmp._sizeBit;
        _memSize = tmp._memSize;
        _mem = new uint16_t[_memSize];
    }
    for (size_t i = 0; i < _memSize; ++i)
        _mem[i] = tmp._mem[i];
    return *this;
}

BitField BitField::operator|(const BitField& tmp){ // побитовое ИЛИ
    BitField B(tmp.GetLength());
    for (size_t i = 0; i < _memSize; i++){
        B._mem[i] = _mem[i] | tmp._mem[i];
    }
    return B;
}

BitField BitField::operator&(const BitField& tmp){ // а это побитовое И
    BitField B(*this);
    for (size_t i = 0; i < _memSize; i++){
        B._mem[i] = _mem[i] & tmp._mem[i];
    }
    return B;
}

BitField BitField::operator^(const BitField& tmp){
    if (_memSize != tmp._memSize){
        throw std::invalid_argument("BitField sizes must match"); // !
    }

    BitField B(_sizeBit);
    for (size_t i = 0; i < _memSize; i++){
        B._mem[i] ^= tmp._mem[i];
    }
    return B;
}

bool BitField::operator==(const BitField& tmp){
    if (_sizeBit != tmp._sizeBit){
        return false;
    }
    for (size_t i = 0; i < _memSize; ++i){
        if (_mem[i] != tmp._mem[i]){
            return false;
        }
    }
    return true;
}

BitField BitField::operator~(){
    BitField cpy = BitField(*this);
    for (size_t i = 0; i < _memSize; ++i){
        cpy._mem[i] = ~cpy._mem[i];
    }
    return cpy;
}
