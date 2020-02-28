//
// Created by 王镱霏 on 2/26/20.
//

#include "array.h"
#include <netinet/in.h>
#ifndef ASSIGNMENT6_SERIALIZER_H
#define ASSIGNMENT6_SERIALIZER_H

#define DATA_MAX        256

class Serializer: public Object {
    char* buffer = new char[DATA_MAX];
    size_t pos_;
public: Serializer(): pos_(0){
    }
    ~Serializer(){
        delete[]  buffer;
    }
    void write(int i){
        memcpy(buffer+pos_, &i, sizeof(int));
//        std::cout<< sizeof(int)<<std::endl;
        pos_+= sizeof(int);
//        std::cout<<buffer<<std::endl;
        assert(pos_<= DATA_MAX);
    }
    void write(double d){
        memcpy(buffer+pos_, &d, sizeof(double));
//        std::cout<< sizeof(double)<<std::endl;
        pos_+= sizeof(double);
//        std::cout<<buffer<<std::endl;
        assert(pos_<= DATA_MAX);
    }
    void write(bool b){
        memcpy(buffer+pos_, &b, sizeof(bool));
        pos_+= sizeof(bool);
//        std::cout<< sizeof(bool)<<std::endl;
//        std::cout<<buffer<<std::endl;
        assert(pos_<= DATA_MAX);
    }
    void write(String* s){
        size_t size = s->size(); // number of characters excluding terminate (\0)
        char *cstr = s->c_str();
        memcpy(buffer+pos_, &size, sizeof(size));
        pos_+= sizeof(size);
        assert(pos_<= DATA_MAX);
        memcpy(buffer+pos_, cstr, size);
        pos_+= size;
        assert(pos_<= DATA_MAX);
    }
    void write(StringArray sa){
        ObjectArray oa = sa._array;
        size_t pos = 0;
        memcpy(buffer+pos, &oa.data_, sizeof(oa.data_));
        pos += sizeof(oa.data_);
        assert(pos<= DATA_MAX);
        // capacity
        memcpy(buffer + pos, &oa.capacity_, sizeof(oa.capacity_));
        pos += sizeof(oa.capacity_);
        assert(pos<= DATA_MAX);
        // length
        memcpy(buffer+ pos, &oa.capacity_, sizeof(oa.length_));
        pos += sizeof(oa.length_);
        assert(pos<= DATA_MAX);
    }

    void write(FloatArray fa){
        size_t pos = 0;
        memcpy(buffer+pos, &fa.data_, sizeof(fa.data_));
        pos += sizeof(fa.data_);
        assert(pos<= DATA_MAX);
        // capacity
        memcpy(buffer + pos, &fa.capacity_, sizeof(fa.capacity_));
        pos += sizeof(fa.capacity_);
        assert(pos<= DATA_MAX);
        // length
        memcpy(buffer+ pos, &fa.capacity_, sizeof(fa.length_));
        pos += sizeof(fa.length_);
        assert(pos<= DATA_MAX);
    }

    void write(sockaddr_in sai){
        memcpy(buffer, &sai , sizeof(sai));
        assert(sizeof(sai)<= DATA_MAX);
    }

    char* get(){
        return buffer;
    }

    void reset(){
        memset(buffer, 0, DATA_MAX);
    }

};


#endif //ASSIGNMENT6_SERIALIZER_H
