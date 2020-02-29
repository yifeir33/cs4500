//
// Created by 王镱霏 on 2/26/20.
//

#include "array.h"
#include <netinet/in.h>
#ifndef ASSIGNMENT6_SERIALIZER_H
#define ASSIGNMENT6_SERIALIZER_H

#define DATA_MAX        256

class Serializer: public Object {
public:
    char* buffer;
    size_t pos_;

    Serializer(): buffer(new char[DATA_MAX]), pos_(0){}

    ~Serializer(){
        delete[]  buffer;
    }

    size_t length() {
        return pos_;
    }

    void write(int i){
        assert(sizeof(int) <= DATA_MAX - pos_);
        memcpy(buffer+pos_, &i, sizeof(int));
        pos_+= sizeof(int);
    }
    void write(float f){
        assert(sizeof(float) <= DATA_MAX - pos_);
        memcpy(buffer+pos_, &f, sizeof(float));
        pos_+= sizeof(float);
    }
    void write(bool b){
        assert(sizeof(bool) <= DATA_MAX - pos_);
        memcpy(buffer+pos_, &b, sizeof(bool));
        pos_+= sizeof(bool);
    }

    void write(String* s){
        assert(sizeof(size_t) < DATA_MAX - pos_);
        size_t size = s->size(); // number of characters excluding terminate (\0)
        memcpy(buffer + pos_, &size, sizeof(size));
        pos_ += sizeof(size);

        assert(size < DATA_MAX - pos_);
        char *cstr = s->c_str();
        memcpy(buffer + pos_, cstr, size);
        pos_ += size;
    }

    void write(StringArray *sa){
        assert(sizeof(size_t) < DATA_MAX - pos_);
        size_t size = sa->length(); // number of characters excluding terminate (\0)
        memcpy(buffer + pos_, &size, sizeof(size));
        pos_ += sizeof(size);
        for(int i = 0; i < size; ++i){
            this->write(sa->get(i));
        }
    }

    void write(FloatArray *fa){
        assert(sizeof(size_t) < DATA_MAX - pos_);
        size_t size = fa->length(); // number of characters excluding terminate (\0)
        memcpy(buffer + pos_, &size, sizeof(size));
        pos_ += sizeof(size);
        for(int i = 0; i < size; ++i){
            this->write(fa->get(i));
        }
    }

    void write(sockaddr_in sai){
        assert(sizeof(sai) < DATA_MAX - pos_);
        memcpy(buffer, &sai , sizeof(sai));
    }

    char* get(){
        char *ret = new char[DATA_MAX];
        memcpy(ret, buffer, DATA_MAX);
        return ret;
    }

    void reset(){
        memset(buffer, 0, DATA_MAX);
    }

};


#endif //ASSIGNMENT6_SERIALIZER_H
