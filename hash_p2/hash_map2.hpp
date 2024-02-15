#include "hash_map.h"

#include <iostream>
#include <cmath>

/*
Still a lot left to do, I tried to get some of the base code in it. The files in this folder are what are due.

*/

template<typename K, typename V>
hash_map::hash_map(size_t capacity, float upper_load_factor, float lower_load_factor){
    _size = 0; 
    _capacity = capacity; 
    _lower_load_factor = lower_load_factor;
    _upper_load_factor = upper_load_factor;
    //_head = new hash_list[capacity]; // questionable
    //pass in a capacity, and determine if it is in the range
}


template<typename K, typename V>
hash_map<K, V>::hash_map(const hash_map &other)
    : _upper_load_factor(other._upper_load_factor),
      _lower_load_factor(other._lower_load_factor),
      _size(other._size),
      _capacity(other._capacity),
      capacity_index(other.capacity_index) {
    _head = new hash_list<K, V>[_capacity];
    for (size_t i = 0; i < _capacity; ++i) {
        _head[i] = other._head[i]; 
    }
}

template<typename K, typename V>
hash_map<K, V>& hash_map<K, V>::operator=(const hash_map &other) {
    if (this != &other) {
        delete[] _head;
        _capacity = other._capacity;
        _size = other._size;
        _upper_load_factor = other._upper_load_factor;
        _lower_load_factor = other._lower_load_factor;
        capacity_index = other.capacity_index;
        _head = new hash_list<K, V>[_capacity];
        for (size_t i = 0; i < _capacity; ++i) {
            _head[i] = other._head[i]; 
        }
    }
    return *this;
}

template<typename K, typename V>
void hash_map<K, V>::insert(K key, V value) {
    size_t index = _hash(key) % _capacity;
    _head[index].insert(key, value); 
    _size++;
    
}

template<typename K, typename V> std::optional<V> hash_map<K,V>::get_value(K key) const
{
    size_t index_hash = _hash(key) % _capacity;
    if(_head[index_hash].get_value(key).has_value())
    {
        return _head[index_hash].get_value(key);
    }
    return std::nullopt;
}

template<typename K, typename V>
bool hash_map<K, V>::remove(K key) {
    size_t index = _hash(key) % _capacity;
    if (_head[index].remove(key)) {
        _size--;
        return true;
    }
    return false;
}

template<typename K, typename V> size_t hash_map<K,V>::get_size() const 
{
    return _size;
}

template<typename K, typename V> size_t hash_map<K,V>::get_capacity() const
{
    return _capacity;
}

template<typename K, typename V> void hash_map<K,V>::get_all_keys(K *keys)
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

template<typename K, typename V>
void hash_map<K, V>::get_all_sorted_keys(K *keys) {
    get_all_keys(keys);
    std::sort(keys, keys + _size); 
}

template<typename K, typename V> void hash_map<K,V>::get_bucket_sizes(size_t *buckets)
{
    for (size_t i = 0; i < _capacity; ++i) {
        buckets[i] = _head[i].get_size();
    }
}

template<typename K, typename V> hash_map<K,V>::~hash_map() {
    delete[] _head;
}
