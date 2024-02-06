#include "hash_list.h"
#include <iostream>

hash_list::hash_list() :size(0), head(nullptr),iter_ptr(nullptr) {}

/**-----------------------------------------------------------------------------------
 * START Part 1
 *------------------------------------------------------------------------------------*/

void hash_list::insert(int key, float value) {
    node* local_head = head;
    
    // if set is empty
    if (local_head == nullptr){
        node* new_node = new node;
        local_head = new_node;
        local_head->key = key;
        local_head->value = value;
        local_head->next = nullptr;
        head = local_head;
        size = 1;
    }
    else
    {
        node* prev_local;
        while(local_head != nullptr)
        {
            if(local_head->key == key)
            {
                local_head->value = value;
                return;
            }
            prev_local = local_head;
            local_head = local_head->next;
 
        }
        node* new_node = new node;
        local_head = new_node;
        prev_local->next = local_head;
        local_head->key = key;
        local_head->value = value;
        
        local_head->next = nullptr;
        this->size = this->size + 1;
        
        
    }
    
}

std::optional<float> hash_list::get_value(int key) const 
{ 
    node *current = head;
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

bool hash_list::remove(int key) 
{ 
    if(this->head == nullptr)
    {
        return false;
    }
   
    if(this->head->key == key)
    {
        node* delete_node = this->head;
        this->head = this->head->next;
        size = size - 1;
        delete delete_node;
        return true;
    }
    node* local_node = this->head;
    while(local_node->next != nullptr)
    {
        if(local_node->next->key == key)
        {
            node * delete_node = local_node->next;
            local_node->next = delete_node->next;
            size = size - 1;
            delete delete_node;
            return true;
        }
        local_node = local_node->next;
    }
    
    return false;
}

size_t hash_list::get_size() const 
{ 
    return size;
}

hash_list::~hash_list() 
{
    node * local_node = this->head;
    node * del_node = nullptr;
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

hash_list::hash_list(const hash_list &other){
    size = 0;
    head = nullptr;
    iter_ptr = nullptr;
    node* current = other.head;
    while (current != nullptr) {
        this->insert(current->key, current->value);
        current = current->next;
    }
}

hash_list &hash_list::operator=(const hash_list &other) 
{ 
    if(this == &other){
        return *this;
    }
    node *curr = head;
    while (curr != nullptr) {
        node *next = curr->next;
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

void hash_list::reset_iter() { 
    if(size == 0){
        iter_ptr = nullptr;
    }
    else{
        iter_ptr = head;
    }
}


void hash_list::increment_iter() {
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


std::optional<std::pair<const int *, float *>> hash_list::get_iter_value() 
{ 
    if(iter_ptr!=nullptr)
    {
        return std::make_pair(&(iter_ptr->key), &(iter_ptr->value));
    }
    return std::nullopt; 
}


bool hash_list::iter_at_end() { 
    if(iter_ptr == nullptr)
    {
        return true;
    }
    return false; }
/**-----------------------------------------------------------------------------------
 * END Part 2
 *------------------------------------------------------------------------------------*/
