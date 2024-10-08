#include <limits>

template<typename T>
class ArrayHandler {
private:
    // Сколько памяти выделено
    size_t _capacity;

    // Сколько элементов хранится с точки зрения того,
    // кто использует класс ArrayHandler.
    size_t _length;

    T* _array;

    T _max;

    T _min;
public:
    ArrayHandler(size_t capacity = 10) {
        _capacity = capacity;
        _length = 0;
        _array = new T[capacity];
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
        // [10, 20, 30, 12, -14]
        // _length = 5
        // _capacity = 5
        if (_length >= _capacity) {
            size_t newCapacity = _capacity * 2;
            T* cpy = new T[newCapacity];
            memcpy(cpy, _array, sizeof(T) * _capacity);
            _capacity = newCapacity;
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