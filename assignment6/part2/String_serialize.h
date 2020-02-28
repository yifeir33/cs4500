//
// Created by 王镱霏 on 2/27/20.
//
#include "string.h"
#include "Deserializer.h"
#ifndef ASSIGNMENT6_STRING_SERIALIZE_H
#define ASSIGNMENT6_STRING_SERIALIZE_H
class String_in_Serialize{
    String* str;
//    String**  str_array;
public:String_in_Serialize(String* s):str(s){
    }
    //, String** ss  ,str_array(ss)
public:String_in_Serialize():str(){
    }
    char* serialize(Serializer s){
        s.write(str);
//        s.write(str_array); ,str_array()
        return s.get();
    }
    void deserilize(Deserializer ds,char* buffer){
        size_t pos = 0;
       this->str = ds.readString(buffer+pos, sizeof(this->str->size_)+ this->str->size_);
       pos += sizeof(this->str->size_);
       pos += this->str->size_;
//       String** s_o = ds.readStringPP();

//    String_in_Serialize ans(s_o, str_array_o);

    }
    String* getString(){
        return this->str;
    }

};

#endif //ASSIGNMENT6_STRING_SERIALIZE_H
