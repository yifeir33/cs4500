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
    HashPair(Object *key, Object *value) {
        this->key_ = key;
        this->value_ = value;
    }

    Object *key_;
    Object *value_;

     ~HashPair() {
        delete key_;
        delete value_;
    }

};

class HashMap : public Object {
    int size_;
    int capacity_;
    HashPair ***map;
public:
    HashMap() : size_(0), capacity_(10), map() {
        this->map = new HashPair **[capacity_];
        initialize();
    }

    ~HashMap() {
        this->clear();
        delete [] map;
    }

    void initialize() {
        this->_ensure_size(this->size());
        for (int i = 0; i < this->capacity_; ++i) {
            HashPair** hp =  new HashPair*[this->capacity_];
            map[i] = hp;
            for (int j = 0; j < this->capacity_; ++j) {
                map[i][j] = nullptr;
            }
        }
    }

    //Removes all the elements from the list
    void clear(){
        for(int i =0; i< size_+1; i++ ){

            for(int j =0;j <size_+1; j++){
                delete this->map[i][j];
                this->map[i][j] = nullptr;
            }
            delete [] map[i];

        }
        size_ =0;
    }

    int hash_index(Object *key) {
        if (key) {
            return key->hash() % (capacity_ - 1);
        }
        return -1;

    }

    void put(Object *key, Object *value) {
        if (key == nullptr || value == nullptr) {
            return;
        }
        this->_ensure_size(size_ + 1);
        //check capacity enough
        std::cout<<"okensuresize"<<std::endl;
//        std::cout<<this->capacity_<<std::endl;
//        std::cout<<this->map[0][0]->key_<<std::endl;
//        std::cout<<"here"<<std::endl;
        HashPair *pair = new HashPair(key, value);
//        std::cout<<"newpair"<<std::endl;
        int hash_val = hash_index(key);
        HashPair **select_data = map[hash_val];
//        std::cout<<"newpair1"<<std::endl;
        std::cout<<"capacity now:"<< this->capacity_<<std::endl;
        for (int i = 0; i < this->capacity_; i++) {
//            std::cout<<"newpair2"<<std::endl;
            if (select_data[i] == nullptr) {
//                std::cout<<"newpair3"<<std::endl;
                std::cout<<"current i:"<<i<<std::endl;
                select_data[i] = pair;
                std::cout<<"current i:"<<i<<std::endl;
                break;
            }
        }
        size_++;
        std::cout<<"finish??"<<std::endl;

    }

    Object *get(Object *key) {
        Object **keys = this->getKeys();
        Object **vals = this->getValues();
        for (int selected = 0; selected < size_; selected++) {
            if (keys[selected]->equals(key)) {
                return vals[selected];
            }
        }

        std::cout << "Not able to find Object" << std::endl;
        exit(1);

    }

    void remove(Object *key) {
        int h_index = hash_index(key);
        HashPair **select_array = map[h_index];
        String *key1 = helper_cast(key);
        if (key1 == nullptr) {
            std::cout << "this string can not be nullptr!" << h_index << std::endl;
            exit(1);
        }
        if (select_array == nullptr) {
            std::cout << "this array can not be nullptr!" << h_index << std::endl;
            exit(1);
        }
        int sofar = 0;
        HashPair *selected = select_array[sofar];
        while (selected != nullptr) {

            Object *key_temp = selected->key_;

            if (key_temp == nullptr) {
                std::cout << "this object can not be nullptr!" << h_index << std::endl;
                exit(1);
            }

            String *key2 = helper_cast(key_temp);

            if (key1->equals(key2)) {

                select_array[sofar] = nullptr;
                break;
            }


            sofar++;
            selected = select_array[sofar];
        }
        size_ = size_ - 1;
    }

    int size() {
        return this->size_;
    }

    Object **getKeys() {
        Object **keys;
        int sofar = 0;
        keys = new Object *[size_];
        for (int i = 0; i < capacity_; i++) {
            if (map[i] != nullptr) {
                for (int j = 0; j < capacity_; j++) {
                    if (sofar < size_) {
                        keys[sofar] = map[i][j]->key_;
                    }
                    sofar++;
                }
            } else {
                std::cout << "map[i] cant be nullptr" << std::endl;
            }
        }
        return keys;
    }

    Object **getValues() {
        Object **values;
        int sofar = 0;
        values = new Object *[size_];
        for (int i = 0; i < capacity_; i++) {
            if (map[i] != nullptr) {
                for (int j = 0; j < capacity_; j++) {
                    if (sofar < size_) {
                        values[sofar] = map[i][j]->value_;
                    }
                }
            } else {
                std::cout << "map[i] cant be nullptr" << std::endl;
            }
        }
        return values;

    }

    bool isEmpty() {
        for (int i = 0; i < capacity_; i++) {
            if (map[i] != nullptr) {
                HashPair **hp = map[i];
                for (int j = 0; j < capacity_; j++) {
                    if (hp[j] != nullptr) {
                        return false;
                    }
                }
            } else {
                std::cout << "map[i] cant be nullptr" << std::endl;
            }
        }
        return true;

    }

    virtual void _ensure_size(int required) {

        if (required >= this->capacity_) {

            int newCap = this->capacity_ * 2;
            while (required > newCap) {
                newCap *= 2;
            }

            HashPair*** new_map = new HashPair** [newCap] ;
            //copy from past
            std::cout<<"again here100"<<std::endl;
            for (int i = 0; i < capacity_; i++) {
                for (int j = 0; j < capacity_; j++) {
                    std::cout<<"again here1000"<<std::endl;
                    std::cout<<"current i:"<<i<<std::endl;
                    std::cout<<"current j:"<<j<<std::endl;
                    HashPair *cur = map[i][j];
                    if (cur != nullptr) {
                        std::cout<<"again here100000"<<std::endl;
                        int index_i = cur->key_->hash() % (newCap - 1);
                        std::cout<<"here1000009090"<<std::endl;
                        if(new_map[index_i] == nullptr){
                                HashPair** subarray = new HashPair*[newCap];
                                subarray[0] = cur;
                                new_map[index_i] = subarray;
                            } else{
                            HashPair** subarray2 = new_map[index_i];
                            for(int k = 0; k< capacity_; k++){
                                if(subarray2[k] == nullptr){
                                    subarray2[k] = cur;
                                }
                            }
                        }

                    }
                }
            }
            std::cout<<"here1000001"<<std::endl;

            //fill in the blanks
            for(int p = 0; p< newCap; p++){
                if(new_map[p] == nullptr){
                    new_map[p] = new HashPair*[newCap];
                    for (int m = 0; m<newCap; m++){
                        new_map[p][m] = nullptr;
                    }
                }
            }
//
// delete old map
            for (int k = 0; k < capacity_; k++) {
//                std::cout<<"here1000003"<<std::endl;
//                for(int l =0; l < capacity_; l++){
//                    std::cout<<"here1000004"<<std::endl;
//                        delete map[k][l];
//                }
                delete[] map[k];
            }
            delete [] map;


            this->capacity_ = newCap;
            this->map = new_map;
            this->size_ = size();
            std::cout<<"here1000002sasas"<<std::endl;
        }
    }

    String *helper_cast(Object *o) {
        return dynamic_cast<String *>(o);
    }


};

#endif //A2_HASHMAP_H
