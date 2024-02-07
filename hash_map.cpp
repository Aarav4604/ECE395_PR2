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

}

void hash_map::insert(int key, float value) 
{
    int index_hash = abs(key) % _capacity;
    int temp_size = _head[index_hash].get_size();
    _head[index_hash].insert(key, value);

    if(temp_size != _head[index_hash].get_size())
    {
        _size = _size + 1;
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
    int index = abs(key) % _capacity;
    if(_head[index].remove(key))
    {
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
    

}

void hash_map::get_bucket_sizes(size_t *buckets) {
    for (size_t i = 0; i < _capacity; ++i) {
        buckets[i] = _head[i].get_size();
    }
}

hash_map::~hash_map() {
    delete[] _head;
}

