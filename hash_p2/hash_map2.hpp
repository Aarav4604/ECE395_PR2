#include "hash_map.h"

#include <iostream>
#include <cmath>


hash_map::hash_map(size_t capacity, float upper_load_factor, float lower_load_factor){
    _size = 0; 
    _capacity = capacity; 
    _lower_load_factor = lower_load_factor;
    _upper_load_factor = upper_load_factor;
    _head = new hash_list[capacity];
}


hash_map<K,V>::hashmap(const hash_map &other)
{

}

template<typename K, typename V> hash_map &hash_map<K,V>::operator=(const hash_map &other)
{

}

template<typename K, typename V> void hash_map<K,V>::insert(K key, V value)
{

}

template<typename K, typename V> std::optional<V> hash_map<K,V>::get_value(K key) const
{

}

template<typename K, typename V> bool hash_map<K,V>::remove(K key)
{

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

}

template<typename K, typename V> void hash_map<K,V>::get_all_sorted_keys(K *keys)
{

}

template<typename K, typename V> void hash_map<K,V>::get_bucket_sizes(size_t *buckets)
{

}

template<typename K, typename V> hash_map<K,V>::~hash_map() {
    delete[] _head;
}
