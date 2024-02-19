
#include "hash_map.h"

#include <iostream>
#include <cmath>


template<typename K, typename V>
hash_map<K, V>::hash_map(size_t initial_capacity,
                         float upper_load_factor,
                         float lower_load_factor)
    : _upper_load_factor(upper_load_factor), _lower_load_factor(lower_load_factor), _size(0), capacity_index(0) {
    
    _capacity = _capacities[0];
    
    _head = new hash_list<K, V>[_capacity];
}

template<typename K, typename V>
hash_map<K, V>::hash_map(const hash_map &other)
    : _size(other._size), _capacity(other._capacity),
      _upper_load_factor(other._upper_load_factor), _lower_load_factor(other._lower_load_factor),
      capacity_index(other.capacity_index) {
    _head = new hash_list<K, V>[_capacity];
    for (size_t i = 0; i < _capacity; i++) {
        _head[i] = other._head[i];
    }
}

template<typename K, typename V>
hash_map<K, V>& hash_map<K, V>::operator=(const hash_map &other) {
    if (this != &other) {
        delete[] _head;

        _size = other._size;
        _capacity = other._capacity;
        _upper_load_factor = other._upper_load_factor;
        _lower_load_factor = other._lower_load_factor;
        capacity_index = other.capacity_index;

        _head = new hash_list<K, V>[_capacity];
        for (size_t i = 0; i < _capacity; i++) {
            _head[i] = other._head[i];
        }
    }
    return *this;
}


template<typename K, typename V>
void hash_map<K, V>::insert(K key, V value) {
    auto index = _hash(key) % _capacity;
    size_t oldSize = _head[index].get_size(); 
    _head[index].insert(key, value);
    size_t newSize = _head[index].get_size(); 


    if (newSize > oldSize) {
        _size++;
    }


    if (static_cast<float>(_size) / _capacity > _upper_load_factor) {
        rehash();
    }
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
void hash_map<K, V>::rehash() {
    size_t new_capacity_index = capacity_index;
   
    if (_size > _upper_load_factor * _capacity) {
        new_capacity_index++;
    } else if (_size < _lower_load_factor * _capacity) {
        new_capacity_index--;
    }


    if (new_capacity_index == capacity_index) {
        return;
    }

    auto new_capacity = _capacities[new_capacity_index];
    auto new_head = new hash_list<K, V>[new_capacity];


    for (size_t i = 0; i < _capacity; ++i) {
        _head[i].reset_iter();
        while (!_head[i].iter_at_end()) {
            auto iter_value = _head[i].get_iter_value();
            if (iter_value) {
                const K* key_ptr = iter_value->first;
                V* value_ptr = iter_value->second;
                size_t new_index = _hash(*key_ptr) % new_capacity;
                new_head[new_index].insert(*key_ptr, *value_ptr);
            }
            _head[i].increment_iter();
        }
    }


    delete[] _head;
    _head = new_head;
    _capacity = new_capacity;
    capacity_index = new_capacity_index;
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
