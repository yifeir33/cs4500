#ifndef ASSIGNMENT6_DESERIALIZER_H
#define ASSIGNMENT6_DESERIALIZER_H

#include <netinet/in.h>
#include "string.h"
#include "array.h"
#include "object.h"

#include <cstdlib>

class Deserializer: public Object {
public: Deserializer(){}

    int readInt(char* c, size_t clen){
        int i;
        assert(sizeof(int)<= clen);
        memcpy(&i, &c, sizeof(int));
        return i;
    }
    float readFloat(char* c, size_t clen){
        float f;
        assert(sizeof(float)<= clen);
        memcpy(&f, &c, sizeof(float));

        return f;
    }
    bool readBool(char* c , size_t clen){
        bool b;
        assert(sizeof(bool)<= clen);
        memcpy(&b, &c, sizeof(bool));
        return b;
    }
    String* readString(char* c, size_t clen){
        StrBuff sb;
        size_t size = 0;
        memcpy(&size, &c, sizeof(size));
        int pos = sizeof(size);
        assert(pos<=clen);
        char *str = c + pos;
        for(int i = 0; i < size; ++i){
            sb.c(str[i]);
        }
        assert(pos<=clen);
        return sb.get();
    }
    StringArray readStringArray(char* c, size_t clen){
        StringArray sa(10);
        ObjectArray oa(10);

        size_t pos = 0;
        memcpy(&oa.data_+pos, c , sizeof(oa.data_));
        pos += sizeof(oa.data_);
        assert(pos<= clen);
        // capacity
        memcpy(&oa.capacity_ + pos, c, sizeof(oa.capacity_));
        pos += sizeof(oa.capacity_);
        assert(pos<= clen);
        // length
        memcpy(&oa.length_ + pos, c, sizeof(oa.length_));
        pos += sizeof(oa.length_);
        assert(pos<= clen);
        sa._array = oa;
        return sa;
    }
    FloatArray readFloatArray(char* c, size_t clen){
        FloatArray fa(10);
        size_t pos = 0;
        memcpy(&fa.data_+pos, c , sizeof(fa.data_));
        pos += sizeof(fa.data_);
        assert(pos<= clen);
        // capacity
        memcpy(&fa.capacity_ + pos, c, sizeof(fa.capacity_));
        pos += sizeof(fa.capacity_);
        assert(pos<= clen);
        // length
        memcpy(&fa.length_ + pos, c, sizeof(fa.length_));
        pos += sizeof(fa.length_);
        assert(pos<= clen);
        return fa;
    }
    sockaddr_in readSockAddrIn(char* c, size_t clen) {
        sockaddr_in sai;
        memcpy(&sai, c, sizeof(sai));
        assert(sizeof(sai)<= clen);
        return sai;
    }



};





#endif //ASSIGNMENT6_DESERIALIZER_H
