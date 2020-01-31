//
// Authors: Neil Resnik (resnik.n@husky.neu.edu) & Yifei Wang (wang3.yi@husky.neu.edu)
//

#ifndef A2_HASHMAP_H
#define A2_HASHMAP_H

#include <iostream>
#include "object.h"
#include "string.h"

using namespace std;

/**
 * HashPair represents a Key - Value pair in the hashmap
 *
 * Authors: Neil Resnik (resnik.n@husky.neu.edu) & Yifei Wang (wang3.yi@husky.neu.edu)
 */
class HashPair {

public:
    Object *key_; // Pointer to the key object
    Object *value_; // Pointer to the value object
    HashPair *next_; // Point to the next HashPair in the singly-linked list

    /**
     * Constructs a hashpair
     *
     * With the given key, value, and next.
     */
    HashPair(Object *key, Object *value, HashPair *next) : key_(key), value_(value), next_(next) {}

    /**
     * Constructs a hashpair
     * With the given key, value, and next
     */
    HashPair(Object *key, Object *value) : key_(key), value_(value), next_(nullptr) {}

    /**
     * Default Constructor, this constructs a hashpair
     * With nullptr, for key, value, and next
     */
    HashPair() : key_(nullptr), value_(nullptr), next_(nullptr) {}

    /** Compare the key with other new key */
    bool compareKey(Object *other){
        if(!key_) return key_ == other;
        return this->key_->equals(other);
    }

    /** get the key of this Hashpair */
    Object *getKey(){
        return this->key_;
    }

    /** get the value of this Hashpair */
    Object *getValue(){
        return this->value_;
    }

    /** get the next of this Hashpair */
    HashPair *getNext(){
        return next_;
    }

    /** set the next to be the input*/
    void setNext(HashPair *next){
        this->next_ = next;
    }
};

/**
 * This is the Hashmap, using Hashpairs to construct a Map
 * The map keep tracks of the size, length and the Hashpair*/
class Map : public Object {
public:
    size_t size_;
    size_t arr_len_;
    HashPair **map_;

    /**
     * Constructs a map
     * With the size, capacity and the Map;
     */
    Map() : size_(0), arr_len_(10), map_(nullptr) {
        map_ = new HashPair*[arr_len_];
        for(size_t i = 0; i < arr_len_; ++i){
            map_[i] = nullptr;
        }
    }

    /**
     * This is the Deconstructor of Map
     */
    ~Map() {
        this->clear();
        delete[] map_;
    }

    /**
     * Rehash class re-assign the values from the old map to the new map after changing the size.
     */
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

    /**
     * give the key an index to hash
     */
    size_t hash_index_(Object *key) {
        if (key) {
            return key->hash() % arr_len_;
        }
        return 0;
    }

    /**
     * add the key and value into a map and extends it if needed.
     * @param key  the key that inputs give
     * @param value the value that inputs give
     */
    void put(Object *key, Object *value) {
        if (!key|| !value) {
            return;
        }
        if(size_ + 1 > 2 * arr_len_){
            rehash_();
        }
        HashPair *new_hp = new HashPair(key, value);
        size_t index = hash_index_(key);
        new_hp->setNext(map_[index]);
        map_[index] = new_hp;
        size_++;
    }

    /**
     * Get the key and return the value, if the value is not found, return nullptr
     * @param key the key is provided
     * @return the value that is founded
     */
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

    /**
     * Remove the item from the HashMap by finding it's key first and delete both the key and the value.
     * @param key the key we need to find
     * @return the value that is being removed
     */
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
    /**
     * Return the size of the Map
     * @return the size of the map
     */
    size_t size() {
        return this->size_;
    }

    /**
     * If the current has this key
     * @param key the key is provided to as
     * @return return the boolean if the map has the key return true, else return false
     */
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

/**
 * This is a class just to be clarified if when the input storage is a String
 * When the input is String as an object, the method should do same thing, but take the String as the data type
 */
class StringMap : public Object {
public:
    Map internal_map_;
    /**
     * Constructor of String map
     */
    StringMap() : internal_map_() {}

    virtual ~StringMap(){}

    /**
    * If the current has this key
    * @param key the key is provided to as
    * @return return the boolean if the map has the key return true, else return false
    */
    bool has_key(String *key){
        return internal_map_.has_key(key);
    }

    /**
     * Get the key and return the value, if the value is not found, return nullptr
     * @param key the key is provided
     * @return the value that is founded
     */
    String *get(String *key){
        return static_cast<String*>(internal_map_.get(key));
    }

    /**
     * add the key and value into a map and extends it if needed.
     * @param key  the key that inputs give
     * @param value the value that inputs give
     */
    void put(String *key, String *value){
        internal_map_.put(key, value);
    }

    /**
     * Remove the item from the HashMap by finding it's key first and delete both the key and the value.
     * @param key the key we need to find
     * @return the value that is being removed
     */
    String *remove(String *key){
        return static_cast<String*>(internal_map_.remove(key));
    }

    /**
     * Return the size of the Map
     * @return the size of the map
     */
    size_t size(){
        return internal_map_.size();
    }
};

#endif //A2_HASHMAP_H
