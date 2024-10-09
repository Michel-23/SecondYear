#include <iostream>

class BitField {
private:
    size_t _sizeBit;
    uint16_t* _mem;
    size_t _memSize;

    size_t GetMemIndex(size_t n) const;
    uint16_t GetMask(size_t n) const;
public:
    BitField(size_t len);
    BitField(const BitField& tmp);
    BitField& operator=(const BitField& tmp);
    
    size_t GetLength() const; // Получить количество бит
    void SetBit(size_t n);
    void ClrBit(size_t n){
        uint16_t mask = GetMask(n);
        mask =~mask;
        _mem[GetMemIndex (n)] &= mask;
    }

    uint8_t GetBit(size_t n) const; // Саша


    BitField operator|(const BitField& tmp){
        BitField B(tmp.GetLength());
        for (size_t i = 0; i < _memSize; i++){
            B._mem[i] = _mem[i] | tmp._mem[i];
        }
        return B;
    }

    BitField operator&(const BitField& tmp){
        BitField B(*this);
        for (size_t i = 0; i < _memSize; i++){
            B._mem[i] = _mem[i] & tmp._mem[i];
        }
        return B;
    }

    BitField operator^(const BitField& tmp){
        BitField B(*this);
        for (size_t i = 0; i < _memSize; i++){
            B._mem[i] ^= tmp._mem[i];
        }
        return B;
    }

    bool operator==(const BitField& tmp){
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

    BitField operator~(){
        BitField cpy = BitField(*this);
        for (size_t i = 0; i < _memSize; ++i){
            cpy._mem[i] = ~cpy._mem[i];
        }
        return cpy;
    }

    ~BitField(); // Все
};