#include <iostream>
#include <cstdint>
#include <bitset>
#include <cstring>

class BitField {
private:
    size_t _sizeBit;
    uint16_t* _mem;
    size_t _memSize;

    size_t GetMemIndex(size_t n) const;
    uint16_t GetMask(size_t n) const;

public:
    BitField();
    BitField(size_t len);
    void Display();
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
    bool operator==(const BitField& tmp);
    BitField operator~();
};