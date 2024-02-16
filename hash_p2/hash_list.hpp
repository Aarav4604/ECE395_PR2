#include "hash_list.h"
#include <iostream>

template<typename K, typename V> 
hash_list<K,V>::hash_list() : size(0), head(nullptr),iter_ptr(nullptr){}

/**-----------------------------------------------------------------------------------
 * START Part 1
 *------------------------------------------------------------------------------------*/
//We need to implement all the functions as Template
template<typename K, typename V> void hash_list<K,V>::insert(K key, V value) {
    node<K,V>* local_head = head;
    
    // if set is empty
    if(local_head == nullptr){
        node<K,V>* new_node = new node<K,V>;
        local_head = new_node;
        local_head->key = key;
        local_head->value = value;
        local_head->next = nullptr;
        head = local_head;
        size = 1;
    }
    else
    {
        node<K,V>* prev_local;
        while(local_head != nullptr)
        {
            if(local_head->key == key)
            {
                local_head->value = value;
                
            }
            prev_local = local_head;
            local_head = local_head->next;
        }
        node<K,V>* new_node = new node<K,V>;
        local_head = new_node;
        prev_local->next = local_head;
        local_head->key = key;
        local_head->value = value;
        
        local_head->next = nullptr;
        size = size + 1;
        
        
    }
    
}

template<typename K,typename V >std::optional<float> hash_list<K,V>::get_value(K key) const 
{ 
    node<K,V> *current = head;
    while(current != nullptr)
    {
        if(current->key==key)
        {
            
            return current->value;
        }
        current = current->next;
    }     

    return std::nullopt; 
}

template<typename K, typename V> bool hash_list<K,V>::remove(K key) 
{ 
    if(this->head == nullptr)
    {
        return false;
    }
   
    if(this->head->key == key)
    {
        node<K,V>* delete_node = this->head;
        this->head = this->head->next;
        size = size - 1;
        delete delete_node;
        return true;
    }
    node<K,V>* local_node = this->head;
    while(local_node->next != nullptr)
    {
        if(local_node->next->key == key)
        {
            node<K,V> * delete_node = local_node->next;
            local_node->next = delete_node->next;
            size = size - 1;
            delete delete_node;
            return true;
        }
        local_node = local_node->next;
    }
    
    return false;
}

template<typename K, typename V> size_t hash_list<K,V>::get_size() const 
{ 
    return size;
}

template<typename K,typename V>hash_list<K,V>::~hash_list() 
{
    node<K,V> * local_node = this->head;
    node<K,V> * del_node = nullptr;
    while(local_node !=nullptr)
    {
        del_node = local_node;
        local_node = del_node->next;
        delete del_node;
    }
}

/**-----------------------------------------------------------------------------------
 * END Part 1
 *------------------------------------------------------------------------------------*/


/**-----------------------------------------------------------------------------------
 * START Part 2
 *------------------------------------------------------------------------------------*/
// Double Check the code if you don't mind. Let me know if you change something so I can know for what should have been made differently.

template<typename K, typename V >hash_list<K,V>::hash_list(const hash_list &other){
    size = 0;
    head = nullptr;
    iter_ptr = nullptr;
    node<K,V>* current = other.head;
    while (current != nullptr) {
        this->insert(current->key, current->value);
        current = current->next;
    }
}

template<typename K, typename V > hash_list<K,V> &hash_list<K,V>::operator=(const hash_list &other) 
{ 
    if(this == &other){
        return *this;
    }
    node<K,V> *curr = head;
    while (curr != nullptr) {
        node<K,V> *next = curr->next;
        delete curr;
        curr = next;
    }

    head = nullptr;
    size = 0;

    curr = other.head;
    while (curr != nullptr) 
    {
        this->insert(curr->key, curr->value);
        curr = curr->next;
    }

    return *this;
}

template<typename K, typename V > void hash_list<K,V>::reset_iter() { 
    if(size == 0){
        iter_ptr = nullptr;
    }
    else{
        iter_ptr = head;
    }
}


template<typename K, typename V > void hash_list<K,V>::increment_iter() {
    if(iter_ptr == nullptr){
        return;
    }    
    else if(iter_at_end())
    {
        iter_ptr = nullptr;
    }
    else{
        iter_ptr = iter_ptr->next;  
    }
    
}


template<typename K, typename V > 
std::optional<std::pair<const K *, V *>> hash_list<K,V>::get_iter_value() 
{ 
    if(iter_ptr!=nullptr)
    {
        return std::make_pair(&(iter_ptr->key), &(iter_ptr->value));
    }
    return std::nullopt; 
}


template<typename K, typename V > bool hash_list<K,V>::iter_at_end() { 
    if(iter_ptr == nullptr)
    {
        return true;
    }
    return false; }
/**-----------------------------------------------------------------------------------
 * END Part 2
 *------------------------------------------------------------------------------------*/

 