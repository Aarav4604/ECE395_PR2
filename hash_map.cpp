#include "hash_map.h"

#include <iostream>
#include <cmath>

hash_map::hash_map(size_t capacity){
    _size = 0; 
    _capacity = capacity; 
    _head = new hash_list[capacity];
}


hash_map::hash_map(const hash_map &other){

}

hash_map& hash_map:: operator=(const hash_map &other){

}

void hash_map::insert(int key, float value) {
}

std::optional<float> hash_map::get_value(int key) const {
}

bool hash_map::remove(int key){

}

size_t hash_map::get_size() const {
    return _size;
}


size_t hash_map::get_capacity() const {
    return _capacity;
}

void hash_map::get_all_keys(int *keys) {
}

void hash_map::get_bucket_sizes(size_t *buckets) {
    for (size_t i = 0; i < _capacity; ++i) {
        buckets[i] = _head[i].get_size();
    }
}

hash_map::~hash_map() {
    delete[] _head;
}

