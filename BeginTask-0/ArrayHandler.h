#include <limits>

template<typename T>
class ArrayHandler {
private:
    // Сколько памяти выделено
    size_t _size;

    // Сколько элементов хранится с точки зрения того,
    // кто использует класс ArrayHandler.
    size_t _length;

    T* _array;

    T _max;

    T _min;
public:
    ArrayHandler(size_t size = 10) {
        _size = size;
        _length = 0;
        _array = new T[size];
        _max = std::numeric_limits<T>::min();
        _min = std::numeric_limits<T>::max();
    }

    ~ArrayHandler() {
        if (_array) {
            delete[] _array;
            _array = 0;
        }
    }

    void AppendElem(T elem) {
        
        if (_length >= _size) {
            size_t newsize = _size * 2;
            T* cpy = new T[newsize];
            memcpy(cpy, _array, sizeof(T) * _size);
            _size = newsize;
            delete[] _array;
            _array = cpy;
        }
        _array[_length] = elem;
        _length++;
        if (elem > _max) {
            _max = elem;
        }
        if (elem < _min) {
            _min = elem;
        }
    }

    bool IsContains(T elem) {
        for (int i = 0; i < _length; i++) {
            if (_array[i] == elem) {
                return true;
            }
        }
        return false;
    }

    T GetMax() {
        return _max;
    }

    T GetMin() {
        return _min;
    }
};