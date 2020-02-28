//
// Created by 王镱霏 on 2/27/20.
//

#include "Serializer.h"
#include "Deserializer.h"

#ifndef ASSIGNMENT6_PRIMITIVE_SERILIZE_H
#define ASSIGNMENT6_PRIMITIVE_SERILIZE_H

#define DATA_MAX        256

//This is a class
class Primitive_Serialize{
    float f;
    bool b;
    int i;

public:Primitive_Serialize():f(0.0),b((bool)0), i(0){
    }

public:Primitive_Serialize(float f_i, bool b_i, int i_i):f(f_i),b(b_i),i(i_i){
    }
    char* serialize(Serializer s){
        s.write(f);
        s.write(b);
        s.write(i);
        return s.get();
    }
    void deserilize(Deserializer ds, char* buffer){
        size_t pos = 0;
        this->i =ds.readInt(buffer+pos, sizeof(this->i));
        pos += sizeof(int);
        this->f =ds.readFloat(buffer+pos,sizeof(this->f));
        pos += sizeof(float);
        this->b =ds.readBool(buffer+pos, sizeof(this->b));
        pos += sizeof(bool);
    }

    float get_float(){
        return f;
    }
    bool get_bool(){
        return b;
    }
    int get_int(){
        return i;
    }
};
#endif //ASSIGNMENT6_PRIMITIVE_SERILIZE_H
