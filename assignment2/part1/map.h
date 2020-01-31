//
// Created by 王镱霏 on 1/27/20.
//

#ifndef A2_HASHMAP_H
#define A2_HASHMAP_H

#include <iostream>
#include "object.h"
#include "string.h"

using namespace std;

class HashPair {

public:
    Object *key_;
    Object *value_;
    HashPair *next_;

    HashPair(Object *key, Object *value, HashPair *next) {
        this->key_ = key;
        this->value_ = value;
        this->next_ = next;
    }

    HashPair(Object *key, Object *value) {
        this->key_ = key;
        this->value_ = value;
        this->next_ = nullptr;
    }

    HashPair(){
        this->key_ = nullptr;
        this->value_ = nullptr;
        this->next_ = nullptr;
    }

    bool compareKey(Object *other){
        if(!key_) return key_ == other;
        return this->key_->equals(other);
    }

    Object *getKey(){
        return this->key_;
    }

    Object *getValue(){
        return this->value_;
    }

    HashPair *getNext(){
        return next_;
    }

    void setNext(HashPair *next){
        this->next_ = next;
    }
};

class Map : public Object {
public:
    size_t size_;
    size_t arr_len_;
    HashPair **map_;

    Map() : size_(0), arr_len_(10), map_(nullptr) {
        map_ = new HashPair*[arr_len_];
        for(size_t i = 0; i < arr_len_; ++i){
            map_[i] = nullptr;
        }
    }

    ~Map() {
        this->clear();
        delete[] map_;
    }

    void rehash_(){
        size_t new_len = arr_len_ * 2;
        HashPair **new_map = new HashPair*[new_len];
        for(size_t i = 0; i < new_len; ++i){
            new_map[i] = nullptr;
        }

        for(size_t i = 0; i < arr_len_; ++i){
            HashPair *hp = map_[i];
            while(hp){
                HashPair *next = hp->getNext();
                size_t new_index = hp->getKey()->hash() % new_len;
                hp->setNext(new_map[new_index]);
                new_map[new_index] = hp;
                hp = next;
            }
            map_[i] = nullptr;
        }

        delete[] map_;
        map_ = new_map;
        arr_len_ = new_len;
    }

    //Removes all the elements from the list
    void clear(){
        for(size_t i = 0; i < arr_len_; ++i){
            HashPair *hp = map_[i];
            while(hp){
                HashPair *next = hp->getNext();
                delete hp;
                hp = next;
            }
            map_[i] = nullptr;
        }
        size_ = 0;
    }

    size_t hash_index_(Object *key) {
        if (key) {
            return key->hash() % arr_len_;
        }
        return -1;

    }

    void put(Object *key, Object *value) {
        if (!key|| !value) {
            return;
        }
        if(size_ + 1 > 2 * arr_len_){
            rehash_();
        }
        HashPair *new_hp = new HashPair(key, value);
        size_t index = hash_index_(key);
        HashPair *hp = map_[index];
        new_hp->setNext(hp);
        map_[index] = new_hp;
        size_++;
    }

    Object *get(Object *key) {
        if(!key){
            return nullptr;
        }
        HashPair *hp = map_[hash_index_(key)];
        while(hp){
            if(hp->compareKey(key)){
                return hp->getValue();
            }
            hp = hp->getNext();
        }
        return nullptr;
    }

    Object* remove(Object *key) {
        if(!key) return nullptr;
        Object *removedValue = nullptr;
        size_t index = hash_index_(key);
        HashPair *hp = map_[index];
        HashPair *prev = nullptr;
        bool found = false;
        while(hp){
            found = hp->compareKey(key);
            if(found){
                break;
            }
            prev = hp;
            hp = hp->getNext();
        }

        if(!hp || !found){
            return nullptr;
        }

        removedValue = hp->getValue();
        if(prev){
            prev->setNext(hp->getNext());
        } else {
            map_[index] = hp->getNext();
        }
        delete hp;
        size_--;
        return removedValue;
    }

    size_t size() {
        return this->size_;
    }

    bool has_key(Object* key) {
        if(!key) return false;
        HashPair *hp = map_[hash_index_(key)];
        while(hp){
            if(hp->compareKey(key)){
                return true;
            }
            hp = hp->getNext();
        }
        return false;
    }
};

class StringMap : public Object {
public:
    Map internal_map_;

    StringMap() : internal_map_() {}

    virtual ~StringMap(){}

    bool has_key(String *key){
        return internal_map_.has_key(key);
    }

    String *get(String *key){
        return static_cast<String*>(internal_map_.get(key));
    }

    void put(String *key, String *value){
        internal_map_.put(key, value);
    }

    String *remove(String *key){
        return static_cast<String*>(internal_map_.remove(key));
    }

    size_t size(){
        return internal_map_.size();
    }
};

#endif //A2_HASHMAP_H
