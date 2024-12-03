#pragma once

#include <iostream>
#include <cstdint>
#include <bitset>
#include <cstring>

class BitField {
private:
    // бколичество активных бит
    size_t _sizeBit;
    // битовое представление
    uint16_t* _mem;
    // количество 2-х байтовых ячеек
    size_t _memSize;

    /// @param n номер принимаемого бита
    /// @return в каком блоке _mem находится данный элемент
    size_t GetMemIndex(size_t n) const;

    /// @param n 
    /// @return 
    uint16_t GetMask(size_t n) const;

public:
    BitField();
    BitField(size_t len);
    void Display() const;
    void DisplayMem();
    ~BitField();
    BitField(const BitField& tmp);
    size_t GetLength() const;
    size_t GetMemSize();
    uint16_t* GetMem();
    void SetBit(size_t n);
    void ClrBit(size_t n);
    uint8_t GetBit(size_t n) const;
    BitField& operator=(const BitField& tmp);
    BitField operator|(const BitField& tmp);
    BitField operator&(const BitField& tmp);
    BitField operator^(const BitField& tmp);
    bool operator==(const BitField& tmp) const;
    BitField operator~();
    void ChangeNumberBits(size_t SizeBit);
};