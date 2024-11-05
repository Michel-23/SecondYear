#include <iostream>
#include <cstdint>
#include <bitset>
#include <cstring>

class BitField {
private:
    size_t _sizeBit;
    uint16_t* _mem;
    size_t _memSize;

    size_t GetMemIndex(size_t n) const {
        if (n >= _sizeBit)
            throw "Bit out of range!";
        size_t index = n / (8 * sizeof(uint16_t));
        return index;
    }

    uint16_t GetMask(size_t n) const{
        return 1 << (n % 16);
    }

public:
    BitField() {
        _sizeBit = 0;
        _memSize = 0;
        _mem = nullptr;
    }

    BitField(size_t len){
        _sizeBit = len;
        _memSize = (len / (8 * sizeof(uint16_t))) + (len % (8 * sizeof(uint16_t)) != 0);
        _mem = new uint16_t [_memSize];
        std::memset(_mem, 0, _memSize * sizeof(uint16_t));
    }

    void Display(){
        for (int i = 0; i < _memSize; i++){
            std::cout << std::bitset<16>(_mem[i]) << " ";
        }
        std::cout << std::endl;
    }

    void DisplayMem(){
        for (int i = 0; i < _memSize; i++){
            std::cout << (_mem[i]) << " ";
        }
        std::cout << std::endl;
    }

    ~BitField(){
        delete[] _mem;
    } 

    BitField(const BitField& tmp){
        _sizeBit = tmp._sizeBit;
        _memSize = tmp._memSize;
        _mem = new uint16_t[_memSize];
        for (size_t i = 0; i < _memSize; i++) // memcpy(_mem, tmp._mem, sizeof(uint16_t)*_memSize);
            _mem[i] = tmp._mem[i];
    }
    
    size_t GetLength() const{
        return _sizeBit;
    }

    size_t GetMemSize(){
        return _memSize;
    }

    uint16_t* GetMem(){
        return _mem;
    }

    void SetBit(size_t n){
        if (n >= _sizeBit) {
            throw "Bit out of range";
        }
        _mem[GetMemIndex(n)] |= GetMask(n); // побитовое ИЛИ
    }

    void ClrBit(size_t n){
        uint16_t mask = GetMask(n);     // маска 0000000000001000 (если n=3)
        mask =~mask;                   // инвертируем => 1111111111110111
        _mem[GetMemIndex (n)] &= mask;
    }

    uint8_t GetBit(size_t n) const{
        if (n >= _sizeBit) {
            throw "Bit out of range!";
        }
        uint16_t res = (_mem[GetMemIndex(n)] >> (n % 16)) & 1;
        return (uint8_t)res;
    }

    BitField& operator=(const BitField& tmp){
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

    BitField operator|(const BitField& tmp){ // побитовое ИЛИ
        BitField B(tmp.GetLength());
        for (size_t i = 0; i < _memSize; i++){
            B._mem[i] = _mem[i] | tmp._mem[i];
        }
        return B;
    }

    BitField operator&(const BitField& tmp){ // а это побитовое И
        BitField B(*this);
        for (size_t i = 0; i < _memSize; i++){
            B._mem[i] = _mem[i] & tmp._mem[i];
        }
        return B;
    }

    BitField operator^(const BitField& tmp){
        if (_memSize != tmp._memSize){
            throw std::invalid_argument("BitField sizes must match"); // !
        }

        BitField B(_sizeBit);
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
};