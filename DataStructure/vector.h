//
// Created by jerry on 2024/8/11.
//

#ifndef VECTOR_H
#define VECTOR_H
namespace mycode {
    using std::size_t;
    template <class T>
    class vector {
    public:
        vector() = default;
        size_t size() const { return _size; }
        size_t capacity() const { return _capacity; }
        void reserve(size_t newCapacity) {
            if(newCapacity > _capacity) {//这种情况下进行扩容
                T* tmp = new T[newCapacity];
                for(size_t i = 0;i < _size;i++) { tmp[i] = _head[i]; }
                delete _head;
                _head = tmp;
                _capacity = newCapacity;
            }
        }
        void resize(size_t newSize) {
            reserve(newSize);//首先得保证空间足够
            if(newSize >= _size) _size = newSize;
            else assert(false);
        }
        void push_back(T&& key) {
            if(_size == _capacity) {
                reserve(_capacity * 2);
                _capacity *= 2;
            }
            _head[_size++] = key;//这里引入的是c++11提出的右值引用
        }
    private:
        T* _head = nullptr;
        size_t _size = 0;
        size_t _capacity = 0;
    };
}

#endif //VECTOR_H
