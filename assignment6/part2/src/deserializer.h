#ifndef ASSIGNMENT6_DESERIALIZER_H
#define ASSIGNMENT6_DESERIALIZER_H

#include <netinet/in.h>
#include "string.h"
#include "array.h"
#include "object.h"

#include <cstdlib>

class Deserializer: public Object {
public: 
    char *buffer_;
    size_t length_;
    size_t pos_;

    Deserializer(char *buf, size_t length): buffer_(buf), length_(length), pos_(0){
        assert(buf);
    }

    int readInt(){
        int i = 0;
        assert(sizeof(int)<= length_ - pos_);
        memcpy(&i, buffer_, sizeof(int));
        pos_ += sizeof(int);
        return i;
    }

    float readFloat(){
        float f = 0;
        assert(sizeof(float)<= length_ - pos_);
        memcpy(&f, buffer_, sizeof(float));
        pos_ += sizeof(float);
        return f;
    }

    bool readBool(){
        bool b = false;
        assert(sizeof(bool)<= length_ - pos_);
        memcpy(&b, buffer_, sizeof(bool));
        pos_ += sizeof(bool);
        return b;
    }

    String* readString(){
        size_t size = 0;
        assert(sizeof(size_t) < length_ - pos_);
        memcpy(&size, buffer_ + pos_, sizeof(size_t));
        pos_ += sizeof(size_t);

        assert(size < length_ - pos_);
        char *s_buf = new char[size + 1];
        char *str = buffer_ + pos_;
        for(size_t i = 0; i < size; ++i){
            s_buf[i] = str[i];
            pos_++;
        }
        return new String(true, s_buf, size);
    }

    StringArray *readStringArray(){
        assert(sizeof(size_t) < length_  - pos_);
        size_t alen = 0;
        memcpy(&alen, buffer_, sizeof(size_t));
        pos_ += sizeof(size_t);

        StringArray *sa = new StringArray(alen);
        for(size_t i = 0; i < alen; ++i){
            sa->push(this->readString());
        }
        return sa;
    }

    FloatArray *readFloatArray(){
        assert(sizeof(size_t) < length_  - pos_);
        size_t alen = 0;
        memcpy(&alen, buffer_, sizeof(size_t));
        pos_ += sizeof(size_t);

        FloatArray *fa = new FloatArray(alen);
        for(size_t i = 0; i < alen; ++i){
            fa->push(this->readFloat());
        }
        return fa;
    }

    sockaddr_in *readSockAddrIn() {
        assert(sizeof(sockaddr_in) < length_ - pos_);
        sockaddr_in *sai = new sockaddr_in;
        memcpy(sai, buffer_, sizeof(sockaddr_in));
        pos_ += sizeof(sockaddr_in);
        return sai;
    }



};
#endif //ASSIGNMENT6_DESERIALIZER_H
