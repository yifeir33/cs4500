//
// Created by 王镱霏 on 1/13/20.
//

#ifndef HW2_OBJECT_H
#define HW2_OBJECT_H


// lang::CwC
#include <stdlib.h>

class Object {
public:
    size_t hash_;

    Object(){hash_ = 0;}

    size_t hash() {
        if(hash_ ==0)///compute the hash
            hash_ = hash_me_();
        return hash_;
    }

    virtual size_t hash_me_(){
        return reinterpret_cast<size_t>(this);
    }
//    #virtual 就是允许写sub function
    virtual bool equals(Object *other){
        return this == other;
    }
    virtual ~Object() {}
};
#endif //HW2_OBJECT_H