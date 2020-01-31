//
// Created by 王镱霏 on 1/13/20.
//

#ifndef HW2_STRING_H
#define HW2_STRING_H


#include <stdlib.h>
#include "Object.h"

class String : public Object {
public:
    char* val_; //data is owned by the string
    size_t size_;

 String(const char* c) {
     this->size_ = strlen(c);
     this->val_ = new char[size_];
        for (size_t i =0; i< size_; i++){
            this->val_[i] = c[i];
        }
    }
    String(){
        this->val_ = new char[1];
        this->val_[0] = '\0';

 }

    size_t hash_me_(){
        size_t  res =0;
        for(size_t i = 0; i < size_; i ++){
            res += val_[i] + (res << 5);
        }
        return res;
    }

    bool equals(Object * other) {
        if (other == nullptr) return false;
        String *s = dynamic_cast<String*>(other);
        if (s == nullptr) return false;
        return strcmp(this->val_, s->val_) == 0;
    }

    String* concat(String* o){
     char * new_array = new char[strlen(this->val_)+strlen(o->val_)+1];
     strcpy(new_array, this->val_);
     strcat(new_array, o->val_);
     String* new_string = new String(new_array);
     return new_string;

 }
     //alphabetically increasing  >0 front  <0 behind
     virtual int Compare(String* other){

         return strcmp(this->val_, other->val_);
     }

    ~String() {
        delete[] val_;
    }
};
#endif //HW2_STRING_H