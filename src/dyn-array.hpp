#ifndef ALGOLABS_DYN_ARRAY_HPP
#define ALGOLABS_DYN_ARRAY_HPP

#include <algorithm>
#define ALGOLABS_DYN_ARRAY_RESIZE_MULTIPLIER 1.6
#define ALGOLABS_DYN_ARRAY_BASE_SIZE 8


template<typename T>
class Array final {
protected:
  int _capacity;
  int _size;
  T* _data;
  T* _dataAlloc(int capacity) {
    return (T*)malloc(sizeof(T) * capacity);
  };

public:
  class ConstIterator {
  protected:
    int _index;
    const Array<T>* _array;
    bool _isForward;

  public:
    ConstIterator(const Array<T>* array, bool isForward = true) :
        _index(0),
        _array(array), // TODO: "Нехорошее решение"
        _isForward(isForward) { }
    ~ConstIterator() = default; // Ручной деструктор не нужен, так как тут важен только массив, а он и так деструктнется
    const T& get() const {
      return _isForward ? (*_array)[_index] : (*_array)[_array->size() - _index - 1];
    };
    void next() {
      ++_index;
    };
    bool hasNext() const {
      return (_index < _array->size());
    };
  };

  class Iterator : public ConstIterator {
  public:
    Iterator(const Array<T>* array, bool isForward = true) :
        ConstIterator(array, isForward) {};
    void set(const Array<T>* value) {
      this->_array = value;
    };
  };

  Array(int capacity = ALGOLABS_DYN_ARRAY_BASE_SIZE) :
      _capacity(capacity),
      _size(0),
      _data(_dataAlloc(capacity)) { }
  Array(const Array<T>& other) :
      _capacity(other._capacity),
      _size(other._size),
      _data(_dataAlloc(other._capacity)) { std::copy(other._data, other._data + _size, _data); }
  Array(Array<T>&& other) noexcept :
      Array() {
    swap(*this, other);
  }
  ~Array() {
    for (int i = 0; i < _size; ++i) {
      _data[i].~T();
    }
    free(_data);
  };

  template <typename TN>
  friend void swap(Array<TN>& lhs, Array<TN>& rhs);

  int insert(const T& value) {
    return insert(_size, value);
  };
  int insert(int index, const T& value) {
    if (index < 0) {
      return -1;
    }

    if (_size >= _capacity) { // > стоит на ВСЯКИЙ случай, такого быть не должно, но так можно будет избежать дальнейший DL
      _capacity *= ALGOLABS_DYN_ARRAY_RESIZE_MULTIPLIER;
      T* data = _dataAlloc(_capacity);
      for (int i = 0; i < _size; ++i) {
        new (data + i) T(std::move(_data[i]));
      }
      std::swap(_data, data);
      free(data);
    }

    index = index > _size ? _size: index;

    for (int i = _size; i > index; --i) {
      new (_data + i) T(std::move(_data[i - 1]));
    }
    new (_data + index) T(value);

    return _size++;
  }
  void remove(int index) {
    if (index < 0 || index >= _size) {
      return;
    }

    _data[index].~T();
    for (int i = index; i < _size - 1; ++i) {
      new (_data + i) T(std::move(_data[i + 1]));
    }

    --_size;
  }
  int size() const {
    return _size;
  };
  Iterator iterator() {
    return Iterator(this);
  };
  ConstIterator iterator() const {
    return ConstIterator(this);
  };
  Iterator reverseIterator() {
    return Iterator(this, false);
  };
  ConstIterator reverseIterator() const {
    return ConstIterator(this, false);
  };

  const T& operator[](int index) const {
    return _data[index];
  }
  T& operator[](int index) {
    return _data[index];
  }
  Array<T>& operator=(Array<T> rhs) {
    swap(this, rhs);
    return *this;
  }
};

template<typename T>
void swap(Array<T>& lhs, Array<T>& rhs);

#endif //ALGOLABS_DYN_ARRAY_HPP
