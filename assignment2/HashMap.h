//
// Created by 王镱霏 on 1/27/20.
//

#ifndef A2_HASHMAP_H
#define A2_HASHMAP_H

#include <iostream>
#include "Object.h"


using namespace std;

class HashPair{

public:
    HashPair(Object* key, Object* value){
        this->key_ = key;
        this->value_ = value;
    }

    Object* key_;
    Object* value_;

    virtual ~HashPair(){
        delete key_;
        delete value_;
    }

};

class HashMap: public Object{
    int size_;
    int capacity_;
    HashPair*** map ;
public:
    HashMap():size_(0),capacity_(10),map(){
        this->map = new HashPair**[capacity_];
        initialize();
    }

    ~HashMap(){
        delete [] map;
    }

    void initialize(){
        for(int i = 0; i < this->capacity_; i++){
            for(int j = 0; j < this->capacity_; j++){
                map[i][j] = nullptr;
            }
        }
    }

    int hash_index(Object* key){
        if(key){
            return key->hash() % (capacity_-1);
        }
        return -1;

    }

    void put(Object* key, Object* value){
        if(key == nullptr || value == nullptr){
            return;
        }
        this->_ensure_size(size_+1);
        //check capacity enough

        HashPair* pair = new HashPair(key,value);
        int hash_val = hash_index(key);
        HashPair** select_data = map[hash_val];
        for(int i= 0; i < this->capacity_; i ++){
            if(select_data[i] == nullptr){
                select_data[i] = pair;
            }
        }
        size_++;

    }

    Object* get(Object *key){
        Object** keys = this->getKeys();
        Object** vals = this->getValues();
        for(int selected = 0; selected <size_; selected++){
            if(keys[selected]->equals(key)){
                return vals[selected];
            }
        }

        std::cout<<"Not able to find Object"<<std::endl;
        exit(1);

    }

    void remove(Object* key){

    }
    int size(){
        return this->size_;
    }

    Object** getKeys(){
        Object** keys;
        int sofar = 0;
        keys = new Object*[size_ ];
        for(int i = 0; i < capacity_ ; i++){
            if(map[i]!= nullptr){
                for(int j = 0; j< capacity_; j++){
                    if(sofar < size_){
                        keys[sofar] = map[i][j]->key_;
                    }
                    sofar++;
                }
            } else {
                std::cout<<"map[i] cant be nullptr"<<std::endl;
            }
        }
        return keys;
    }

    Object** getValues(){
        Object** values;
        int sofar =0;
        values = new Object*[size_];
        for(int i = 0; i < capacity_ ; i++){
            if(map[i]!= nullptr){
                for(int j = 0; j<capacity_; j++){
                    if(sofar < size_){
                        values[sofar] = map[i][j] ->value_;
                    }
                }
            } else {
                std::cout<<"map[i] cant be nullptr"<<std::endl;
            }
        }
        return values;

    }

    bool isEmpty(){
        for(int i = 0; i < capacity_ ; i++){
            if(map[i]!= nullptr){
                for(int j = 0; j<capacity_; j++){
                    if(map[i][j] != nullptr){
                        return false;
                    }
                }
            } else{
                std::cout<<"map[i] cant be nullptr"<<std::endl;
            }
        }
        return true;

    }

    virtual void _ensure_size(int required){
        if(required>= this->capacity_){
            int newCap = this->capacity_ * 2;
            while(required > newCap){
                newCap *= 2;
            }

            HashPair** new_map[newCap];
            int new_size_array[newCap];
            for(int k = 0; k< newCap; k++){
                new_size_array[k] =0;
            }
            for(int i = 0; i < capacity_; i++){
                for(int j = 0; j< capacity_; j++){
                    HashPair* cur = map[i][j];
                    if(cur != nullptr){
                        int index_i = map[i][j]->key_->hash() % (newCap-1);
                        int index_j = new_size_array[index_i];
                        new_map[index_i][index_j] = map[i][j];
                        new_size_array[index_i] = new_size_array[index_i]+1;
                    }
                }
            }

            for(int k =0; k< capacity_;k++){
                delete[] map[k];
            }

            capacity_ = newCap;
            this->map = new_map;
        }
    }




};
#endif //A2_HASHMAP_H
