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
        p("Write Int\n");
        memcpy(buffer+pos_, &i, sizeof(int));

        pos_+= sizeof(int);
        std::cout<< pos_<<std::endl;
//        std::cout<<buffer<<std::endl;
        assert(pos_<= DATA_MAX);
    }
    void write(float f){
        memcpy(buffer+pos_, &f, sizeof(float));
//        std::cout<< sizeof(double)<<std::endl;
        pos_+= sizeof(float);
        std::cout<< pos_<<std::endl;
//        std::cout<<buffer<<std::endl;
        assert(pos_<= DATA_MAX);
    }
    void write(bool b){
        p("Write Bool\n");
        memcpy(buffer+pos_, &b, sizeof(bool));
        pos_+= sizeof(bool);
        std::cout<< "here929182"<<pos_<<std::endl;
//        std::cout<< sizeof(bool)<<std::endl;
//        std::cout<<buffer<<std::endl;
        assert(pos_<= DATA_MAX);
    }
    void write(String* s){
        size_t size = s->size(); // number of characters excluding terminate (\0)
        char *cstr = s->c_str();
        memcpy(buffer + pos_, &size, sizeof(size));
        pos_ += sizeof(size);

        memcpy(buffer+pos_, cstr, size);
        pos_ += size;
        pos_+= sizeof(size);
        assert(pos_<= DATA_MAX);
//        memcpy(buffer+pos_, cstr, size);
//        pos_+= size;
//        assert(pos_<= DATA_MAX);
    }
    void write(StringArray sa){
        ObjectArray oa = sa._array;
        memcpy(buffer+pos_, &oa.data_, sizeof(oa.data_));
        pos_ += sizeof(oa.data_);
        assert(pos_<= DATA_MAX);
        // capacity
        memcpy(buffer + pos_, &oa.capacity_, sizeof(oa.capacity_));
        pos_ += sizeof(oa.capacity_);
        assert(pos_<= DATA_MAX);
        // length
        memcpy(buffer+ pos_, &oa.length_, sizeof(oa.length_));
        pos_ += sizeof(oa.length_);
        assert(pos_<= DATA_MAX);
    }

    void write(FloatArray fa){
        memcpy(buffer+pos_, &fa.data_, sizeof(fa.data_));
        pos_ += sizeof(fa.data_);
        assert(pos_<= DATA_MAX);
        // capacity
        memcpy(buffer + pos_, &fa.capacity_, fa.capacity_);
        pos_ += sizeof(fa.capacity_);
        assert(pos_<= DATA_MAX);
        // length
        memcpy(buffer+ pos_, &fa.length_, fa.length_);
        pos_ += sizeof(fa.length_);
        assert(pos_<= DATA_MAX);
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
