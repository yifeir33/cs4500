//
// Created by 王镱霏 on 1/27/20.
//

#ifndef A2_HASHMAP_H
#define A2_HASHMAP_H

#include <iostream>
#include "Object.h"
#include "String.h"

using namespace std;

class HashPair {

public:
    HashPair(Object *key, Object *value) {
        this->key_ = key;
        this->value_ = value;
    }

    Object *key_;
    Object *value_;
    HashPair(){
        this->key_ = nullptr;
        this->value_ = nullptr;
    }

    ~HashPair() {
        delete key_;
        delete value_;
    }

};

class Map : public Object {
    int size_;
    int capacity_;
    HashPair ***map;
public:
    Map() : size_(0), capacity_(10), map() {
        this->map = new HashPair **[capacity_];
        initialize();
    }

    ~Map() {
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
        for(int i =0; i< this->size_+1; i++ ){

//            for(int j =0;j <this->size_+1; j++){
//                HashPair* hp = this->map[i][j];
//                delete hp;
//            }
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
//        std::cout<<this->capacity_<<std::endl;
//        std::cout<<this->map[0][0]->key_<<std::endl;
        HashPair *pair = new HashPair(key, value);
//        std::cout<<"newpair"<<std::endl;
        int hash_val = hash_index(key);
        HashPair **select_data = map[hash_val];
//        std::cout<<"newpair1"<<std::endl;

        for (int i = 0; i < this->capacity_; i++) {
//            std::cout<<"newpair2"<<std::endl;
            if (select_data[i] == nullptr) {
//                std::cout<<"newpair3"<<std::endl;
//                std::cout<<"current i:"<<i<<std::endl;
                select_data[i] = pair;
//                std::cout<<"current i:"<<i<<std::endl;
                break;
            }
        }
        size_++;
//        std::cout<<"finish??"<<std::endl;

    }

    Object *get(Object *key) {

        int select_index = hash_index(key);
        for (int i = 0; i < size_; i++) {
            if(map[select_index][i] != nullptr){
//                String* temp_str = helper_cast(map[select_index][i]->key_);
                if(map[select_index][i]->key_ != nullptr ){
                    if (key->equals(map[select_index][i]->key_)) {
                        return map[select_index][i]->value_;
                    }
                }
            }

        }
        return nullptr;
    }



    Object* remove(Object *key) {
        Object* removed;
        int h_index = hash_index(key);
        HashPair **select_array = map[h_index];
//        String *key1 = helper_cast(key);
//        if (key1 == nullptr) {
//            std::cout << "this string can not be nullptr!" << h_index << std::endl;
//            exit(1);
//        }
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

//            String *key2 = helper_cast(key_temp);

            if (key->equals(key_temp)) {
                removed = select_array[sofar]->value_;
                select_array[sofar] = nullptr;
                break;
            }


            sofar++;
            selected = select_array[sofar];
        }
        size_ = size_ - 1;
        return removed;
    }

    size_t size() {
        return this->size_;
    }

    Object **getKeys() {
        Object **keys;
        int sofar = 0;
        keys = new Object *[this->size_+1];
        for (int i = 0; i < capacity_; i++) {
            if (map[i] != nullptr) {

                for (int j = 0; j < capacity_; j++) {

                    if (sofar < size_) {

                        HashPair* cur = map[i][j];
                        if(cur != nullptr){
                            keys[sofar] = cur->key_;
                        }


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
        values = new Object *[this->size_+1];
        for (int i = 0; i < capacity_; i++) {
            if (map[i] != nullptr) {
                for (int j = 0; j < capacity_; j++) {
                    if (sofar < size_) {

                        HashPair* cur = map[i][j];
                        if(cur != nullptr){
                            values[sofar] = cur->value_;
                        }


                    }
                    sofar++;
                }
            } else {
                std::cout << "map[i] cant be nullptr" << std::endl;
            }
        }
        return values;

    }


    virtual void _ensure_size(int required) {

        if (required >= this->capacity_) {

            int newCap = this->capacity_ * 2;
            while (required > newCap) {
                newCap *= 2;
            }

            //build new
            HashPair*** new_map = new HashPair** [newCap];

            for (int i = 0; i < newCap; ++i) {
                HashPair** hp =  new HashPair*[newCap];
                new_map[i] = hp;
                for (int j = 0; j < newCap; ++j) {
                    new_map[i][j] = nullptr;
                }
            }
            //copy from past
            for (int i = 0; i < capacity_; i++) {
                for (int j = 0; j < capacity_; j++) {

//                    std::cout<<"current i:"<<i<<std::endl;
//                    std::cout<<"current j:"<<j<<std::endl;

                    if (map[i][j] != nullptr) {

                        int index_i = map[i][j]->key_->hash() % (newCap - 1);
//                        std::cout<<"index_i:"<< index_i<<std::endl;
//                          HashPair** subarray2 = new_map[index_i];
                        for (int k = 0; k < capacity_; k++) {
                            if (new_map[index_i][k] == nullptr) {
                                new_map[index_i][k] = map[i][j];
                            }
                        }

                    }
                }
            }



// delete old map
            for (int k = 0; k < capacity_; k++) {

//                for(int l =0; l < capacity_; l++){
//                    delete map[k][l];
//                    map[k][l] = nullptr;
//                }
                delete[] map[k];
            }
            delete [] map;


            this->capacity_ = newCap;
            this->map = new_map;
            this->size_ = size();

//            for (int k = 0; k < capacity_; k++) {
//
//                for(int l =0; l < capacity_; l++){
//
//                    new_map[k][l] = nullptr;
//                }
//                delete[] new_map[k];
//            }
//            delete [] new_map;


        }
    }

    String *helper_cast(Object *o) {
        return dynamic_cast<String *>(o);
    }

    bool has_key(Object* key) {
        int h_index = hash_index(key);
        HashPair **select_array = map[h_index];
//        String *key1 = helper_cast(key);
        if (key == nullptr) {
            std::cout << "this key can not be nullptr!" << h_index << std::endl;
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

//            String *key2 = helper_cast(key_temp);

            if (key->equals(key_temp)) {

                return true;
            }

            sofar++;
            selected = select_array[sofar];
        }
        return false;
    }


};

#endif //A2_HASHMAP_H
