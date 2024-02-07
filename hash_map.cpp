#include "hash_map.h"

#include <iostream>
#include <cmath>

hash_map::hash_map(size_t capacity){
    _size = 0; 
    _capacity = capacity; 
    _head = new hash_list[capacity];
}


hash_map::hash_map(const hash_map &other)
{
    _size = other._size;
    _capacity = other._capacity;
    _head = new hash_list[_capacity];

    for(int i = 0; i <= _size; i++)
    {
        this->_head[i] = other._head[i];        
    }

}

hash_map& hash_map:: operator=(const hash_map &other)
{
    if (this == &other) return *this;

    delete[] _head; 

    _size = other._size;
    _capacity = other._capacity;
    _head = new hash_list[_capacity];
    for (size_t i = 0; i < _capacity; ++i) {
        _head[i] = other._head[i]; 
    }

    return *this;

}

void hash_map::insert(int key, float value) 
{
    size_t index = std::abs(key) % _capacity;
    auto oldValue = _head[index].get_value(key);
    _head[index].insert(key, value);
    if (!oldValue.has_value()) {
        _size++;
    }
}

std::optional<float> hash_map::get_value(int key) const 
{
    int index_hash = abs(key) % _capacity;
    if(_head[index_hash].get_value(key).has_value())
    {
        return _head[index_hash].get_value(key);
    }
    return std::nullopt;
}

bool hash_map::remove(int key)
{
    size_t index = std::abs(key) % _capacity;
    if (_head[index].remove(key)) {
        _size--;
        return true;
    }
    return false;
}

size_t hash_map::get_size() const {
    return _size;
}


size_t hash_map::get_capacity() const {
    return _capacity;
}

void hash_map::get_all_keys(int *keys) 
{
   size_t index = 0;
    for (size_t i = 0; i < _capacity; ++i) {
        _head[i].reset_iter();
        while (!_head[i].iter_at_end()) {
            auto iterValue = _head[i].get_iter_value();
            if (iterValue.has_value()) {
                keys[index++] = *(iterValue->first); 
            }
            _head[i].increment_iter(); 
        }
    }
    
}

void hash_map::get_bucket_sizes(size_t *buckets) {
    for (size_t i = 0; i < _capacity; ++i) {
        buckets[i] = _head[i].get_size();
    }
}

hash_map::~hash_map() {
    delete[] _head;
}

